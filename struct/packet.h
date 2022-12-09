//
// Created by lkj on 2022/12/01.
//

#ifndef DNS_CLIENT_PACKET_H
#define DNS_CLIENT_PACKET_H

#include <vector>

class Packet {
private:
    std::vector<char> m_buf;
    int m_offset{0};
    int m_size{0};

public:
    Packet();
    explicit Packet(std::vector<char> buf);
    void add(char byte);
    void add(char *bytes, int size);

    char *get();

    int getPacketSize();

    int getOffset();
    void setOffset(int offset);
};

using PacketPtr = std::unique_ptr<Packet>;

#endif //DNS_CLIENT_PACKET_H
