// main.cpp
#include "http_server.hpp"
#include <cstdlib>

int main(int argc, char **argv) {
    int port = 8069;

    if (argc > 1) {
        port = std::stoi(argv[1]);
    }

    const char *api_key = std::getenv("CHATGPT_API_KEY");
    if (!api_key) {
        std::cerr << "Error: CHATGPT_API_KEY environment variable not set." << std::endl;
        return 1;
    }

    HTTPServer server(port, api_key);
    server.run();

    return 0;
}
