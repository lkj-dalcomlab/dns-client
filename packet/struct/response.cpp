//
// Created by lkj on 2022/12/01.
//

#include "response.h"
#include "emptyrecord.h"

void Response::setQuery(QueryPtr query) {
    m_query = std::move(query);
}

const Query *Response::getQuery() const {
    return m_query.get();
}

uint32_t Response::getTtl() const {
    return m_ttl;
}

void Response::setTtl(uint32_t ttl) {
    m_ttl = ttl;
}

Record *Response::getRecord() const {
    return m_record.get();
}

void Response::setRecord(RecordPtr record) {
    m_record = std::move(record);
}

