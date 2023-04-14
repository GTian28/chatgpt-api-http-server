// chatbot_adapter.hpp
#pragma once

#include "chatbot_interface.hpp"
#include <memory>
#include <string>

class ChatBotAdapter : public ChatBotInterface {
public:
    ChatBotAdapter(std::unique_ptr<ChatBotInterface> chatbot);
    std::string send_message(const std::string &message) override;
    void reset_conversation() override;
    void initialize(const std::string &config) override;

private:
    std::unique_ptr<ChatBotInterface> chatbot;
};
