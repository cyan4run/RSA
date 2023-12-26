//
//  LongBytesTransform.cpp
//  BigInt test
//
//  Created by lincoxi on 2023/12/10.
//

#include<string>
#include<sstream>
#include <iomanip>
#include "LongBytesTransform.h"
using namespace std;
string plaintextToNumber(const string& plaintext) {
    std::stringstream ss;
    bool leadingZero = true;

    for (char ch : plaintext) {
        if (ch != '0' || !leadingZero) {
            ss << std::setw(3) << std::setfill('0') << static_cast<int>(ch);
            leadingZero = false;
        }
    }

    // 如果明文全是0，则返回单个字符'0'，否则返回转换后的数字字符串
    return (ss.str().empty() || leadingZero) ? "0" : ss.str();
}

// 将大整数转换为明文字符串
string numberToPlaintext(const std::string& number) {
    std::stringstream ss;
    std::string temp;

    // 计算需要补充前导零的数量
    size_t leadingZeros = 3 - (number.length() % 3);
    if (leadingZeros == 3) {
        leadingZeros = 0; // 当长度为 3 的倍数时，无需补充前导零
    }

    // 补充前导零
    std::string paddedNumber = std::string(leadingZeros, '0') + number;

    // 将数字转换为字符，每三位数字对应一个字符
    for (size_t i = 0; i < paddedNumber.length(); i += 3) {
        temp = paddedNumber.substr(i, 3);
        char ch = 0;
        for (char digit : temp) {
            ch = ch * 10 + (digit - '0');
        }
        ss << ch;
    }

    return ss.str();
}
