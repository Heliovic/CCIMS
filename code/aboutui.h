#ifndef ABOUTUI_H
#define ABOUTUI_H

#include <QString>
#include <QDateTime>
#include <QProgressDialog>

#include "ccims.h"

class AboutUI
{
public:
    AboutUI();

    static QString ShowDateTime();  //输出当前日期时间
    static bool PDlg (QProgressDialog*, CCIMS*, unsigned int);   //进度条显示
};

#endif // ABOUTUI_H
