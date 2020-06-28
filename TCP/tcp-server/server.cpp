#include "common.hpp"

int main() {

    std::system("clear");
    std::cout << "\033[33mServer running\n";

    const char server_message[256] = "\033[40mHello, client!\033[0m - greeting from the server";

    const int domain   = AF_INET; // (= PF_INET) Internet domain sockets for use with IPv4 addresses
    const int type     = SOCK_STREAM; // bitstream socket used in TCP
    const int protocol = 0; // default type of socket that works with the other chosen params

    // create a socket
    int network_socket = socket(domain, type, protocol);
    // specify address
    struct sockaddr_in server_address;
    server_address.sin_family      = AF_INET;
    server_address.sin_port        = htons(9002);
    server_address.sin_addr.s_addr = INADDR_ANY;

    int bind_status
        = bind(network_socket, (struct sockaddr*)&server_address, sizeof(server_address));

    if (bind_status == -1) {
        std::cout << "Connection error\n";
        return EXIT_FAILURE;
    }

    // listen to connections
    listen(network_socket, 5);
    int client_socket = accept(network_socket, NULL, NULL);

    // send the data
    send(client_socket, server_message, sizeof(server_message), 0);

    // close socket
    close(network_socket);
    return 0;
}