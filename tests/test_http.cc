#include "../sherry/http/http.h"
#include "../sherry/log.h"


void test_req(){
    sherry::http::HttpRequest::ptr req(new sherry::http::HttpRequest);  
    req->setHeader("host", "www.sylar.top");
    req->setBody("hello sylar");

    req->dump(std::cout) << std::endl;
}

void test_response(){
    sherry::http::HttpResponse::ptr rsp(new sherry::http::HttpResponse);  
    rsp->setHeader("X-X", "sherry");
    rsp->setBody("hello sherry");
    rsp->setStatus((sherry::http::HttpStatus)400);
    rsp->setClose(false);

    rsp->dump(std::cout) << std::endl;
}
int main(int argc, char** argv){
    test_req();
    test_response();
    return 0;
}   