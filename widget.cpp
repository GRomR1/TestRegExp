#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_lineEditRegExp_returnPressed()
{
    on_pushButton_clicked();
}

void Widget::on_lineEditString_returnPressed()
{
    on_pushButton_clicked();
}

void Widget::on_pushButton_clicked()
{
    QString str=ui->lineEditRegExp->text();
    str.replace("\\\\", "\\");
    QRegExp reg(str);
    str=ui->lineEditString->text();
    int pos = reg.indexIn(str);
    qDebug() << str << reg.pattern() << "\n"
             << reg.capturedTexts();
    int row = ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(row);
    ui->tableWidget->setItem(row, 0, new QTableWidgetItem("\""+str+"\""));
    ui->tableWidget->setItem(row, 1, new QTableWidgetItem("\""+reg.pattern()+"\""));
    ui->tableWidget->setItem(row, 2, new QTableWidgetItem(QString::number(pos)));
    ui->tableWidget->setItem(row, 3, new QTableWidgetItem(reg.cap(0)));
}

void Widget::on_lineEditRegExp_textChanged(const QString &arg1)
{
    QString str=arg1;
    str.replace("\\\\", "\\");
    checkString(QRegExp(str), ui->lineEditString->text());
}

void Widget::on_lineEditString_textChanged(const QString &arg1)
{
    QString str=ui->lineEditRegExp->text();
    str.replace("\\\\", "\\");
    checkString(QRegExp(str), arg1);
}

void Widget::checkString(QRegExp r, QString s)
{
//    qDebug() << "r" << r.pattern();
//    qDebug() << "s" << s;
    int pos=r.indexIn(s);
    if(pos==-1)
        ui->labelMatch->setText("<font color=red>"+QString::number(pos)+"|"+QString::number(r.indexIn(s))+"</font>");//not match
    else
        ui->labelMatch->setText("<font color=green>"+QString::number(pos)+"|"+QString::number(r.indexIn(s))+"</font>");
}
