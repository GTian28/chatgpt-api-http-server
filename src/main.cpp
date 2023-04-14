// main.cpp
#include "http_server.hpp"

int main(int argc, char **argv) {
    int port = 8080;

    if (argc > 1) {
        port = std::stoi(argv[1]);
    }

    HTTPServer server(port);
    server.run();

    return 0;
}
