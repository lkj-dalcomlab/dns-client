//
// Created by lkj on 2022/12/09.
//

#ifndef DNS_CLIENT_SOCKET_H
#define DNS_CLIENT_SOCKET_H


#include "../packet//struct/String.h"

class Socket {
private:
    int m_sockFd;
public:
    Socket();
    bool connect(const String &ip, int port);
    int read(char *buf, uintmax_t size);
    int write(const char *buf, uintmax_t size);
};

#endif //DNS_CLIENT_SOCKET_H
