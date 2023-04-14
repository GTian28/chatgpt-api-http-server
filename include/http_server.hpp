// http_server.hpp
#pragma once

#include "chat_gpt_client.hpp"
#include <crow.h>

class HTTPServer {
public:
    HTTPServer(int port, const std::string & api_key);
    void run();

private:
    ChatGPTClient chat_gpt_client;
    crow::SimpleApp app;

    void setup_routes();
};
