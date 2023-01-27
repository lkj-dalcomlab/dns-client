#include "dnsclient.h"
#include <iostream>

int main(int args, char **argv) {
    DnsClient client;
    String input{""};
    String record{""};
    while(input != "exit") {
        try {
            std::cout << "search domain :";
            std::cin >> input;
            if (input.empty()) {
                continue;
            }
            std::cout << "record type :";
            std::cin >> record;
            if (input.empty()) {
                continue;
            }

            auto addList = client.findAddress(/*"168.126.63.1"*/argv[1], input, record);
            for (const auto &address: addList) {
                std::cout << address->toString() << std::endl;
            }
            input = "";

        } catch (std::runtime_error e) {
            e.what();
        }
    }
    return 0;
}
