#ifndef GETPRIME_H
#define GETPRIME_H
#include <stdio.h>
#include <deque>
#include <string>
#include<vector>
#include"BigInteger.h"
void strTodeque(std::deque<int>& a, std::string str);
void printDeque(const std::deque<int>& d);
void copydeque(std::deque<int>& x, std::deque<int>& y);
std::deque<int> dequeTobinary(std::deque<int>& x);
std::deque<int> dequeToAdd(std::deque<int>& x, std::deque<int>& y);
std::deque<int> binaryTodeque(std::deque<int>& x);
std::deque<int> dequeToSub(std::deque<int>& x, std::deque<int>& y);
int compare(std::deque<int>& x, std::deque<int>& y);
std::deque<int> dequeToMod(std::deque<int>& x, std::deque<int>& y);
std::deque<int> quick_multiply(std::deque<int>& x, std::deque<int>& y, std::deque<int>& z);
std::deque<int> quick_power(std::deque<int>& x, std::deque<int>& y, std::deque<int>& z);
bool miller_rabin(std::deque<int>& x);
std::deque<int> randnum();
std::string dequeToString(const std::deque<int>& d);
std::string getprime(int num);
void readPrime256(vector<BigInteger> &primes);
void readPrime512(vector<BigInteger> &primes);
void readPrime1024(vector<BigInteger> &primes);
void readPrime2048(vector<BigInteger> &primes);
BigInteger getrandom_prime(vector<BigInteger> primes);
#endif // GETPRIME_H
