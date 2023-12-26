#include "mainwindow.h"

#include <QApplication>
#include"Rsa.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle(QStringLiteral("RSA Tools"));
    w.show();

  //  RSA rsa;
    return a.exec();
}
