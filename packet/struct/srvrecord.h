//
// Created by lkj on 2023/01/18.
//

#ifndef DNS_CLIENT_SRVRECORD_H
#define DNS_CLIENT_SRVRECORD_H


#include "query.h"
#include "Record.h"

class SrvRecord : public Record {
private:
    String m_ip;
    String m_target;
    uint16_t m_port;
    uint16_t m_priority{0};
    uint16_t m_weight{0};
public:

    const String &getIp() override;

    RecordType getType() override;

    uint16_t getPriority() override;

    uint16_t getWeight() override;

    void setIp(const String &ip);

    void setPriority(uint16_t priority);

    uint16_t getPort() override;

    void setPort(uint16_t port);

    void setWeight(uint16_t weight);

    const String &getTarget() override;

    void setTarget(const String &target);
};

using SrvRecordPtr = std::unique_ptr<SrvRecord>;

#endif //DNS_CLIENT_SRVRECORD_H
