#include "TCPCommon.hpp"

int main(int argc, const char* argv[])
{
    if (argc != 2)
    {
        TCP::error("Please specify one argument only - port number");
        exit(ERR_UNSPECIFIED_PORT_NUMBER);
    }
    std::system("clear");

    const int domain   = AF_INET; // (= PF_INET) Internet domain sockets for use with IPv4 addresses
    const int type     = SOCK_STREAM; // bitstream socket used in TCP
    const int protocol = 0; // default type of socket that works with the other chosen params

    // create a socket
    int network_socket = socket(domain, type, protocol);
    // specify address
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port   = htons(atoi(argv[1])); // Use 80 for HTTP
    inet_aton("127.0.0.1", (in_addr*)&server_address.sin_addr.s_addr);

    int connection_status
        = connect(network_socket, (struct sockaddr*)&server_address, sizeof(server_address));

    if (connection_status == -1)
    {
        TCP::error("Connection error");
        return EXIT_FAILURE;
    }

    std::string client_message = "";

    char server_response[MAX_MSG_LEN];
    recv(network_socket, &server_response, MAX_MSG_LEN, 0);
    TCP::info(server_response);

    while (!(client_message[0] == 92 && client_message[1] == 0))
    {
        std::cout << "Message to the server: ";
        std::getline(std::cin, client_message);

        send(network_socket, client_message.c_str(), client_message.length() + 1, 0);

        recv(network_socket, &server_response, MAX_MSG_LEN, 0);

        TCP::info(server_response);
    }

    std::cout << "Closing socket Nr. " << network_socket << std::endl;
    shutdown(network_socket, SHUT_RDWR);
    close(network_socket);
    return 0;
}
