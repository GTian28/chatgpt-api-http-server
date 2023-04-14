// chat_gpt_client.hpp
#ifndef CHAT_GPT_CLIENT_HPP
#define CHAT_GPT_CLIENT_HPP

#include "chatbot_interface.hpp"
#include <iostream>
#include <string>
#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include <mutex>

class ChatGPTClient : public ChatBotInterface {
public:
    ChatGPTClient();
    ~ChatGPTClient();
    std::string send_message(std::string &message) override;
    void reset_conversation() override;
    void initialize(const std::string &api_key) override;

private:
    CURL *curl;
    std::string api_key;
    int token_limit = 1500;
    int token_count = 0;
    bool first_message = true;
    std::vector<nlohmann::json> conversation;

    static size_t write_to_string(void *ptr, size_t size, size_t nmemb, void *stream);
    std::string perform_request(const std::string &request_body);

    std::mutex conversation_mutex;
};

#endif // CHAT_GPT_CLIENT_HPP
