#include <stdlib.h>

#include <sys/socket.h>
#include <sys/types.h>

#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h> // for close

#include <iostream>
#include <string>

#include "TCPLog.hpp"

#define MAX_MSG_LEN 4096

#define ERR_CONNECTION_FAILURE -1
#define ERR_BIND_TO_SOCKET_FAILURE -2
#define ERR_SOCKET_CREATION_FAILURE -3
#define ERR_LISTENING_TO_SOCKET_FAILURE -4
#define ERR_CLIENT_CONNECTING_FAILURE -5