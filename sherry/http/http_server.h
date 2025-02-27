
 #ifndef __SYLAR_HTTP_HTTP_SERVER_H__
 #define __SYLAR_HTTP_HTTP_SERVER_H__
 
 #include "../tcp_server.h"
 #include "http_session.h"
 #include "servlet.h"
 
 namespace sherry {
 namespace http {
 
 class HttpServer : public TcpServer {
 public:
     /// 智能指针类型
     typedef std::shared_ptr<HttpServer> ptr;

     HttpServer(bool keepalive = false
                ,sherry::IOManager* worker = sherry::IOManager::GetThis()
                ,sherry::IOManager* io_worker = sherry::IOManager::GetThis()
                ,sherry::IOManager* accept_worker = sherry::IOManager::GetThis());

     ServletDispatch::ptr getServletDispatch() const { return m_dispatch;}
     void setServletDispatch(ServletDispatch::ptr v) { m_dispatch = v;}
 
    // virtual void setName(const std::string& v) override;
 protected:
     virtual void handleClient(Socket::ptr client) override;
 private:
     // 是否支持长连接
     bool m_isKeepalive;
     // Servlet分发器
     ServletDispatch::ptr m_dispatch;
 };
 
 }
 }
 
 #endif