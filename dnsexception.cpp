//
// Created by lkj on 2022/12/28.
//

#include "dnsexception.h"

std::runtime_error DnsException::failConnectDnsServer(const String &dnsServer) {
    return std::runtime_error("fail Connect DNS Server [" + dnsServer + "]");
}

std::runtime_error DnsException::failWritePacket() {
    return std::runtime_error("fail write packet.");
}

std::runtime_error DnsException::failReadPacket() {
    return std::runtime_error("fail read packet.");
}

std::runtime_error DnsException::unknownRecordType() {
    return std::runtime_error("unknown RecordType");
}
