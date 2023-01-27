//
// Created by lkj on 2022/12/28.
//

#ifndef DNS_CLIENT_DNSEXCEPTION_H
#define DNS_CLIENT_DNSEXCEPTION_H


#include <stdexcept>
#include "packet/struct/String.h"

class DnsException {
public:
    static std::runtime_error failConnectDnsServer(const String &dnsServer);
    static std::runtime_error failWritePacket();
    static std::runtime_error failReadPacket();
    static std::runtime_error unknownRecordType();
};


#endif //DNS_CLIENT_DNSEXCEPTION_H
