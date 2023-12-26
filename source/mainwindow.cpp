#include<iostream>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"BigInteger.h"
#include"Rsa.h"
#include<string>
#include<vector>
#include<getprime.h>
#include <QMessageBox>
BigInteger e("65537");
QString Qstr1="init succeed.You can input your text now.\r\n";
QString Qstr2="start init process ...pls wait...\r\n";
//QString Qstr3="publickey showed.\r\n";
int choice=0;//预加载选项
using namespace std;
vector<BigInteger> primes;
RSA rsa;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_Init_16_clicked()
{
    ui->textBrowser->clear();
    ui->m_input_textEdit->clear();
    ui->c_output_textEdit->clear();
    ui->textBrowser->insertPlainText(Qstr2);
    rsa.Init(16,e);
    cout<<"p="<<rsa.p.getNumber();
    cout<<"q="<<rsa.q.getNumber()<<endl;
    ui->textBrowser->insertPlainText(Qstr1);


}


void MainWindow::on_EnCrypto_Button_clicked()
{

    QString text=ui->m_input_textEdit->toPlainText();
    string str=text.toStdString();
    cout<<"str="<<str<<endl;
    string c=rsa.RSA_EnCrypto(str,e,rsa.p,rsa.q);
    cout<<"c is:"<<c<<endl;
    ui->textBrowser->insertPlainText("calculate successfully.\r\n");
  //  ui->m_input_textEdit->clear();
    text=QString::fromStdString(c);
    ui->c_output_textEdit->insertPlainText(text);
}

void MainWindow::on_Init_32_clicked()
{
    ui->textBrowser->clear();
    ui->m_input_textEdit->clear();
    ui->c_output_textEdit->clear();
    ui->textBrowser->insertPlainText(Qstr2);
    rsa.Init(32,e);
    cout<<"p="<<rsa.p.getNumber();
    cout<<"q="<<rsa.q.getNumber()<<endl;
    ui->textBrowser->insertPlainText(Qstr1);
}


void MainWindow::on_showPublicKey_Button_clicked()
{
    ui->publickey_textEdit->clear();
    string str=rsa.getPublicKey();
    QString text=QString::fromStdString(str);
    ui->publickey_textEdit->insertPlainText(text);
    ui->textBrowser->insertPlainText("publickey showed.\r\n");
}


void MainWindow::on_showPrivateKey_Button_clicked()
{
    ui->privatekey_textEdit->clear();
    string str=rsa.getPrivatekey();
    QString text=QString::fromStdString(str);
    ui->privatekey_textEdit->insertPlainText(text);
    ui->textBrowser->insertPlainText("privatekey showed.\r\n");
}


void MainWindow::on_Init_64_clicked()
{
    ui->textBrowser->clear();
    ui->m_input_textEdit->clear();
    ui->c_output_textEdit->clear();
    ui->textBrowser->insertPlainText(Qstr2);
    rsa.Init(64,e);
    cout<<"p="<<rsa.p.getNumber();
    cout<<"q="<<rsa.q.getNumber()<<endl;
    ui->textBrowser->insertPlainText(Qstr1);
}


void MainWindow::on_Init_128_clicked()
{
    ui->textBrowser->clear();
    ui->textBrowser->insertPlainText(Qstr2);
    ui->m_input_textEdit->clear();
    ui->c_output_textEdit->clear();
    rsa.Init(128,e);
    cout<<"p="<<rsa.p.getNumber();
    cout<<"q="<<rsa.q.getNumber()<<endl;
    ui->textBrowser->insertPlainText(Qstr1);
}


void MainWindow::on_Init_256_clicked()
{
    if(choice==0){
        ui->textBrowser->clear();
        ui->m_input_textEdit->clear();
        ui->textBrowser->insertPlainText(Qstr2);
        ui->c_output_textEdit->clear();
        rsa.Init(256,e);
        cout<<"p="<<rsa.p.getNumber();
        cout<<"q="<<rsa.q.getNumber()<<endl;
        ui->textBrowser->insertPlainText(Qstr1);
    }
    if(choice==2){
        primes.clear();
        ui->textBrowser->clear();
        ui->textBrowser->insertPlainText(Qstr2);
        ui->m_input_textEdit->clear();
        ui->c_output_textEdit->clear();
        do{
            readPrime256(primes);
            rsa.p=getrandom_prime(primes);
            rsa.q=getrandom_prime(primes);
        }while(rsa.p==rsa.q);
        cout<<"p="<<rsa.p.getNumber();
        cout<<"q="<<rsa.q.getNumber()<<endl;
        rsa.N=rsa.p*rsa.q;
        rsa.Fi=(rsa.p-1)*(rsa.q-1);
        rsa.e=e;
        rsa.d=(rsa.d).modInverse(rsa.e, rsa.Fi);
        cout<<"Init finished."<<endl;
        ui->textBrowser->insertPlainText(Qstr1);
    }
}


