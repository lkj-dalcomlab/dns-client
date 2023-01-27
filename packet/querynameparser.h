//
// Created by lkj on 2023/01/18.
//

#ifndef DNS_CLIENT_QUERYNAMEPARSER_H
#define DNS_CLIENT_QUERYNAMEPARSER_H


#include "struct/String.h"
#include "buffer/buffer.h"
#include <vector>

class QueryNameParser {
    enum class State {
        DOMAIN_LENGTH,
        DOMAIN_NAME,
        QUERY_NAME_OFFSET,
        END
    };
private:
    Buffer *m_buffer;
    State m_state{State::DOMAIN_LENGTH};
    String m_queryName;
    std::vector<char> m_bytes;

    uint16_t m_tempOffset{0};

public:
    String parse(Buffer *buffer);
private:
    void clear();
    void parseDomainLength();
    void parseDomainName();
    void parseQueryNameOffset();
};

using QueryNameParserPtr = std::unique_ptr<QueryNameParser>;

#endif //DNS_CLIENT_QUERYNAMEPARSER_H
