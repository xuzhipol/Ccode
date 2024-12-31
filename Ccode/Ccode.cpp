#include "Ccode.h"
#include "ConvolutionalcodeClass.h"

Ccode::Ccode(QWidget *parent)     //整个图形用户界面的构造函数，进行界面设置和信号与槽的连接
    : QMainWindow(parent)
{
    ui.setupUi(this);

    connect(ui.pushButton, SIGNAL(clicked()), this, SLOT(encode_display()));
    connect(ui.pushButton_2, SIGNAL(clicked()), this, SLOT(rdecode_display()));
    connect(ui.pushButton_3, SIGNAL(clicked()), this, SLOT(ydecode_display()));
    connect(ui.pushButton_6, SIGNAL(clicked()), this, SLOT(File_input()));
}

Ccode::~Ccode()
{}

void Ccode::encode_display()     //槽函数定义，输出卷积码
{
    ConvolutionalcodeClass b;
    if (ui.lineEdit->text().size() == 0 && global.size() != 0)
    {
        QString k= b.Encode(global);
        ui.plainTextEdit->appendPlainText("Convolutional code: " + k);
        return;
    }
    QString a = b.Encode(ui.lineEdit->text());
    if (a.size() == 0)          //输出报错信息
    {
        ui.plainTextEdit->appendPlainText("Error, only 0 and 1 are allowed in the input sequence");
        return;
    }
    ui.plainTextEdit->appendPlainText("Convolutional code: "+a);
    return;
}

void Ccode::rdecode_display()
{
    ConvolutionalcodeClass b;
    if (ui.lineEdit->text().size() == 0 && global.size() != 0)
    {
        QString k = b.rDecode(global);
        ui.plainTextEdit->appendPlainText("Soft-decision decode: " + k);
        return;
    }
    QString a = b.rDecode(ui.lineEdit->text());
    if (a.size() == 0)          //输出报错信息
    {
        ui.plainTextEdit->appendPlainText("Error, only 0 and 1 are allowed in the input sequence and the length of the sequence must be an integer multiple of 3");
        return;
    }
    ui.plainTextEdit->appendPlainText("Soft-decision decode: " + a);
    return;
}

void Ccode::ydecode_display()
{
    ConvolutionalcodeClass b;
    if (ui.lineEdit->text().size()==0&&global.size() != 0)
    {
        QString k = b.yDecode(global);
        ui.plainTextEdit->appendPlainText("Hard-decision decode: " + k);
        return;
    }
    QString a = b.yDecode(ui.lineEdit->text());
    if (a.size() == 0)          //输出报错信息
    {
        ui.plainTextEdit->appendPlainText("Error,only 0 and 1 are allowed in the input sequence and the length of the sequence must be an integer multiple of 3");
        return;
    }
    ui.plainTextEdit->appendPlainText("Hard-decision decode: " + a);
    return;
}

void Ccode::File_input()
{
    QString curpath = QDir::currentPath();
    QString dlgtitle = "Open a file";
    QString filter = "* .h * .cpp;;* .txt";
    QString afilename = QFileDialog::getOpenFileName(this, dlgtitle, curpath, filter);
    if (afilename.isEmpty())
        return;

    QFileInfo fileinfo(afilename);
    QDir::setCurrent(fileinfo.absolutePath());
    QFile afile(afilename);
    if (!afile.exists())
        return;
    if (!afile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        ui.plainTextEdit->appendPlainText("File opening failed, please try again");
        return;
    }
    QTextStream astream(&afile);
    astream.setAutoDetectUnicode(true);
    global = astream.readAll();   //读取文件中的全部内容
    ui.plainTextEdit->appendPlainText("The file has been loaded");
    afile.close();
    return;
}
