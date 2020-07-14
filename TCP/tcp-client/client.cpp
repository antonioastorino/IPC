#include "TCPCommon.hpp"

int main() {
    std::system("clear");

    const int domain   = AF_INET; // (= PF_INET) Internet domain sockets for use with IPv4 addresses
    const int type     = SOCK_STREAM; // bitstream socket used in TCP
    const int protocol = 0; // default type of socket that works with the other chosen params

    // create a socket
    int network_socket = socket(domain, type, protocol);
    // specify address
    struct sockaddr_in server_address;
    server_address.sin_family      = AF_INET;
    server_address.sin_port        = htons(9002);       // Use 80 for HTTP
    server_address.sin_addr.s_addr = htonl(0x7F000001); // 127.0.0.1

    int connection_status
        = connect(network_socket, (struct sockaddr*)&server_address, sizeof(server_address));

    if (connection_status == -1) {
        TCP::error("Connection error");
        return EXIT_FAILURE;
    }

    std::string client_message;
    std::cout << "Message to the server" << std::endl;

    std::getline(std::cin, client_message);

    send(network_socket, &client_message, sizeof(client_message), 0);

    std::string server_response;
    recv(network_socket, &server_response, sizeof(server_response), 0);

    TCP::info(server_response);

    close(network_socket);
    return 0;
}