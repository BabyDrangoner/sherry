#include "http_server.h"
#include "../log.h"
//#include "sherry/http/servlets/config_servlet.h"
//#include "sherry/http/servlets/status_servlet.h"

namespace sherry {
namespace http {

static sherry::Logger::ptr g_logger = SYLAR_LOG_NAME("system");

HttpServer::HttpServer(bool keepalive
               ,sherry::IOManager* worker
               ,sherry::IOManager* io_worker
               ,sherry::IOManager* accept_worker)
    :TcpServer(worker, accept_worker)
    ,m_isKeepalive(keepalive) {
    m_dispatch.reset(new ServletDispatch);
    //m_type = "http";
    //m_dispatch->addServlet("/_/status", Servlet::ptr(new StatusServlet));
    //m_dispatch->addServlet("/_/config", Servlet::ptr(new ConfigServlet));
}

// void HttpServer::setName(const std::string& v) {
//     TcpServer::setName(v);
//     m_dispatch->setDefault(std::make_shared<NotFoundServlet>(v));
// }

void HttpServer::handleClient(Socket::ptr client) {
    SYLAR_LOG_DEBUG(g_logger) << "handleClient " << *client;
    HttpSession::ptr session(new HttpSession(client));
    do {
        auto req = session->recvRequest();
        if(!req) {
            SYLAR_LOG_DEBUG(g_logger) << "recv http request fail, errno="
                << errno << " errstr=" << strerror(errno)
                << " cliet:" << *client << " keep_alive=" << m_isKeepalive;
            break;
        }

        HttpResponse::ptr rsp(new HttpResponse(req->getVersion()
                            ,req->isClose() || !m_isKeepalive));
        // rsp->setHeader("Server", getName());
        m_dispatch->handle(req, rsp, session);
        // rsp->setBody("hello sherry");

        // SYLAR_LOG_INFO(g_logger) << "request:" << std::endl << *req;
        // SYLAR_LOG_INFO(g_logger) << "response:" << std::endl << *rsp;

        session->sendResponse(rsp);

        if(!m_isKeepalive || req->isClose()) {
            break;
        }
    } while(m_isKeepalive);
    session->close();
}

}
}