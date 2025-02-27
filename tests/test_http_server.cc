#include "../sherry/http/http_server.h"
#include "../sherry/log.h"

static sherry::Logger::ptr g_logger = SYLAR_LOG_ROOT();

void run(){
    sherry::http::HttpServer::ptr server(new sherry::http::HttpServer);
    sherry::Address::ptr addr = sherry::Address::LookupAnyIPAddress("0.0.0.0:8020");
    while(!server->bind(addr)){
        sleep(2);
    }
    auto sd = server->getServletDispatch();
    sd->addServlet("/sherry/xx", [](sherry::http::HttpRequest::ptr req
                    ,sherry::http::HttpResponse::ptr rsp
                    ,sherry::http::HttpSession::ptr session){
            rsp->setBody(req->toString());
            return 0;
    });

    sd->addGlobServlet("/sherry/*", [](sherry::http::HttpRequest::ptr req
                                ,sherry::http::HttpResponse::ptr rsp
                                ,sherry::http::HttpSession::ptr session){
        rsp->setBody("Glob:\r\n" + req->toString());
        return 0;
    }); 
    server->start();
}

int main(int argc, char** argv){
    sherry::IOManager iom(2);
    iom.schedule(run);
    return 0;
}