void MainWindow::on_Decrypto_Button_clicked() {
    try {
        QString text = ui->c_input_textEdit->toPlainText();
        string str1 = text.toStdString();
        text = ui->d_input_textEdit->toPlainText();
        string str2 = text.toStdString();
        text = ui->N_input_textEdit->toPlainText();
        string str3 = text.toStdString();
        text = QString::fromStdString(rsa.RSA_Decrypto_usr(BigInteger(str1), BigInteger(str2), BigInteger(str3)));
        ui->m_output_textEdit->insertPlainText(text);
        ui->textBrowser->insertPlainText("Decode successfully.");
    } catch (const std::exception& e) {
        // 处理异常，例如显示错误信息
        QString errorMsg = "请输入密文和私钥！ ";
        errorMsg += e.what();
        // 显示错误信息
        QMessageBox::critical(this, "Error", errorMsg);
    }
}


void MainWindow::on_pushButton_clicked()
{
    ui->m_input_textEdit->clear();
    ui->m_output_textEdit->clear();
    ui->N_input_textEdit->clear();
    ui->d_input_textEdit->clear();
    ui->c_input_textEdit->clear();
    ui->c_output_textEdit->clear();
    ui->privatekey_textEdit->clear();
    ui->publickey_textEdit->clear();
    ui->textBrowser->clear();

}



void MainWindow::on_Init_512_clicked()
{
    if(choice==0){
        ui->textBrowser->clear();
        ui->m_input_textEdit->clear();
        ui->textBrowser->insertPlainText(Qstr2);
        ui->c_output_textEdit->clear();
        rsa.Init(512,e);
        cout<<"p="<<rsa.p.getNumber();
        cout<<"q="<<rsa.q.getNumber()<<endl;
        ui->textBrowser->insertPlainText(Qstr1);
    }
    if(choice==2){
    primes.clear();
    ui->textBrowser->clear();
    ui->textBrowser->insertPlainText(Qstr2);
    ui->m_input_textEdit->clear();
    ui->c_output_textEdit->clear();
    do{
        readPrime512(primes);
        rsa.p=getrandom_prime(primes);
        rsa.q=getrandom_prime(primes);
    }while(rsa.p==rsa.q);
    cout<<"p="<<rsa.p.getNumber();
    cout<<"q="<<rsa.q.getNumber()<<endl;
    rsa.N=rsa.p*rsa.q;
    rsa.Fi=(rsa.p-1)*(rsa.q-1);
    rsa.e=e;
    rsa.d=(rsa.d).modInverse(rsa.e, rsa.Fi);
    cout<<"Init finished."<<endl;
    ui->textBrowser->insertPlainText(Qstr1);
    }
}


void MainWindow::on_Init_1024_clicked()
{
    if(choice==0){
        ui->textBrowser->clear();
        ui->m_input_textEdit->clear();
        ui->textBrowser->insertPlainText(Qstr2);
        ui->c_output_textEdit->clear();
        rsa.Init(1024,e);
        cout<<"p="<<rsa.p.getNumber();
        cout<<"q="<<rsa.q.getNumber()<<endl;
        ui->textBrowser->insertPlainText(Qstr1);
    }//我电脑算起来太慢了
    if(choice==2){
        primes.clear();
        ui->textBrowser->clear();
        ui->textBrowser->insertPlainText(Qstr2);
        ui->m_input_textEdit->clear();
        ui->c_output_textEdit->clear();
        do{
            readPrime1024(primes);
            rsa.p=getrandom_prime(primes);
            rsa.q=getrandom_prime(primes);
        }while(rsa.p==rsa.q);
        cout<<"p="<<rsa.p.getNumber();
        cout<<"q="<<rsa.q.getNumber()<<endl;
        rsa.N=rsa.p*rsa.q;
        rsa.Fi=(rsa.p-1)*(rsa.q-1);
        rsa.e=e;
        rsa.d=(rsa.d).modInverse(rsa.e, rsa.Fi);
        cout<<"Init finished."<<endl;
        ui->textBrowser->insertPlainText(Qstr1);
    }
}


void MainWindow::on_Init_2048_clicked()
{
    if(choice==0){
        ui->textBrowser->clear();
        ui->m_input_textEdit->clear();
        ui->textBrowser->insertPlainText(Qstr2);
        ui->c_output_textEdit->clear();
        rsa.Init(2048,e);
        cout<<"p="<<rsa.p.getNumber();
        cout<<"q="<<rsa.q.getNumber()<<endl;
        ui->textBrowser->insertPlainText(Qstr1);
    }
    if(choice==2){
        primes.clear();
        ui->textBrowser->clear();
        ui->textBrowser->insertPlainText(Qstr2);
        ui->m_input_textEdit->clear();
        ui->c_output_textEdit->clear();
        do{
            readPrime2048(primes);
            rsa.p=getrandom_prime(primes);
            rsa.q=getrandom_prime(primes);
        }while(rsa.p==rsa.q);
        cout<<"p="<<rsa.p.getNumber();
        cout<<"q="<<rsa.q.getNumber()<<endl;
        rsa.N=rsa.p*rsa.q;
        rsa.Fi=(rsa.p-1)*(rsa.q-1);
        rsa.e=e;
        rsa.d=(rsa.d).modInverse(rsa.e, rsa.Fi);
        cout<<"Init finished."<<endl;
        ui->textBrowser->insertPlainText(Qstr1);
    }
}


void MainWindow::on_checkBox_stateChanged(int arg1)
{
    choice=arg1;
    cout<<choice<<endl;
}

