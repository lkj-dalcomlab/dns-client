//
// Created by lkj on 2022/12/22.
//

#ifndef DNS_CLIENT_QUERYPARSER_H
#define DNS_CLIENT_QUERYPARSER_H


#include <vector>
#include "../struct/query.h"
#include "../buffer/buffer.h"

class QueryParser {
    enum class State {
        QNAME_BYTES,
        QNAME,
        DOUBLE_BYTES,
        QTYPE,
        QCLASS,
        END,
    };
private:
    QueryPtr m_query;
    Buffer *m_buffer;
    std::vector<char> m_bytes;
    State m_state{State::QNAME_BYTES};
public:
    QueryParser();

    QueryPtr parse(Buffer *buffer);
private:
    void saveQNameBytes();
    void parseQName();
    void parseQType();
    void parseQClass();
};


#endif //DNS_CLIENT_QUERYPARSER_H
