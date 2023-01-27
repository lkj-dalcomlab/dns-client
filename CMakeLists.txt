cmake_minimum_required(VERSION 3.24)
project(dns_client)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
FetchContent_declare(
        spdlog
        GIT_REPOSITORY https://github.com/gabime/spdlog.git
        GIT_TAG v1.11.0
)
FetchContent_MakeAvailable(spdlog)

FetchContent_Declare(fmt URL https://github.com/fmtlib/fmt/archive/refs/tags/8.1.1.zip)
FetchContent_MakeAvailable(fmt)

add_executable(dns_client main.cpp packet/struct/packet.cpp packet/struct/packet.h packet/struct/OpCode.h
        packet/packetbuilder.cpp packet/packetbuilder.h packet/struct/query.cpp packet/struct/query.h
        packet/struct/String.h packet/struct/RecordType.h packet/struct/QClass.h packet/struct/response.cpp packet/struct/response.h
        packet/bufferbuilder.cpp packet/bufferbuilder.h logger/logger.h logger/logger.cpp
        packet/buffer/buffer.cpp packet/buffer/buffer.h packet/buffer/bufferexception.cpp net/socket.cpp net/socket.h
        packet/packetparser.cpp packet/packetparser.h packet/queryparser.cpp packet/queryparser.h
        packet/responseparser.cpp packet/responseparser.h packet/packetparser.cpp packet/packetparser.h address.cpp address.h dnsclient.cpp dnsclient.h dnsexception.cpp dnsexception.h packet/struct/srvrecord.cpp packet/struct/srvrecord.h packet/struct/Record.h packet/struct/arecord.cpp packet/struct/arecord.h packet/struct/emptyrecord.cpp packet/struct/emptyrecord.h packet/querynameparser.cpp packet/querynameparser.h packet/srvrecordparser.cpp packet/srvrecordparser.h packet/arecordparser.cpp packet/arecordparser.h packet/util.cpp packet/util.h packet/strings.cpp packet/strings.h)
target_link_libraries(dns_client PRIVATE spdlog fmt)
target_include_directories(dns_client PRIVATE logger)