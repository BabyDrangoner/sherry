#include "sherry/http/http_parser.h"
#include "sherry/log.h"

static sherry::Logger::ptr g_logger = SYLAR_LOG_NAME("system");

const char test_request_data[] = "POST / HTTP/1.1\r\n"
                                "Host: www.sylar.top\r\n"
                                "Content-Length: 10\r\n\r\n"
                                "1234567890";

void test_request(){

    sherry::http::HttpRequestParser parser;
    std::string tmp = test_request_data;
    size_t s = parser.execute(&tmp[0], tmp.size());
    SYLAR_LOG_ERROR(g_logger) << "execute rt=" << s
        << " has_error=" << parser.hasError()
        << " is_finished=" << parser.isFinished()
        << " total=" << tmp.size()
        << " content_length=" << parser.getContentLength();
    tmp.resize(tmp.size() - s);
    SYLAR_LOG_INFO(g_logger) << parser.getData()->toString();
    SYLAR_LOG_INFO(g_logger) << tmp;
}

const char test_response_data[] = "HTTP/1.1 200 OK\r\n"
                                "Date: Tue, 04 Jun 2019 07:19:52 GMT\r\n"
                                "Server: Apache\r\n"
                                "Last-Modified: Tue, 04 Jun 2019 07:19:52 GMT\r\n"
                                "ETag: \"1d-588f1f3a7f7b9\"\r\n"
                                "Accept-Ranges: bytes\r\n"
                                "Content-Length: 29\r\n"
                                "Connection: close\r\n"
                                "Content-Type: text/html\r\n\r\n"
                                "<html>\r\n"
                                "<head>\r\n"
                                "<title>Test</title>\r\n"
                                "</head>\r\n"
                                "<body>\r\n"
                                "<h1>Hello, World!</h1>\r\n"
                                "</body>\r\n"
                                "</html>\r\n";

void test_response(){
    sherry::http::HttpResponseParser parser;
    std::string tmp = test_response_data;
    size_t s = parser.execute(&tmp[0], tmp.size());
    SYLAR_LOG_ERROR(g_logger) << "execute rt=" << s
        << " has_error=" << parser.hasError()
        << " is_finished=" << parser.isFinished()
        << " total=" << tmp.size()
        << " content_length=" << parser.getContentLength()
        << " tmp[s]=" << tmp[s];
    tmp.resize(tmp.size() - s);
    SYLAR_LOG_INFO(g_logger) << parser.getData()->toString();
    SYLAR_LOG_INFO(g_logger) << tmp;
}

int main(){{
    // test_request();
    SYLAR_LOG_INFO(g_logger) << "------------------";
    test_response();
    return 0;
}}