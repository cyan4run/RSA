//
//  Rsa.cpp
//  BigInt test
//
//  Created by lincoxi on 2023/12/10.
//
#include<iostream>
#include "Rsa.h"
#include"BigInteger.h"
#include"LongBytesTransform.h"
#include"getprime.h"
using namespace std;
RSA::RSA(){
    m=BigInteger("0");
    c=BigInteger("0");
}
void RSA::Init(int num,BigInteger ee){
    cout<<"Start init with num_size:"<<num<<"...wait..."<<endl;
    p=getprime(num);
    q=getprime(num);
    N=p*q;
    Fi=(p-1)*(q-1);
    e=ee;
    d=d.modInverse(e, Fi);
    cout<<"Init finished."<<endl;
}
BigInteger RSA::RSA_EnCrypto(string ss, BigInteger e, BigInteger p, BigInteger q){
    BigInteger c;
    c=plaintextToNumber(ss);
    N=p*q;
    c=c.modpow(c, e, p*q);
    return c;
}
string RSA::RSA_DeCrypto(BigInteger c, BigInteger e, BigInteger p, BigInteger q){
    string m;
    BigInteger d;
    c=c-BigInteger("0");
    Fi=(p-1)*(q-1);
    d=d.modInverse(e, Fi);
    c=c.modpow(c, d, N);
    //cout<<c.getNumber()<<endl;
    return numberToPlaintext(c.getNumber());
}
string RSA::getPublicKey(){
    string publickey;
    publickey="e= "+e.getNumber()+"\r\n"+"N= "+N.getNumber();
    return publickey;
}
string RSA::getPrivatekey(){
    string privatekey;
    privatekey="d= "+d.getNumber()+"\r\n"+"N= "+N.getNumber();
    return privatekey;
}
string RSA::RSA_Decrypto_usr(BigInteger c, BigInteger dd, BigInteger NN){
    string result;
    BigInteger m=m.modpow(c, dd, NN);
    result=numberToPlaintext(m.getNumber());
    return result;
}
