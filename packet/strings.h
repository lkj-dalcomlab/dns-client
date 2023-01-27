//
// Created by lkj on 2023/01/27.
//

#ifndef DNS_CLIENT_STRINGS_H
#define DNS_CLIENT_STRINGS_H


#include "struct/String.h"

class Strings {
public:
    static String trim(String text);
    static String toUpperCase(String text);
private:
    static void leftTrim(String &text);
    static void rightTrim(String &text);
};


#endif //DNS_CLIENT_STRINGS_H
