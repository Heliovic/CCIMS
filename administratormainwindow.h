#ifndef ADMINISTRATORMAINWINDOW_H
#define ADMINISTRATORMAINWINDOW_H

#include <QMainWindow>
#include <QDate>
#include <QTime>
#include <QTimer>

#include "administratorleadwindow.h"
#include "administratorscwindow.h"

#include "ccmis.h"

namespace Ui {
class AdministratorMainWindow;
}

class AdministratorMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit AdministratorMainWindow(CCMIS* c, QWidget *parent = 0);
    ~AdministratorMainWindow();

public slots:
    void showtime();
    void ShowNameSlot(QString);

private slots:
    //重新显示主界面：X，Y，宽，长
    void reshow(int,int,int,int);
    void on_BackButton_clicked();
    void on_ImportButton_clicked();
    void on_WorkButton_clicked();

signals:
    //返回主界面：X，Y，宽，长
    void BackMainWindow(int,int,int,int);
    void ShowNameSignal(QString);

private:
    Ui::AdministratorMainWindow *ui;
    CCMIS* mCCMIS;

    AdministratorLeadWindow *mALW;
    AdministratorSCWindow *mASCW;
};

#endif // ADMINISTRATORMAINWINDOW_H
