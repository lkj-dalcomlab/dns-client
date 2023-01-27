//
// Created by lkj on 2023/01/19.
//

#ifndef DNS_CLIENT_SRVRECORDPARSER_H
#define DNS_CLIENT_SRVRECORDPARSER_H


#include "buffer/buffer.h"
#include "querynameparser.h"
#include "struct/srvrecord.h"
#include <vector>

class SrvRecordParser {
    enum class State {
        RDATA_LENGTH,
        PRIORITY,
        WEIGHT,
        PORT,
        TARGET,
        END
    };
private:
    State m_state{State::RDATA_LENGTH};
    Buffer *m_buffer;
    QueryNameParser m_queryNameParser;
    SrvRecordPtr m_record{nullptr};
    std::vector<char> m_bytes;
    uint16_t m_rDataLength{0};
public:
    RecordPtr parse(Buffer *buffer);
private:
    void parseRdLength();
    void parsePriority();
    void parseWeight();
    void parsePort();
    void parseTarget();
};


#endif //DNS_CLIENT_SRVRECORDPARSER_H
