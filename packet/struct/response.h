//
// Created by lkj on 2022/12/01.
//

#ifndef DNS_CLIENT_RESPONSE_H
#define DNS_CLIENT_RESPONSE_H


#include "query.h"
#include "Record.h"
#include <vector>

class Response {
private:
    QueryPtr m_query{nullptr};
    uint32_t m_ttl{0};
    RecordPtr m_record{nullptr};
public:
    void setQuery(QueryPtr query);

    const Query *getQuery() const;

    uint32_t getTtl() const;

    void setTtl(uint32_t ttl);

    Record *getRecord() const;

    void setRecord(RecordPtr record);
};

using ResponsePtr = std::unique_ptr<Response>;

#endif //DNS_CLIENT_RESPONSE_H
