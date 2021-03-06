#ifndef ADMINISTRATORADDDIALOG_H
#define ADMINISTRATORADDDIALOG_H

#include <QDialog>
#include <QCheckBox>
#include "ccims.h"
#include "aboutui.h"
#include "administratorscwindow.h"

namespace Ui {
class AdministratorAddDialog;
}

class AdministratorAddDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AdministratorAddDialog(CCIMS* c, int ismod, QWidget *parent = 0);
    ~AdministratorAddDialog();
    void setInOutNumEnable(bool state);

private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();
    void on_checkForCurTime_stateChanged(int arg1); //选择当前时间
    void on_dateEdit_dateChanged(const QDate &date);
    void on_timeEdit_2_timeChanged(const QTime &time);

    void on_Cur_Onum_Btn_stateChanged(int arg1);

    void on_Cur_Inum_Btn_stateChanged(int arg1);

private:
    Ui::AdministratorAddDialog *ui;
    CCIMS* mCCIMS;
    int isModify;
    QDate* mDate;
    QTime* mTime;
    QCheckBox* mCur_Inum_Btn;
    QCheckBox* mCur_Onum_Btn;
};

#endif // ADMINISTRATORADDDIALOG_H
