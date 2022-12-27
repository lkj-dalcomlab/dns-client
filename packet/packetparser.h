//
// Created by lkj on 2022/12/22.
//

#ifndef DNS_CLIENT_PACKETPARSER_H
#define DNS_CLIENT_PACKETPARSER_H


#include "../struct/packet.h"
#include "../buffer/buffer.h"
#include "../struct/header.h"
#include "queryparser.h"

class PacketParser {
private:
    enum class State {
        HEADER_BYTES,
        TRANSACTION_ID,
        FLAGS,
        COUNT,
        QUERY,
        ANSWER,
        AUTHORITY,
        ADDITIONAL
    };
    State m_state{State::HEADER_BYTES};
    BufferPtr m_buffer{nullptr};
    HeaderPtr m_header;
    std::vector<char> m_headerBytes;
    uint16_t m_qCount{0};
    uint16_t m_anCount{0};
    uint16_t m_nsCount{0};
    uint16_t m_arCount{0};

    QueryParser m_queryParser;

public:
    PacketParser();

    HeaderPtr parse(BufferPtr buffer);
    void saveHeaderBytes();
    void parseTransactionId();
    void parseFlags();
    void parseCount();
    void parseQuery();
    void parseAnswer();
    void parseAuthority();
    void parseAdditional();
};


#endif //DNS_CLIENT_PACKETPARSER_H
