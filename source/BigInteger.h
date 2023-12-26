#ifndef BIGINTEGER_H
#define BIGINTEGER_H
#include <stdio.h>
#include <string>
#define MAX 10000 // for strings

using namespace std;
//-------------------------------------------------------------
class BigInteger
{
private:
    string number;
    bool sign;
public:
    BigInteger(); // empty constructor initializes zero
    BigInteger(string s); // "string" constructor
    BigInteger(string s, bool sin); // "string" constructor
    BigInteger(int n); // "int" constructor
    void setNumber(string s);
    const string& getNumber(); // retrieves the number
    void setSign(bool s);
    const bool& getSign();
    BigInteger absolute(); // returns the absolute value
    void operator = (BigInteger b);//重载赋值号
    bool operator == (BigInteger b);//重载等于
    bool operator != (BigInteger b);//重载非等
    bool operator > (BigInteger b);//重载大于
    bool operator < (BigInteger b);//重载小于
    bool operator >= (BigInteger b);//重载大于等于
    bool operator <= (BigInteger b);//重载小于等于
    BigInteger& operator ++(); // 重载前缀自增
    BigInteger  operator ++(int); //重载后缀自增
    BigInteger& operator --(); // 重载前缀自减
    BigInteger  operator --(int); //重载后缀自减
    BigInteger operator + (BigInteger b);//+
    BigInteger operator - (BigInteger b);//-
    BigInteger operator * (BigInteger b);//*
    BigInteger operator / (BigInteger b);// /
    BigInteger operator % (BigInteger b);//%
    BigInteger& operator += (BigInteger b);
    BigInteger& operator -= (BigInteger b);
    BigInteger& operator *= (BigInteger b);
    BigInteger& operator /= (BigInteger b);
    BigInteger& operator %= (BigInteger b);
    BigInteger& operator [] (int n);
    BigInteger operator -(); //负号
    operator string(); // 强制类型转换

    string mod(BigInteger& a, BigInteger& b) {//返回a模b的结果
        BigInteger temp = a;
        while (true)
        {
            if (greater(temp, b) != 1)
            {
                return temp;
            }
            temp = subtract(temp, b);
        }
    }
    //∑µªÿ a/b a%b <…Ã£¨”‡ ˝>
    pair<string ,string> divide(BigInteger& a, BigInteger& b) {
        BigInteger temp = BigInteger("0");//…Ã
        BigInteger a_temp = BigInteger(a);
        BigInteger b_temp = BigInteger(b);
        if (b.greater(b,a))//»Áπ˚≥˝ ˝¥Û”⁄±ª≥˝ ˝∑µªÿ0 ”‡ ˝Œ™±ª≥˝ ˝±æ…Ì
        {
            return make_pair("0",a.getNumber());
        }
        if (a.equals(a,b))
        {
            return make_pair("1", "0");
        }
        if (a.getNumber().size() == b.getNumber().size())
        {
            while (a_temp >= b)
            {
                a_temp = a_temp - b;
                temp = temp + 1;
            }
            return make_pair(temp.getNumber(), a_temp.getNumber());
        }
        int differenceInLength = abs((int)(a.getNumber().size() - b.getNumber().size()));

        BigInteger result = BigInteger("0");

        for (size_t i = 0; i < differenceInLength; i++)
        {
            int differenceInLength2 = abs((int)(a_temp.getNumber().size() - b.getNumber().size()));

            string One = "1";
            if (differenceInLength2 != 0)
            {
                One.append(differenceInLength2 - 1, '0');
            }
            BigInteger correntLevel = BigInteger(One);
            BigInteger b_buf = b * correntLevel;
            BigInteger sbsturtTimes = 0;
            while (a_temp >= b_buf)
            {
                a_temp = a_temp - b_buf;
                sbsturtTimes = sbsturtTimes + 1;
            }
            result = result + (sbsturtTimes * correntLevel);
        }
        return make_pair(result.getNumber(), a_temp.getNumber());
    }

