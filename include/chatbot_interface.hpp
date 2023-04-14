// chatbot_interface.hpp
#pragma once

#include <string>

class ChatBotInterface {
public:
    virtual ~ChatBotInterface() = default;

    virtual std::string send_message(std::string &message) = 0;
    virtual void reset_conversation() = 0;
    virtual void initialize(const std::string &config) = 0;
};
