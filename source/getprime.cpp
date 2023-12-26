//
//  getPrime.cpp
//  BigInt test
//
//  Created by lincoxi on 2023/12/11.
//

#include "getPrime.h"
#include<iostream>
#include<cstdlib>
#include<ctime>
#include<cmath>
#include<cstdio>
#include<deque>
#include<string>
#include<time.h>
#include<chrono>
#include<random>
#include<fstream>
#include <QFile>
#include <QTextStream>
#include <QDebug>
using namespace std;
int prime[10] = { 2,3,5,7,11,13,17,19,23,29 };
int num_size = 128 ;
void strTodeque(deque<int>&a,string str)
{
    int len = str.length();
    for (int i = 0; i < len; ++i)
    {
        a.push_back(str[i]-'0');
    }
}
void printDeque(const deque<int>& d)
{
    for (deque<int>::const_iterator it = d.begin(); it != d.end(); it++)
    {
        cout << *it;
    }
    cout << endl;
}

void copydeque(deque<int>& x, deque<int>& y)
{
    for (deque<int>::const_iterator it = x.begin(); it != x.end(); it++)
    {
        y.push_back(*it);
    }
}
deque<int> dequeTobinary(deque<int>& x)
{
    //int index = 0;
    deque<int> ans;
    deque<int> a;
    deque<int> temp;
    copydeque(x, a); //将队列x复制到a
    while (a.size()>0 &&a.front()!=0)
    {
        //二进制
        deque<int>::const_iterator it = a.end();
        it--;
        if (*it % 2 == 0)
        {
            ans.push_front(0);
        }
        else {
            ans.push_front(1);
        }
        //余数
        int flag = 0;
        for (it = a.begin(); it != a.end();it++ )
        {
            if ((*it+flag*10) < 2)
            {
                flag = *it;
                temp.push_back(0);
                if (it + 1 == a.end())
                {
                    //temp.push_back(0);
                }
            }
            else
            {
                temp.push_back((*it + flag * 10) / 2);
                flag = (*it + flag * 10) % 2;
            }
        }
        a.clear();
        while (temp.size()>0&&temp.front()==0)
        {
            temp.pop_front();
        }
        if (temp.size() > 0) {
            copydeque(temp, a);
            //printDeque(temp);
        }
        temp.clear();

    }
    return ans;
}
deque<int> dequeToAdd(deque<int>& x, deque<int>& y)
{
    deque<int> ans;
    deque<int> temp1;
    deque<int> temp2;
    //temp1长度>=temp2
    if (x.size() > y.size())
    {
        copydeque(x, temp1);
        copydeque(y, temp2);
    }
    else
    {
        copydeque(y, temp1);
        copydeque(x, temp2);
    }
    if (temp2.size() == 0)
    {
        return temp1;
    }
    deque<int>::const_iterator it1 = temp1.end();
    it1--;
    deque<int>::const_iterator it2 = temp2.end();
    it2--;
    int flag = 0;
    while (it2 != temp2.begin())
    {
        if ((*it1 + *it2 + flag) > 9)
        {
            ans.push_front((*it1 + *it2 + flag) % 10);
            flag = 1;
        }
        else
        {
            ans.push_front(*it1 + *it2 + flag);
            flag = 0;
        }
        it1--;
        it2--;
    }
    //如果位数相同
    if (it1 == temp1.begin())
    {
        if ((*it1 + *it2 + flag) > 9)
        {
            ans.push_front((*it1 + *it2 + flag) % 10);
            flag = 1;
            ans.push_front(flag);
        }
        else
        {
            ans.push_front(*it1 + *it2 + flag);
            flag = 0;
        }
    }
    //如果位数不相同
    else
    {
        //处理temp2首位
        if ((*it1 + *it2 + flag) > 9)
        {
            ans.push_front((*it1 + *it2 + flag) % 10);
            flag = 1;
        }
        else
        {
            ans.push_front(*it1 + *it2 + flag);
            flag = 0;
        }
        it1--;
        //处理temp1剩下的位数
        while (it1 != temp1.begin())
        {
            if ((*it1 + flag) > 9)
            {
                ans.push_front((*it1 + flag) % 10);
                flag = 1;
            }
            else
            {
                ans.push_front(*it1 + flag);
                flag = 0;
            }
            it1--;

        }
        //处理temp1首位
        if ((*it1 + flag) > 9)
        {
            ans.push_front((*it1 + flag) % 10);
            flag = 1;
            ans.push_front(flag);
        }
        else
        {
            ans.push_front(*it1 + flag);
            flag = 0;
        }
    }

    return ans;
}
deque<int> binaryTodeque(deque<int>& x)
{
    deque<int> ans;
    deque<int> one;
    if (x.size() == 1)
    {
        copydeque(x, ans);
        return ans;
    }
    else
    {
        ans.push_back(1);
        deque<int>::const_iterator it = x.begin();
        it++;
        while (it != x.end())
        {

            ans = dequeToAdd(ans, ans);
            one.push_back(*it);
            ans = dequeToAdd(ans, one);
            one.clear();
            it++;
        }

    }
    return ans;
}
deque<int> dequeToSub(deque<int>& x, deque<int>& y)
{
    //默认x>y
    deque<int> ans;
    deque<int>::const_iterator it1 = x.end();
    deque<int>::const_iterator it2 = y.end();
    it1--;
    it2--;
    int flag = 0;
    while (it2 != y.begin())
    {
        if ((*it1 - flag) >= *it2)
        {
            ans.push_front((*it1 - flag) - *it2);
            flag = 0;
        }
        else
        {
            ans.push_front((*it1 - flag + 10) - *it2);
            flag = 1;
        }
        it2--;
        it1--;
    }
    //处理y首位

    if ((*it1 - flag) >= *it2)
    {
        ans.push_front((*it1 - flag) - *it2);
        flag = 0;
    }
    else
    {
        ans.push_front((*it1 - flag + 10) - *it2);
        flag = 1;
    }
    if (it1 == x.begin())
    {
        while (ans.front() == 0&&ans.size()>1)
        {
            ans.pop_front();
        }
        return ans;
    }
    it1--;
    while (it1 != x.begin())
    {
        if (*it1 - flag >= 0)
        {
            ans.push_front(*it1 - flag);
            flag = 0;
        }
        else
        {
            ans.push_front(*it1 - flag + 10);
            flag = 1;
        }
        it1--;
    }
    ans.push_front(*it1 - flag);
    while (ans.front() == 0 && ans.size() > 1)
    {
        ans.pop_front();
    }
    return ans;

}
int compare(deque<int>& x, deque<int>& y)
{
    if (x.size() > y.size())
    {
        return 1;
    }
    else if (x.size() < y.size())
    {
        return 0;
    }
    else {
        deque<int>::const_iterator it1= x.begin();
        deque<int>::const_iterator it2 = y.begin();
        while (it1!=x.end())
        {
            if (*it1 > *it2)
            {
                return 1;
            }
            else if (*it1 < *it2)
            {
                return 0;
            }
            it1++;
            it2++;
        }
        return -1;
    }
}
deque<int> dequeToMod(deque<int>& x, deque<int>& y)
{
    deque<int> ans;
    deque<int> temp;
    copydeque(x, temp);
    deque<int> temp2;
    copydeque(y, temp2);
    int len = temp.size() - y.size();
    //x>y
    if (compare(x, y) == 1)
    {

        if (len<2)//10倍范围内
        {
            ans = dequeToSub(temp, y);
            while (compare(ans, y) != 0)
            {
                temp.clear();
                copydeque(ans,temp);
                ans.clear();
                ans = dequeToSub(temp, y);
            }
            return ans;
        }
        else
        {
            while (len >= 2)
            {
                int a = len - 1;
                while (a>0)
                {
                    temp2.push_back(0);
                    a--;
                }
                deque<int> temp3 = dequeToSub(temp, temp2);
                temp.clear();
                copydeque(temp3, temp);
                temp3.clear();
                len = temp.size() - y.size();
                temp2.clear();
                copydeque(y, temp2);
            }
            ans = dequeToMod(temp, y);
            return ans;
        }

    }
    else if (compare(x, y) == 0)
    {
        copydeque(x, ans);
    }
    else
    {
        ans.push_back(0);
    }
    return ans;
}
deque<int> quick_multiply(deque<int>&x, deque<int>& y, deque<int>& z ) {
    deque<int> ans;
    deque<int> res;
    copydeque(x, res);
    deque<int> b = dequeTobinary(y);
    while (b.size() > 0)
    {
        deque<int>::const_iterator it = b.end();
        it--;
        if (*it == 1)
        {
            ans = dequeToAdd(ans, res);
            ans = dequeToMod(ans, z);
        }
        res = dequeToAdd(res, res);
        res = dequeToMod(res, z);
        b.pop_back();
    }
    return ans;

}
deque<int> quick_power(deque<int>& x, deque<int>& y, deque<int>& z) {
    deque<int>ans;
    ans.push_back(1);
    deque<int>res;
    copydeque(x, res);
    deque<int> b = dequeTobinary(y);
    while (b.size() > 0)
    {
        deque<int>::const_iterator it = b.end();
        it--;
        if (*it == 1)
        {
            ans = quick_multiply(ans, res, z);
        }
        res = quick_multiply(res, res, z);
        b.pop_back();
    }
    return ans;
}
bool miller_rabin(deque<int>&x)
{
    deque<int> one;
    one.push_back(1);
    deque<int> target;
    target = dequeToSub(x, one);

    deque<int> k;
    deque<int> s;
    s.push_back(0);
    deque<int> t;
    t = dequeToSub(x, one);

    if (x.size() == 1 && x.front() == 2)//2是素数
    {
        return true;
    }
    if (x.size() == 1 && x.front() < 2)//小于2的不是素数
    {
        return false;
    }
    deque<int> temp = dequeTobinary(x);
    if (temp.back() % 2 == 0)//偶数不是素数
    {
        return false;
    }
    temp.clear();
    temp = dequeTobinary(t);
    while (temp.size() > 0)
    {
        deque<int>::const_iterator it = temp.end();
        it--;
        if (*it == 0)
        {
            s = dequeToAdd(s, one);
        }
        else
        {
            break;
        }
        temp.pop_back();
    }
    t = binaryTodeque(temp);
    temp.clear();
    for (int i = 0; i < 1; ++i){
        deque<int> a;
        a.push_back(prime[i]);
        if (compare(x, a) != 1)
            break;
        deque<int> b = quick_power(a, t, x);
        deque<int>j;
        j.push_back(1);
        while (compare(j, s) != 1)
        {
            k.clear();
            k = quick_multiply(b, b, x);
            if (compare(k, one) == -1 && compare(b, one) != -1 && compare(b, target) != -1)
            {
                return false;
            }
            b.clear();
            copydeque(k, b);
            j = dequeToAdd(j, one);
        }
        if (compare(b, one) != -1)
        {
            return false;
        }
    }
    return true;
}

