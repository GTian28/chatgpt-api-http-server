// http_server.hpp
#pragma once

#include "chatbot_adapter.hpp"
#include <crow.h>

class HTTPServer {
public:
    HTTPServer(int port, const std::string & api_key);
    void run();

private:
    ChatBotAdapter chatbot_adapter;
    crow::SimpleApp app;

    void setup_routes();
};
