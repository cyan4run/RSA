#ifndef RSA_H
#define RSA_H
//
//  Rsa.hpp
//  BigInt test
//
//  Created by 徐可钊 on 2023/12/10.
//
#include <stdio.h>
#include<string>
#include"BigInteger.h"
#include"LongBytesTransform.h"
#include"getPrime.h"
using namespace std;
class RSA{
private:
    BigInteger m;
    BigInteger c;



public:
    BigInteger p,q,e;
    BigInteger N;
    BigInteger Fi;
    BigInteger d;
    RSA();
    void Init(int num,BigInteger e);
    BigInteger RSA_EnCrypto(string ss, BigInteger e, BigInteger p, BigInteger q);
    string RSA_DeCrypto(BigInteger c, BigInteger e, BigInteger p, BigInteger q);
    string RSA_Decrypto_usr(BigInteger c,BigInteger dd,BigInteger NN);
    string getPublicKey();
    string getPrivatekey();
};

#endif // RSA_H
