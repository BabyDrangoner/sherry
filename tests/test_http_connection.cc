#include <iostream>
#include "../sherry/http/http_connection.h"
#include "../sherry/log.h"
#include "../sherry/iomanager.h"

static sherry::Logger::ptr g_logger = SYLAR_LOG_ROOT();

void run(){
    sherry::Address::ptr addr = sherry::Address::LookupAnyIPAddress("www.sylar.top:80");
    if(!addr){
        SYLAR_LOG_INFO(g_logger) << "get addr error";
        return;
    }

    sherry::Socket::ptr sock = sherry::Socket::CreateTCP(addr);
    bool rt = sock->connect(addr);

    if(!rt){
        SYLAR_LOG_INFO(g_logger) << "connect " << addr << " failed";
        return;
    }

    sherry::http::HttpConnection::ptr conn(new sherry::http::HttpConnection(sock));
    sherry::http::HttpRequest::ptr req(new sherry::http::HttpRequest);
    req->setPath("/blog/");
    req->setHeader("host", "www.sylar.top");
    SYLAR_LOG_INFO(g_logger) << "req:" << std::endl
                             << *req;
    
    conn->sendRequest(req);
    auto rsp = conn->recvResponse();

    if(!rsp){
        SYLAR_LOG_INFO(g_logger) << "recv error";
        return;
    }  
    SYLAR_LOG_INFO(g_logger) << "rsp:" << std::endl 
                                 << *rsp;

}

int main(int argc, char ** argv){
    sherry::IOManager iom(2);
    iom.schedule(run);
    return 0;
}