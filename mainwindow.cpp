#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    mCCMIS = new CCMIS();

    QRegExp regx("[0-9]+$");    //正则表达式，只允许输入0~9
    QValidator *validator = new QRegExpValidator(regx, ui->UserNameLineEdit);
    ui->UserNameLineEdit->setValidator(validator);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{

    int number = ui->UserNameLineEdit->text().toInt();

    mCCMIS->SetUserNumber(number);

    if (mCCMIS->CheckPassword(
                ui->PasswordLineEdit->text().toStdString()))
    {
        QMessageBox msg;

        if (number < 1000)
        {
            msg.setText(tr("登录成功！\n 你是：管理员"));
            //SuperuserMainWindow* window = new SuperuserMainWindow();
            Info_Table* AllInfo = new Info_Table(mCCMIS->GetInfoPointer());
            AllInfo->show();
        } else if (number < 4000){
            msg.setText(tr("登录成功！\n 你是：店家"));

        } else {
            msg.setText(tr("登录成功！\n 你是：学生/教职工"));
        }


        //msg.exec();
    } else {
//        QMessageBox msg;
//        msg.setText(tr("用户名或密码错误！"));
//        msg.exec();

         //可以有错误提示音
        QMessageBox::warning(this, tr("警告！"),
                           tr("用户名或密码错误！"),
                           QMessageBox::Yes);
        ui->UserNameLineEdit->clear();
        ui->PasswordLineEdit->clear();
        ui->UserNameLineEdit->setFocus();
}

}
