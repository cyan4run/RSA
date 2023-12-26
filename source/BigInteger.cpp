//
//  BigInteger.cpp
//  BigInt test
//
//  Created by lincoxi on 2023/12/10.
//



#include "BigInteger.h"
#include <iostream>
#include <string>
#include <sstream>
#include <cmath>


const BigInteger BigInteger::ZERO = BigInteger(0);
const BigInteger BigInteger::ONE = BigInteger(1);
const BigInteger BigInteger::TWO = BigInteger(2);
const BigInteger BigInteger::TEN = BigInteger(10);

BigInteger::BigInteger() //置空则置零
{
    number = "0";
    sign = false;
}
//-------------------------------------------------------------
BigInteger::BigInteger(string s) // 可以作为字符串输入
{
    if( isdigit(s[0]) )
    {
        setNumber(s);
        sign = false;
    }
    else
    {
        setNumber( s.substr(1) );
        sign = (s[0] == '-');
    }
}
//-------------------------------------------------------------
BigInteger::BigInteger(string s, bool sin) // 符号字符串输入
{
    setNumber( s );
    setSign( sin );
}
//-------------------------------------------------------------
BigInteger::BigInteger(int n) // 可以作为整数输入
{
    stringstream ss;
    string s;
    ss << n;
    ss >> s;


    if( isdigit(s[0]) ) // if not signed
    {
        setNumber( s );
        setSign( false );
    }
    else
    {
        setNumber( s.substr(1) );
        setSign( s[0] == '-' ); //首位置符号
    }
}
//===========================================================
void BigInteger::setNumber(string s) //置数
{
    number = s;
}
//===========================================================
const string& BigInteger::getNumber() // 输出该大整数（绝对值），这个算法被多次使用
{
    return number;
}
//===========================================================
void BigInteger::setSign(bool s)//置符号
{
    sign = s;
}
//===========================================================
const bool& BigInteger::getSign()//判断符号
{
    return sign;
}
//===========================================================
BigInteger BigInteger::absolute()//绝对值
{
    return BigInteger( getNumber() );
}
//===========================================================
void BigInteger::operator = (BigInteger b)
{
    setNumber( b.getNumber() );
    setSign( b.getSign() );
}
//===========================================================
bool BigInteger::operator == (BigInteger b)
{
    return equals((*this) , b);
}
//===========================================================
bool BigInteger::operator != (BigInteger b)
{
    return ! equals((*this) , b);
}
//===========================================================
bool BigInteger::operator > (BigInteger b)
{
    return greater((*this) , b);
}
//===========================================================
bool BigInteger::operator < (BigInteger b)
{
    return less((*this) , b);
}
//===========================================================
bool BigInteger::operator >= (BigInteger b)
{
    return equals((*this) , b)
           || greater((*this), b);
}
//===========================================================
bool BigInteger::operator <= (BigInteger b)
{
    return equals((*this) , b)
           || less((*this) , b);
}
//===========================================================

BigInteger& BigInteger::operator ++() //
{
    (*this) = (*this) + 1;
    return (*this);
}
//===========================================================

BigInteger BigInteger::operator ++(int)
{
    BigInteger before = (*this);

    (*this) = (*this) + 1;

    return before;
}
//===========================================================
BigInteger& BigInteger::operator --()
{
    (*this) = (*this) - 1;
    return (*this);

}
//===========================================================

BigInteger BigInteger::operator --(int) // postfix
{
    BigInteger before = (*this);

    (*this) = (*this) - 1;

    return before;
}
//===========================================================
BigInteger BigInteger::operator + (BigInteger b)
{
    BigInteger addition;
    if( getSign() == b.getSign() )
    {
        addition.setNumber( add(getNumber(), b.getNumber() ) );
        addition.setSign( getSign() );
    }
    else
    {
        if( absolute() > b.absolute() )
        {
            addition.setNumber( subtract(getNumber(), b.getNumber() ) );
            addition.setSign( getSign() );
        }
        else
        {
            addition.setNumber( subtract(b.getNumber(), getNumber() ) );
            addition.setSign( b.getSign() );
        }
    }
    if(addition.getNumber() == "0")
        addition.setSign(false);

    return addition;
}
//-------------------------------------------------------------
BigInteger BigInteger::operator - (BigInteger b)
{
    b.setSign( ! b.getSign() );
    return (*this) + b;
}
//-------------------------------------------------------------
BigInteger BigInteger::operator * (BigInteger b)
{
    BigInteger mul;

    mul.setNumber( multiply(getNumber(), b.getNumber() ) );
    mul.setSign( getSign() != b.getSign() );

    if(mul.getNumber() == "0")
            mul.setSign(false);

    return mul;
}
//===========================================================

BigInteger BigInteger::operator / (BigInteger b)
{

    BigInteger div = b;

    if (div.getNumber() == "0") // avoid (-0) problem
    {
        div.setSign(false);
    }
    else
    {
        BigInteger thisAbs = (*this).absolute();
        pair<string, string> re = divide((*this).absolute(), b.absolute());
        div = BigInteger(re.first);
        div.setSign((*this).sign ^ b.sign);
    }

    return div;
}
//===========================================================
BigInteger BigInteger::operator % (BigInteger b)
{
    BigInteger div = b;

    if (div.getNumber() == "0")
    {
        div.setSign(false);
    }
    else
    {
        BigInteger absBig = ((*this).getSign() == true) ? (b - (*this)) : (*this);
        pair<string, string> re = divide(absBig, b.absolute());
        div = BigInteger(re.second);
        div.setSign((*this).sign ^ b.sign);
    }
    return div;
}
//===========================================================
BigInteger& BigInteger::operator += (BigInteger b)
{
    (*this) = (*this) + b;
    return (*this);
}
//===========================================================
BigInteger& BigInteger::operator -= (BigInteger b)
{
    (*this) = (*this) - b;
    return (*this);
}
//===========================================================
BigInteger& BigInteger::operator *= (BigInteger b)
{
    (*this) = (*this) * b;
    return (*this);
}
//===========================================================
BigInteger& BigInteger::operator /= (BigInteger b)
{
    (*this) = (*this) / b;
    return (*this);
}
//===========================================================
BigInteger& BigInteger::operator %= (BigInteger b)
{
    (*this) = (*this) % b;
    return (*this);
}
//===========================================================
BigInteger& BigInteger::operator [] (int n)
{
    return *(this + (n*sizeof(BigInteger)));
}
//===========================================================
BigInteger BigInteger::operator -() // unary minus sign
{
    return (*this) * -1;
}
//===========================================================
BigInteger::operator string()
{
    string signedString = ( getSign() ) ? "-" : "";
    signedString += number;
    return signedString;
}
//===========================================================