// 重新定义 randnum() 函数，利用更高精度的时间函数作为种子
deque<int> randnum() {
    deque<int> ans;
    ans.push_front(1);

    auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    std::mt19937 generator(seed);

    for (int i = 0; i < num_size; ++i) {
        int a = generator() % 2;
        ans.push_back(a);
    }
    ans.push_back(1);
    ans = binaryTodeque(ans);
    return ans;
}


string dequeToString(const deque<int>& d) {
    string result;
    for (deque<int>::const_iterator it = d.begin(); it != d.end(); it++) {
        result += to_string(*it);
    }
    return result;
}
string getprime(int num){
    num_size=num;
    deque<int> ONE;
    ONE.push_back(1);
    int index=0;
    deque<int> x;
    while(1){
        x=randnum();
        bool ans=miller_rabin(x);
        if(ans){
            // printDeque(x);
            break;
        }
        else{
            index++;
        }
    }
    return dequeToString(x);
}
void readPrime512(vector<BigInteger> &primes) {
    clock_t start;
    clock_t finish;
    start=clock();
    QFile file("://primes/prime512.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "File open error!";
        exit(-1);
    }

    QTextStream in(&file);

    while (!in.atEnd()) {
        QString line = in.readLine();

        primes.push_back(BigInteger(line.toStdString()));
    }

    file.close();
    finish=clock();
    cout<<"\nruntime="<<double(finish-start)<<endl;
}
void readPrime1024(vector<BigInteger> &primes) {
    QFile file("://primes/prime1024.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "File open error!";
        exit(-1);
    }

    QTextStream in(&file);

    while (!in.atEnd()) {
        QString line = in.readLine();

        primes.push_back(BigInteger(line.toStdString()));
    }

    file.close();
}
void readPrime2048(vector<BigInteger> &primes) {
    QFile file("://primes/prime2048.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "File open error!";
        exit(-1);
    }

    QTextStream in(&file);

    while (!in.atEnd()) {
        QString line = in.readLine();

        primes.push_back(BigInteger(line.toStdString()));
    }

    file.close();
}
void readPrime256(vector<BigInteger> &primes) {
    QFile file("://primes/prime256.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "File open error!";
        exit(-1);
    }

    QTextStream in(&file);

    while (!in.atEnd()) {
        QString line = in.readLine();

        primes.push_back(BigInteger(line.toStdString()));
    }

    file.close();
}
BigInteger getrandom_prime(vector<BigInteger> primes){
    BigInteger prime;
    auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    std::mt19937 generator(seed);
    int i=generator()%primes.size();
    prime=primes[i];
    return prime;
}

