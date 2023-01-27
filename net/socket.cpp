//
// Created by lkj on 2022/12/09.
//

#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "socket.h"
#include "logger.h"

Socket::Socket() {
    m_sockFd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    timeval tv;
    tv.tv_sec = 5;
    tv.tv_usec = 0;
    setsockopt(m_sockFd, SOL_SOCKET, SO_RCVTIMEO, (char*)&tv, sizeof(timeval));
    LOG_INFO("socket create[{}]", m_sockFd);
}

sockaddr_in createSocketAddr(int port, in_addr_t addr) {
    //통신 서버 구동을 위한 구조체 sockaddr_in 구조체 설정
    sockaddr_in sockaddr;
    memset(&sockaddr, 0, sizeof(sockaddr));
    sockaddr.sin_family = AF_INET;
    sockaddr.sin_addr.s_addr = addr;
    sockaddr.sin_port = htons(port);
    return sockaddr;
}

bool Socket::connect(const String &ip, int port) {
    const sockaddr_in& sockaddr = createSocketAddr(port, inet_addr(ip.c_str()));
    int pear = ::connect(m_sockFd, (struct sockaddr *) &sockaddr, sizeof(sockaddr));
    if (pear < 0) {
        LOG_DEBUG("connectServer error");
        return false;
    }
    return true;
}

int Socket::read(char *buf, uintmax_t size) {
    memset(buf, 0x00, size);
//    return recv(m_sockFd, buf, size, MSG_DONTWAIT);
    return ::read(m_sockFd, buf, size);
}

int Socket::write(const char *buf, uintmax_t size) {
//    return send(m_sockFd, buf, size, MSG_DONTWAIT);
    return ::write(m_sockFd, buf, size);
}