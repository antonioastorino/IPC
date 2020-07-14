#include "TCPCommon.hpp"
#include <sstream>

int main() {

    std::system("clear");
    TCP::info("Server running");

    const int domain   = AF_INET; // (= PF_INET) Internet domain sockets for use with IPv4 addresses
    const int type     = SOCK_STREAM; // bitstream socket used in TCP
    const int protocol = 0; // default type of socket that works with the other chosen params

    // create a socket
    int network_socket = socket(domain, type, protocol);
    if (network_socket == -1) {
        TCP::error("Failed to create socket");
        return ERR_SOCKET_CREATION_FAILURE;
    }

    // specify address
    struct sockaddr_in server_address;
    server_address.sin_family      = AF_INET;
    server_address.sin_port        = htons(9002);       // Use 80 for HTTP
    server_address.sin_addr.s_addr = htonl(0x7F000001); // 127.0.0.1

    int bind_status = bind(network_socket, (sockaddr*)&server_address, sizeof(server_address));

    if (bind_status == -1) {
        TCP::error("Failed to bind to network socket");
        return ERR_BIND_TO_SOCKET_FAILURE;
    }

    // listen to connections
    if (listen(network_socket, SOMAXCONN) == -1) {
        TCP::error("Failed to listen to socket");
        return ERR_LISTENING_TO_SOCKET_FAILURE;
    }
    sockaddr_in client;
    socklen_t client_size;

    while (1) {
        int client_socket = accept(network_socket, (sockaddr*)&client, &client_size);

        if (client_socket == -1) {
            TCP::error("Problem with client connecting");
            return ERR_CLIENT_CONNECTING_FAILURE;
        }

        if (fork() == 0) {
            std::string buffer = "";
            // receive message from the client
            int bytes_recv = recv(client_socket, &buffer, 4096, 0);

            std::stringstream s;
            s << "Message:       " << buffer << "\nClient socket: " << client_socket;

            TCP::info(s.str().c_str());
            send(client_socket, &buffer, sizeof(buffer), 0);
            close(client_socket);
            return 0;
        } else {
            TCP::info("Server forked");
        }
    }

    return 0;
}