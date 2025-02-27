#ifndef __SHERRY_HTTP_HTTP_CONNECTION_H__
#define __SHERRY_HTTP_HTTP_CONNECTION_H__

#include "../socket_stream.h"
#include "http.h"

namespace sherry {
namespace http {

class HttpConnection : public SocketStream {
public:
    typedef std::shared_ptr<HttpConnection> ptr;
    HttpConnection(Socket::ptr sock, bool owner = true);
    HttpRequest::ptr recvRequest();
    int sendRequest(HttpRequest::ptr req);
    HttpResponse::ptr recvResponse();
    int sendResponse(HttpResponse::ptr rsp);
};

}

}

#endif // __SHERRY_HTTP_HTTP_SESSION_H__