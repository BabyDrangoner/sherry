#include "../sherry/hook.h"
#include "../sherry/iomanager.h"
#include "../sherry/log.h"

sherry::Logger::ptr g_logger = SYLAR_LOG_ROOT();

void test_sleep(){
    sherry::IOManager iom(1);
    iom.schedule([](){
        sleep(2);
        SYLAR_LOG_INFO(g_logger) << "sleep 2";
    });

    iom.schedule([](){
        sleep(3);
        SYLAR_LOG_INFO(g_logger) << "sleep 3";
    });
    SYLAR_LOG_INFO(g_logger) << "test_sleep";
}

int main(int argc, char ** argv){
    test_sleep();
    return 0;
}

