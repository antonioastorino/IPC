#include "common.hpp"

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
    server_address.sin_port        = htons(9002);
    server_address.sin_addr.s_addr = INADDR_ANY;

    int connection_status
        = connect(network_socket, (struct sockaddr*)&server_address, sizeof(server_address));

	if (connection_status == -1) {
		std::cout << "Connection error\n";
		return EXIT_FAILURE;
	}

    char server_response[256];
    recv(network_socket, &server_response, sizeof(server_response), 0);

    std::cout << server_response << std::endl;
    close(network_socket);
    return 0;
}