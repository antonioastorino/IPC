#include <arpa/inet.h>
#include <iostream>
#include <netinet/in.h>
#include <stdlib.h>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h> // for close

#include "TCPLog.hpp"

#define MAX_MSG_LEN 4096

#define ERR_CONNECTION_FAILURE -1
#define ERR_BIND_TO_SOCKET_FAILURE -2
#define ERR_SOCKET_CREATION_FAILURE -3
#define ERR_LISTENING_TO_SOCKET_FAILURE -4
#define ERR_CLIENT_CONNECTING_FAILURE -5
#define ERR_UNSPECIFIED_PORT_NUMBER -6