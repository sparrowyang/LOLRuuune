#include "decode.h"
Decode::Decode() {}
/**
 * @brief base64 encode string
 *
 * @param instr
 * @return string
 */
string Decode::base64_encode(const string& instr) {
    string res;
    int len        = instr.length();
    int tail       = len % 3;
    int head       = len - tail;
    int tail_index = 0;
    // head 3n char
    // todo: stdin get different result with string in.
    for (size_t i = 0; i < head; i += 3) {
        // 这里 Bug
        // 改了半天，脑壳不行了，逻辑不复杂，但是容易搞错位与位之间的对应
        int index_1 = instr[i] >> 2 & 0x3f;
        int index_2 = ((instr[i] & 0x03) << 4) | ((instr[i + 1] >> 4) & 0x0f);
        int index_3 = ((instr[i + 1] & 0x0f) << 2) | ((instr[i + 2] >> 6) & 0x03);
        int index_4 = instr[i + 2] & 0x3f;
        res += base64_sheet[index_1];
        res += base64_sheet[index_2];
        res += base64_sheet[index_3];
        res += base64_sheet[index_4];
        tail_index = i;
    }
    // tail
    if (tail == 1) {
        int index_1 = instr[tail_index + 3] >> 2 & 0x3f;
        int index_2 = (instr[tail_index + 3] & 0x03) << 4;
        res += base64_sheet[index_1];
        res += base64_sheet[index_2];
        res += "==";
    }
    else if (tail == 2) {
        int index_1 = instr[tail_index + 3] >> 2 & 0x3f;
        int index_2 = ((instr[tail_index + 3] & 0x03) << 4 |
            ((instr[tail_index + 4] >> 4) & 0x0f));
        int index_3 = (instr[tail_index + 4] & 0x0f) << 2;
        res += base64_sheet[index_1];
        res += base64_sheet[index_2];
        res += base64_sheet[index_3];
        res += '=';
    }
    return res;
}
// -nbad -nbap -bbo -bc -br -brs -c33 -cd33 -cdb -ce -ci4 -cli0-cp33 -di16
//
// -fc1 -fca -hnl -i4 -ip4 -l75 -lp -npcs -nprs -psl -saf -sai -saw -sc
// -nsob -nss -ts8
