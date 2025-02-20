#include "fd_manager.h"
#include "hook.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

namespace sherry{

FdCtx::FdCtx(int fd)
    :m_isInit(false)
    ,m_isSocket(false)
    ,m_sysNonblock(false)
    ,m_userNonblock(false)
    ,m_isClosed(false)
    ,m_fd(fd)
    ,m_recvTimeout(-1)
    ,m_sendTimeout(-1){
    init();
}

FdCtx::~FdCtx(){
}

bool FdCtx::init(){
    if(m_isInit){
        return  true;
    }
    m_recvTimeout = -1;
    m_sendTimeout = -1;

    struct stat fd_stat;
    if(-1 == fstat(m_fd, &fd_stat)){  // fdstat会将fd的信息存储在fd_stat中
        m_isInit = false;
        m_isSocket = false;
    } else {
        m_isInit = true;
        // 判断是否是套接字
        m_isSocket = S_ISSOCK(fd_stat.st_mode);
    }

    if(m_isSocket){
        // 获取fd的属性
        int flags = fcntl_f(m_fd, F_GETFL, 0);
        // 如果fd是阻塞的
        if(!(flags & O_NONBLOCK)){
            // 设置为非阻塞 
            fcntl_f(m_fd, F_SETFL, flags | O_NONBLOCK);
        }
        // 设置系统层面非阻塞
        m_sysNonblock = true;
    } else { 
        m_sysNonblock = false;
    }
    m_userNonblock = false;
    m_isClosed = false;
    return m_isInit;
}

void FdCtx::setTimeout(int type, uint64_t v){
    if(type == SO_RCVTIMEO){
        m_recvTimeout = v;
    } else {
        m_sendTimeout = v;
    }
}

uint64_t FdCtx::getTimeout(int type){
    if(type == SO_RCVTIMEO){
        return m_recvTimeout;
    } else {
        return m_sendTimeout;
    }
}

FdManager::FdManager(){
    m_datas.resize(64);
}

FdCtx::ptr FdManager::get(int fd, bool auto_create){
    RWMutexType::ReadLock lock(m_mutex);
    if((int)m_datas.size() <= fd){
        if(auto_create == false){
            return nullptr;
        } else {
            if(m_datas[fd] || !auto_create){
                return m_datas[fd];
            }
        }
    }
    lock.unlock();

    RWMutexType::WriteLock lock2(m_mutex);
    FdCtx::ptr ctx(new FdCtx(fd));
    m_datas[fd] = ctx;
    return ctx;
}

void FdManager::del(int fd){
    RWMutexType::WriteLock lock(m_mutex);
    if((int)m_datas.size() <= fd){
        return;
    }
    m_datas[fd].reset();
}


}