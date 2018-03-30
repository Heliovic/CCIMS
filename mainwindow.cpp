#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    mCCMIS = new CCMIS();

    //时间处理
    QTimer *timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(time_dispose()));
    timer->start(500);

    //正则表达式，只允许输入0~9
    QRegExp regx("[0-9]+$");
    QValidator *validator = new QRegExpValidator(regx, ui->UserNameLineEdit);
    ui->UserNameLineEdit->setValidator(validator);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::time_dispose()
{
    //月初刷新券
    mCCMIS->CouponFresh();
}

void MainWindow::on_pushButton_clicked()
{
    //进度条
    int i = 0;
    QProgressDialog *progressDlg = new
            QProgressDialog(QStringLiteral("正在载入文件......"),
                            QStringLiteral("等待"),0,10000,this);
    progressDlg->setWindowModality(Qt::WindowModal);
    //如果运行时间小于3，进度条就不会显示（测试时请置0）
    progressDlg->setMinimumDuration(3);
    progressDlg->setWindowTitle(QStringLiteral("请稍候"));
    while (i < 10000) {
        //这里可以添加进度前进的活动；初步构想是先获取文件大小，近似拟合时间，
        //当完成时直接置满结束，但暂时没看懂读文件线程怎么操作的
        i++;
        progressDlg->setValue(i);
    }

    //获取帐号
    int number = ui->UserNameLineEdit->text().toInt();
    mCCMIS->SetUserNumber(number);

    //判断用户名和密码条件
    if (mCCMIS->CheckPassword(ui->PasswordLineEdit->text().toStdString()))
    {
        if (number <= CCMIS::SUPERUSER_END) {
            //管理员
            AdministratorMainWindow *mAMW =
                    new AdministratorMainWindow(mCCMIS,this);
            mAMW->setGeometry(this->x(),this->y(),this->width(),this->height());
            mAMW->show();

//            Info_Table* info = new Info_Table(mCCMIS);
//            info->show();
        } else if (number <= CCMIS::SHOP_END) {
            if (number%100 == 0){
                //场所（总商家）
                PlaceMainWindow *mPMW = new PlaceMainWindow(mCCMIS,this);
                mPMW->setGeometry(this->x(),this->y(),this->width(),this->height());
                mPMW->show();
            }else {
                //商家
                ShopMainWindow *mSMW = new ShopMainWindow(mCCMIS,this);
                mSMW->setGeometry(this->x(),this->y(),this->width(),this->height());
                mSMW->show();
            }
        } else {
            //用户
            UserMainWindow *mUMW = new UserMainWindow(mCCMIS,this);
            mUMW->setGeometry(this->x(),this->y(),this->width(),this->height());
            mUMW->show();
        }
    this->hide();   //隐藏该窗口
    } else {
        //弹出警告窗口（可以有错误提示音）
        QMessageBox::warning(this, tr("警告！"),
                             tr("用户名或密码错误！"),
                             QMessageBox::Yes);

        //清空文字，目标回到用户名编辑
        ui->UserNameLineEdit->clear();
        ui->PasswordLineEdit->clear();
        ui->UserNameLineEdit->setFocus();
    }
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (QMessageBox::information
            (this, QObject::tr("关闭"),
             QObject::tr("退了就别回来了，这里到处都是BUG"),
             QObject::tr("好的"), QObject::tr("我再待一会"), 0, 1) == 0) {
        event->accept();
    }else {
        event->ignore();
    }
}
