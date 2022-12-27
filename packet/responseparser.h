//
// Created by lkj on 2022/12/26.
//

#ifndef DNS_CLIENT_RESPONSEPARSER_H
#define DNS_CLIENT_RESPONSEPARSER_H


#include "../struct/response.h"
#include "../buffer/buffer.h"
#include "queryparser.h"

class ResponseParser {
private:
    enum class State {
        QUERY,
        TTL,
        RD_LENGTH,
        RDATA,
        END
    };
    State m_state{State::QUERY};
    Buffer *m_buffer;
    std::vector<char> m_bytes;
    QueryParser m_queryParser;
    ResponsePtr m_response{nullptr};

public:
    ResponsePtr parse(Buffer *buffer);
    void parseQuery();
    void parseTTL();
    void parseRdLength();
    void parseRdata();
};


#endif //DNS_CLIENT_RESPONSEPARSER_H
