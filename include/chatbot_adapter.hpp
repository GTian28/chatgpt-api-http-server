// chatbot_adapter.hpp
#pragma once

#include "chatbot_interface.hpp"
#include <memory>
#include <string>
#include <unordered_map>
#include <functional>

class ChatBotAdapter : public ChatBotInterface {
public:
    ChatBotAdapter();
    std::string send_message(std::string &message) override;
    void reset_conversation() override;
    void initialize(const std::string &config) override;

    std::string switch_chatbot(const std::string & name);

private:
    std::shared_ptr<ChatBotInterface> current_chatbot;
    std::unordered_map<std::string, std::shared_ptr<ChatBotInterface>> chatbots;
    std::unordered_map<std::string, std::function<std::shared_ptr<ChatBotInterface>()>> chatbot_factories;
};
