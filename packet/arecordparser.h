//
// Created by lkj on 2023/01/25.
//

#ifndef DNS_CLIENT_ARECORDPARSER_H
#define DNS_CLIENT_ARECORDPARSER_H


#include "struct/Record.h"
#include "buffer/buffer.h"
#include <vector>

class ARecordParser {
    enum class State {
        INIT,
        RDATA_LENGTH,
        IP,
        END
    };
private:
    State m_state{State::INIT};
    Buffer *m_buffer;
    RecordPtr m_record{nullptr};
    std::vector<char> m_bytes;
    uint16_t m_rDataLength{0};
public:
    RecordPtr parse(Buffer *buffer);
    void parseRdLength();
    void parseIP();

private:
    String toIP();
};


#endif //DNS_CLIENT_ARECORDPARSER_H
