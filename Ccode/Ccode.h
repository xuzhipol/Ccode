#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Ccode.h"
#include<QPushButton>
#include<qfile.h>
#include<qdir.h>
#include <QFileInfo>
#include<qfiledialog.h>

class Ccode : public QMainWindow
{
    Q_OBJECT

public:
    Ccode(QWidget *parent = nullptr);
    ~Ccode();
    QString global;    //全局变量

private:
    Ui::CcodeClass ui;

private slots:   //自定义槽函数
    void encode_display();
    void rdecode_display();
    void ydecode_display();
    void File_input();
};
