//
// Created by lkj on 2022/12/01.
//

#ifndef DNS_CLIENT_RESPONSE_H
#define DNS_CLIENT_RESPONSE_H


#include "query.h"

class Response {
private:
    QueryPtr m_query{nullptr};
    uint32_t m_ttl{0};
    uint16_t m_resDataLen{0};
    String m_data;
public:
    Response();

    void setQuery(QueryPtr mQuestion);

    const Query *getQuestion() const;

    uint32_t getTtl() const;

    void setTtl(uint32_t ttl);

    uint16_t getResDataLen() const;

    void setResDataLen(uint16_t resDataLen);

    String getData() const;

    void setData(String data);
};

using ResponsePtr = std::unique_ptr<Response>;

#endif //DNS_CLIENT_RESPONSE_H
