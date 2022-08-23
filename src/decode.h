#ifndef DECODE_H
#define DECODE_H
#include<iostream>
using namespace std;

class Decode {
public:
    Decode();
    string base64_encode(const string& instr);

    //string base64_encode(std::byte,)
private:
    const char* base64_sheet = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/=";

};


/*

Base64将输入字符串按字节切分，取得每个字节对应的二进制值（若不足8比特则高位补0），
然后将这些二进制数值串联起来，再按照6比特一组进行切分（因为2^6=64），最后一组若不
足6比特则末尾补0。将每组二进制值转换成十进制，然后在上述表格中找到对应的符号并串联
起来就是Base64编码结果。

由于二进制数据是按照8比特一组进行传输，因此Base64按照6比特一组切分的二进制数据必
须是24比特的倍数（6和8的最小公倍数）。24比特就是3个字节，若原字节序列数据长度不是
3的倍数时且剩下1个输入数据，则在编码结果后加2个=；若剩下2个输入数据，则在编码结果
后加1个=。

完整的Base64定义可见RFC1421和RFC2045。因为Base64算法是将3个字节原数据编码为4
个字节新数据，所以Base64编码后的数据比原始数据略长，为原来的4/3。在电子邮件中，
根据RFC822规定，每76个字符，还需要加上一个回车换行。可以估算编码后数据长度大约为
原长的135.1%。

Base64可用于任意数据的底层二进制数据编码，以应用于只能传输ASCII字符的场合。不过
最常用于文本数据的处理传输，例如在MIME格式的电子邮件中，Base64可以用来编码邮件
内容，方便在不同语言计算机间传输而不乱码，注意是传输而不是显示，例如在西欧地区计算
机上使用utf-8编码即可正常显示中文（安装有对应字库），但是它未必能正常传输中文，这
时转换为Base64便无此顾虑。

Base64编码若无特别说明，通常约定非ASCII字符按照UTF-8字符集进行编码处理。
*/
#endif // DECODE_H