    pair<string, string> divide(BigInteger a, BigInteger b) {
        BigInteger temp = BigInteger("0");//…Ã
        BigInteger a_temp = BigInteger(a);
        BigInteger b_temp = BigInteger(b);
        if (b.greater(b, a))
        {
            return make_pair("0", a.getNumber());
        }
        if (a.equals(a, b))
        {
            return make_pair("1", "0");
        }
        if (a.getNumber().size() == b.getNumber().size())
        {
            while (a_temp >= b)
            {
                a_temp = a_temp - b;
                temp = temp + 1;
            }
            return make_pair(temp.getNumber(), a_temp.getNumber());
        }
        int differenceInLength = abs((int)(a.getNumber().size() - b.getNumber().size()));
        BigInteger result = BigInteger("0");

        for (size_t i = 0; i < differenceInLength; i++)
        {
            int differenceInLength2 = abs((int)(a_temp.getNumber().size() - b.getNumber().size()));
            int d = differenceInLength2 - 1;
            string One = "1";
            if (differenceInLength2 != 0)
            {
                One.append(differenceInLength2 - 1, '0');
            }
            BigInteger correntLevel = BigInteger(One);
            BigInteger b_buf = b * correntLevel;
            BigInteger sbsturtTimes = 0;
            while (a_temp >= b_buf)
            {
                a_temp = a_temp - b_buf;
                sbsturtTimes = sbsturtTimes + 1;
            }
            result = result + (sbsturtTimes * correntLevel);
        }
        return make_pair(result.getNumber(), a_temp.getNumber());
    }
    static const BigInteger ZERO;
    static const BigInteger ONE;
    static const BigInteger TWO;
    static const BigInteger TEN;
    BigInteger modpow(BigInteger base, BigInteger exp, BigInteger n) {
        BigInteger result = BigInteger("1");
        result = ex_Mod(base, exp, n, result);
        return result;
    }
    BigInteger modInverse(BigInteger a, BigInteger m) {//逆模运算 ***关键***
        BigInteger x = ONE;
        BigInteger y = ONE;
        BigInteger gcd = e_gcd(a, m, x,y);
        x = x / gcd;

        if (x  < ZERO) {
            x = x+(m);
        }
        return x % m;
    }
private:
    bool equals(BigInteger n1, BigInteger n2);
    bool less(BigInteger n1, BigInteger n2);
    bool greater(BigInteger n1, BigInteger n2);
    string add(string number1, string number2);
    string subtract(string number1, string number2);
    string multiply(string n1, string n2);
    pair<string, long long> divide(string n, long long den);
    string toString(long long n);
    long long toInt(string s);
    BigInteger my_abs() {//绝对值
        BigInteger re = BigInteger(*this);
        if (re.getSign() == true)
        {
            re.setSign(false);
        }
        return re;
    }
    BigInteger ex_Mod(BigInteger& base, BigInteger& exp, BigInteger& n, BigInteger& result) {

        if (exp == (ZERO)) {
            return ONE;
        }
        while (1)
        {
            if (exp == (ONE))
            {
                exp = exp - (ONE);
                result = (result * (base)) % (n);
                return result;
            }
            char ar = exp.getNumber()[exp.getNumber().size() - 1] - '0';
            if ((ar & 0x01) == 0) {
                base = (base * (base)) % (n);
                exp = exp / (TWO);
            }
            else {
                exp = exp - (ONE);
                result = (result * (base)) % (n);
            }

        }
        return result;
    }
    BigInteger e_gcd(BigInteger& a, BigInteger& b, BigInteger& x,BigInteger& y) {
        if (b == ZERO) {
            x =   BigInteger("1");
            y =   BigInteger("0");
            return a;
        }
        BigInteger c = a % b;
        BigInteger ans = e_gcd(b, c, x,y);
        BigInteger temp = x;
        x = y;
        y = temp-((a / b)*x);
        return ans;
    }

};


#endif // BIGINTEGER_H
