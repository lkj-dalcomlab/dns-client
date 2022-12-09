//
// Created by lkj on 2022/12/01.
//

#ifndef DNS_CLIENT_HEADERBUILDER_H
#define DNS_CLIENT_HEADERBUILDER_H


#include "struct/header.h"
#include <string>

class HeaderBuilder {
private:
    static uint8_t m_id;
public:
    HeaderPtr build(const std::string &domain);
};


#endif //DNS_CLIENT_HEADERBUILDER_H
