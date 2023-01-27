//
// Created by lkj on 2022/12/28.
//

#include "dnsclient.h"
#include "net/socket.h"
#include "packet/packetbuilder.h"
#include "packet/bufferbuilder.h"
#include "packet/packetparser.h"
#include "dnsexception.h"
#include "packet/util.h"
#include "packet/strings.h"

#define MAX_BUF_SIZE 1024

std::vector<AddressPtr> DnsClient::findAddress(const String &serverIP, const String &domain, const String recordType) {
    auto type = Util::toRecordType(recordType);
    if (type == RecordType::RESERVED) {
        throw DnsException::unknownRecordType();
    }

    std::vector<AddressPtr> addList;
    auto trimDomain = Strings::trim(domain);

    auto socket = std::make_unique<Socket>();
    if (!socket->connect(serverIP, 53)) {
        throw DnsException::failConnectDnsServer(serverIP);
    }

    PacketBuilder packetBuilder;
    auto header = packetBuilder.build(trimDomain, type);

    BufferBuilder bufferBuilder;
    auto buffer = bufferBuilder.build(header.get());

    int write;
    while (buffer->getReadableBytes() > 0) {
        write = socket->write(buffer->getReadableData(), buffer->getReadableBytes());
        if (write < 0 && buffer->hasNext()) {
            throw DnsException::failWritePacket();
        }
        buffer->setIndex(buffer->getIndex() + write);
    }
    buffer->clear();

    PacketPtr packet{nullptr};
    PacketParser packetParser;
    while (!packet) {
        char buf[MAX_BUF_SIZE] = {0,};
        uint16_t read = socket->read(buf, MAX_BUF_SIZE);
        if (read < 0) {
            throw DnsException::failReadPacket();
        }
        if (read == 0) {
            continue;
        }
        buffer->appendBuffer(buf, read);
        packet = packetParser.parse(std::move(buffer));
    }


    for (auto i = 0; i < packet->getANCount(); ++i) {
        auto res = packet->getResponse(i);
        auto record = res->getRecord();
        addList.push_back(std::make_unique<Address>(Util::targetToIp(packet.get(), record), res->getRecord()->getPort()));
    }

    return addList;
}