bool BigInteger::equals(BigInteger n1, BigInteger n2)
{
    return n1.getNumber() == n2.getNumber()
           && n1.getSign() == n2.getSign();
}
//===========================================================
bool BigInteger::less(BigInteger n1, BigInteger n2)
{
    bool sign1 = n1.getSign();
    bool sign2 = n2.getSign();

    if(sign1 && ! sign2)
        return true;

    else if(! sign1 && sign2)
        return false;

    else if(! sign1)
    {
        if(n1.getNumber().length() < n2.getNumber().length() )
            return true;
        if(n1.getNumber().length() > n2.getNumber().length() )
            return false;
        return n1.getNumber() < n2.getNumber();
    }
    else
    {
        if(n1.getNumber().length() > n2.getNumber().length())
            return true;
        if(n1.getNumber().length() < n2.getNumber().length())
            return false;
        return n1.getNumber().compare( n2.getNumber() ) > 0; // greater with -ve sign is LESS
    }
}
//===========================================================
bool BigInteger::greater(BigInteger n1, BigInteger n2)
{
    //n1>n2返回真
    //否则假
    return ! equals(n1, n2) && ! less(n1, n2);
}

//===========================================================
string BigInteger::add(string number1, string number2)//加操作
{
    string add = (number1.length() > number2.length()) ?  number1 : number2;
    char carry = '0';//进位初始置零
    int differenceInLength = abs( (int) (number1.size() - number2.size()) );//长度比较

    if(number1.size() > number2.size())
        number2.insert(0, differenceInLength, '0');//让两个数的长度一样便于我加减
    else
        number1.insert(0, differenceInLength, '0');
    for(int i=number1.size()-1; i>=0; --i)//循环是逐位进行加操作
    {
        add[i] = ((carry-'0')+(number1[i]-'0')+(number2[i]-'0')) + '0';//add用于记录加完以后每位的数值是否达到10若则进位

        if(i != 0)
        {
            if(add[i] > '9')
            {
                add[i] -= 10;
                carry = '1';
            }
            else
                carry = '0';
        }
    }
    //
    if(add[0] > '9')//如果在最大位产生进位
    {
        add[0]-= 10;
        add.insert(0,1,'1');//前插1
    }
    return add;
}

//================================================
string BigInteger::subtract(string number1, string number2)
{
    string sub = (number1.length()>number2.length())? number1 : number2;
    int differenceInLength = abs( (int)(number1.size() - number2.size()) );
    if(number1.size() > number2.size())    //÷¥––≤π0
        number2.insert(0, differenceInLength, '0');

    else
        number1.insert(0, differenceInLength, '0');

    for(int i=number1.length()-1; i>=0; --i)
    {
        if(number1[i] < number2[i])
        {
            number1[i] += 10;
            number1[i-1]--;
        }
        sub[i] = ((number1[i]-'0')-(number2[i]-'0')) + '0';
    }

    while(sub[0]=='0' && sub.length()!=1)
        sub.erase(0,1);

    return sub;
}

//==========================================================================
string BigInteger::multiply(string n1, string n2)
{
    if(n1.length() > n2.length())
        n1.swap(n2);

    string res = "0";
    for(int i=n1.length()-1; i>=0; --i)
    {
        string temp = n2;
        int currentDigit = n1[i]-'0';
        int carry = 0;

        for(int j=temp.length()-1; j>=0; --j)
        {
            temp[j] = ((temp[j]-'0') * currentDigit) + carry;

            if(temp[j] > 9)
            {
                carry = (temp[j]/10);
                temp[j] -= (carry*10);
            }
            else
                carry = 0;
            temp[j] += '0';
        }

        if(carry > 0)
            temp.insert(0, 1, (carry+'0'));

        temp.append((n1.length()-i-1), '0');
        res = add(res, temp);
    }

    while(res[0] == '0' && res.length()!=1)
        res.erase(0,1);
    return res;
}

pair<string, long long> BigInteger::divide(string n, long long den) //除，返回的是商和余数
{
    long long rem = 0;
    string result; result.resize(MAX);

    for(int indx=0, len = n.length(); indx<len; ++indx)
    {
        rem = (rem * 10) + (n[indx] - '0');
        result[indx] = rem / den + '0';
        rem %= den;
    }
    result.resize( n.length() );

    while( result[0] == '0' && result.length() != 1)
        result.erase(0,1);

    if(result.length() == 0)
        result = "0";

    return make_pair(result, rem);
}

//=====================================
string BigInteger::toString(long long n)
{
    stringstream ss;
    string temp;

    ss << n;
    ss >> temp;

    return temp;
}

//======================================

long long BigInteger::toInt(string s)
{
    long long sum = 0;

    for(int i=0; i<s.length(); i++)
        sum = (sum*10) + (s[i] - '0');

    return sum;
}

