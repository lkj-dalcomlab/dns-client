//
// Created by lkj on 2022/12/22.
//

#ifndef DNS_CLIENT_QUERYPARSER_H
#define DNS_CLIENT_QUERYPARSER_H


#include <vector>
#include "struct/query.h"
#include "buffer/buffer.h"
#include "querynameparser.h"

class QueryParser {
    enum class State {
//        QNAME_BYTES,
        QNAME,
        QNAME_OFFSET,
        DOUBLE_BYTES,
        QTYPE,
        QCLASS,
        END,
    };
private:
    QueryPtr m_query;
    QueryNameParser m_queryNameParser;
    Buffer *m_buffer;

    uint16_t m_tempOffset;
    std::vector<char> m_bytes;
    State m_state{State::QNAME};
public:
    QueryParser();

    QueryPtr parse(Buffer *buffer);
private:
    void saveQNameBytes();
    void parseQName();
    void parseQNameOffset();
    void parseQType();
    void parseQClass();
};


#endif //DNS_CLIENT_QUERYPARSER_H
