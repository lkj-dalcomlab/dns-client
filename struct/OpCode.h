//
// Created by lkj on 2022/12/01.
//

#ifndef DNS_CLIENT_OPCODE_H
#define DNS_CLIENT_OPCODE_H

enum class OpCode {
    QUERY = 0x00,
    INVERSE_QUERY = 0x01,
    STATUS = 0x02,
    UNASSIGNED = 0x03,
    NOTIFY = 0x04,
    UPDATE = 0x05
    //UNASSIGNED = 0x06 ~ 0x0f
};

#endif //DNS_CLIENT_OPCODE_H