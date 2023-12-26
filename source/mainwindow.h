#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_Init_16_clicked();

    void on_EnCrypto_Button_clicked();

    void on_Init_32_clicked();

    void on_showPublicKey_Button_clicked();

    void on_showPrivateKey_Button_clicked();

    void on_Init_64_clicked();

    void on_Init_128_clicked();

    void on_Init_256_clicked();

    void on_Decrypto_Button_clicked();

    void on_pushButton_clicked();

    void on_Init_512_clicked();

    void on_Init_1024_clicked();

    void on_Init_2048_clicked();

    void on_checkBox_stateChanged(int arg1);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
