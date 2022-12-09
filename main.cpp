#include <iostream>
#include "headerbuilder.h"
#include "packetbuilder.h"

int main() {
    HeaderBuilder headerBuilder;
    auto header = headerBuilder.build("www.dalcomlab.com");

    PacketBuilder packetBuilder;
    auto packet = packetBuilder.build(header.get());
    return 0;
}
