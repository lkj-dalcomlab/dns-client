//
// Created by lkj on 2022/12/28.
//

#ifndef DNS_CLIENT_DNSCLIENT_H
#define DNS_CLIENT_DNSCLIENT_H

#include <vector>
#include "address.h"
#include "packet/struct/RecordType.h"

class DnsClient {
public:
    std::vector<AddressPtr> findAddress(const String &serverIP, const String &domain, const String recordType);
};


#endif //DNS_CLIENT_DNSCLIENT_H
