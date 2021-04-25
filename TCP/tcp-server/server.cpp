#include "TCPCommon.hpp"
#include <sstream>

int main(int argc, const char* argv[])
{
    if (argc != 2)
    {
        TCP::error("Please specify one argument only - port number");
        exit(ERR_UNSPECIFIED_PORT_NUMBER);
    }
    std::system("clear");
    TCP::info("Server running");

    const int domain   = AF_INET; // (= PF_INET) Internet domain sockets for use with IPv4 addresses
    const int type     = SOCK_STREAM; // bitstream socket used in TCP
    const int protocol = 0; // default type of socket that works with the other chosen params

    // create a socket
    int network_socket = socket(domain, type, protocol);
    if (network_socket == -1)
    {
        TCP::error("Failed to create socket");
        return ERR_SOCKET_CREATION_FAILURE;
    }

    // specify address
    struct sockaddr_in server_address;
    server_address.sin_family      = AF_INET;
    server_address.sin_port        = htons(atoi(argv[1]));
    server_address.sin_addr.s_addr = INADDR_ANY; // htonl(0x7F000001 /*127.0.0.1*/);

    int bind_status = bind(network_socket, (sockaddr*)&server_address, sizeof(server_address));

    if (bind_status == -1)
    {
        TCP::error("Failed to bind to network socket");
        return ERR_BIND_TO_SOCKET_FAILURE;
    }

    // listen to connections
    if (listen(network_socket, SOMAXCONN) == -1)
    {
        TCP::error("Failed to listen to socket");
        return ERR_LISTENING_TO_SOCKET_FAILURE;
    }
    sockaddr_in client;
    socklen_t client_size;

    while (1)
    {
        int client_socket = accept(network_socket, (sockaddr*)&client, &client_size);

        if (client_socket == -1)
        {
            TCP::error("Problem with client connecting");
            return ERR_CLIENT_CONNECTING_FAILURE;
        }
        const char welcome_msg[] = "Welcome to this fantastic TCP server";
        send(client_socket, &welcome_msg, sizeof(welcome_msg), 0);

        if (fork() == 0)
        {
            char buffer[MAX_MSG_LEN];
            buffer[0] = 0;
            while (!(buffer[0] == 92 && buffer[1] == 0))
            {
                memset(&buffer, 0, MAX_MSG_LEN);
                // receive message from the client
                int bytes_recv = recv(client_socket, &buffer, MAX_MSG_LEN, 0);

                std::stringstream s;
                s << "Client socket: " << client_socket;
                TCP::print(buffer);
                TCP::info(s.str().c_str());

                send(client_socket, &buffer, sizeof(buffer), 0);
            }

            std::cout << "Closing socket Nr. " << client_socket << std::endl;
            shutdown(client_socket, SHUT_RDWR);
            close(client_socket);
            return 0;
        }
        else
        {
            std::stringstream s;
            s << "Connection to socket nr. " << client_socket << " accepted";
            TCP::info(s.str());
        }
    }

    return 0;
}
