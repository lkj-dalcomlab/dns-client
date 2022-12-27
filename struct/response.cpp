//
// Created by lkj on 2022/12/01.
//

#include "response.h"

void Response::setQuery(QueryPtr query) {
    m_query = std::move(query);
}

const Query *Response::getQuestion() const {
    return m_query.get();
}

uint32_t Response::getTtl() const {
    return m_ttl;
}

void Response::setTtl(uint32_t ttl) {
    m_ttl = ttl;
}

uint16_t Response::getResDataLen() const {
    return m_resDataLen;
}

void Response::setResDataLen(uint16_t resDataLen) {
    m_resDataLen = resDataLen;
}

String Response::getData() const {
    return m_data;
}

void Response::setData(String data) {
    m_data = data;
}
