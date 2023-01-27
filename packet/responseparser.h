//
// Created by lkj on 2022/12/26.
//

#ifndef DNS_CLIENT_RESPONSEPARSER_H
#define DNS_CLIENT_RESPONSEPARSER_H


#include "struct/response.h"
#include "buffer/buffer.h"
#include "queryparser.h"
#include "srvrecordparser.h"
#include "arecordparser.h"

class ResponseParser {
private:
    enum class State {
        INIT,
        QUERY,
        TTL,
        RECORD,
        RD_LENGTH,
        RDATA,
        END
    };
    State m_state{State::INIT};
    Buffer *m_buffer;
    std::vector<char> m_bytes;
    QueryParser m_queryParser;
    ARecordParser m_aParser;
    SrvRecordParser m_srvParser;

    uint16_t m_resDataLen{0};
    ResponsePtr m_response{nullptr};

public:
    ResponsePtr parse(Buffer *buffer);

protected:
    void init();
    void parseQuery();
    void parseTTL();
    void parseRecord();
};


#endif //DNS_CLIENT_RESPONSEPARSER_H
