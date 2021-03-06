#include "usermainwindow.h"
#include "ui_usermainwindow.h"
#include <QDebug>

UserMainWindow::UserMainWindow(CCIMS* c, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::UserMainWindow)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose,true);

    mCCIMS = c;

    //时间处理
    QTimer *timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(time_dispose()));
    timer->start(500);

    //基本信息展示
    ui->UserName->setText(mCCIMS->GetCurrentUserName());
    QString Money = "余额：" + QString::number
            (double(mCCIMS->GetUserByNum(mCCIMS->GetUserNum())->balance)/100,'f',2)
            + "元";
    ui->Money->setText(Money);
    QString Coupon = "劵：" + QString::number
            (double(mCCIMS->GetUserByNum(mCCIMS->GetUserNum())->coupon)/100,'f',2)
            + "元";
    ui->Coupon->setText(Coupon);

    //图片导入
    QIcon icon;
    std::string str = mCCIMS->FilenameCorrect
            (mCCIMS->BACKBUTTON_PICTURE_NAME).toStdString();
    const char* address = str.c_str();  //转地址QString到char*
    icon.addFile(tr(address));
    ui->BackButton->setIcon(icon);

}

UserMainWindow::~UserMainWindow()
{
    delete ui;
}

QString UserMainWindow::str2qstr(const string str)
{
    return QString::fromLocal8Bit(str.data());
}
string UserMainWindow::qstr2str(const QString qstr)
{
    QByteArray cdata = qstr.toLocal8Bit();
    return string(cdata);
}

void UserMainWindow::time_dispose()
{
    ui->Time->display(AboutUI::ShowDateTime());
}

void UserMainWindow::on_BackButton_clicked()
{
    parentWidget()->setGeometry(this->x(),this->y(),this->width(),this->height());
    parentWidget()->show();
    this->close();
}

void UserMainWindow::on_SearchButton_clicked()
{
    //进度条展示
    QProgressDialog *progressDlg = new
            QProgressDialog(QStringLiteral("正在载入文件......"),
                            QStringLiteral("等待"),0,mCCIMS->GuessTotalNumber,this);
    if(!AboutUI::PDlg(progressDlg,mCCIMS,mCCIMS->GuessTotalNumber)){
        return;
    }

    //产生界面
    UserSearchWindow *mUSW = new UserSearchWindow(mCCIMS,this);
    mUSW->setGeometry(this->x(),this->y(),this->width(),this->height());
    mUSW->show();
    this->hide();
}

void UserMainWindow::on_WorkButton_clicked()
{
    UserRechargeWindow *mURW = new UserRechargeWindow(mCCIMS,this);
    mURW->setGeometry(this->x(),this->y(),this->width(),this->height());
    mURW->show();
    this->hide();
}

void UserMainWindow::refreshUi()
{
    ui->UserName->setText(mCCIMS->GetCurrentUserName());
    QString Money = "余额：" + QString::number
            (double(mCCIMS->GetUserByNum(mCCIMS->GetUserNum())->balance)/100,'f',2)
            + "元";
    ui->Money->setText(Money);
    QString Coupon = "劵：" + QString::number
            (double(mCCIMS->GetUserByNum(mCCIMS->GetUserNum())->coupon)/100,'f',2)
            + "元";
    ui->Coupon->setText(Coupon);
}
