//
// Created by lkj on 2023/01/27.
//

#include "strings.h"

String Strings::trim(String text) {
    leftTrim(text);
    rightTrim(text);
    return text;
}

void Strings::leftTrim(String &text) {
    text.erase(text.begin(), std::find_if(text.begin(), text.end(), [](unsigned char ch) {
        return !std::isspace(ch);
    }));
}

void Strings::rightTrim(String &text) {
    text.erase(std::find_if(text.rbegin(), text.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base(), text.end());
}

String Strings::toUpperCase(String text) {
    std::transform(text.begin(), text.end(), text.begin(),
                   [](unsigned char c) { return std::toupper(c); });
    return text;
}