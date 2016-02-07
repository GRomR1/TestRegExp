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
    if(pos==-1)
        return;
    QStringList captures = reg.capturedTexts();
    qDebug() << str << reg.pattern() << "\n"
             << captures;
    int columns = ui->tableWidget->columnCount();
    int capCount = captures.size();
//    columns-=3;
    while(columns-3< capCount)
    {
        ui->tableWidget->insertColumn(columns);
        ui->tableWidget->setHorizontalHeaderItem(columns,
                                                 new QTableWidgetItem( tr("cap(%1)")
                                                                       .arg(columns-3)));
        columns=ui->tableWidget->columnCount();
    }
    int row = ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(row);
    ui->tableWidget->setItem(row, 0, new QTableWidgetItem("\""+str+"\""));
    ui->tableWidget->setItem(row, 1, new QTableWidgetItem("\""+reg.pattern()+"\""));
    ui->tableWidget->setItem(row, 2, new QTableWidgetItem(QString::number(pos)));
    int nCap=0;
    while(nCap<captures.size())
    {
        ui->tableWidget->setItem(row, nCap+3, new QTableWidgetItem(captures.at(nCap)));
        nCap++;
    }
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
        ui->labelMatch->setText("<font color=red>"+QString::number(pos)+"</font>");//not match
    else
        ui->labelMatch->setText("<font color=green>"+QString::number(pos)+"</font>");
}

void Widget::on_pushButtonSave_clicked()
{
    QString currTime=QDateTime::currentDateTime().toString("yyyy_MM_dd__hh_mm_ss");
    saveToCsv("Result__"+currTime.append(".csv"), ui->tableWidget);
}

bool Widget::saveToCsv(QString fname, QTableWidget *tbl)
{
    QFile file1(fname);
    if (!file1.open(QIODevice::WriteOnly))
    {
        qDebug() << "Ошибка открытия файла для записи";
        return false;
    }
    int rows = tbl->rowCount();
    int cols = tbl->columnCount();
    QString stringResultForCsv;
    QStringList strListHeader;
    for(int col=0; col<cols; col++)
    {
        strListHeader.append(tbl->horizontalHeaderItem(col)->text());
    }
    stringResultForCsv.append(strListHeader.join(';'));
    stringResultForCsv+="\n";
    for(int row=0; row<rows; row++)
    {
        for(int col=0; col<cols; col++)
        {
            QTableWidgetItem *ptwi = tbl->item(row, col);
            stringResultForCsv+=ptwi->text();
            if(col<cols-1)
                stringResultForCsv+=';';
        }
        stringResultForCsv+="\n";
    }
    QTextCodec *codec = QTextCodec::codecForName("Windows-1251");
    QByteArray ba = codec->fromUnicode(stringResultForCsv.toUtf8());
    file1.write(ba);
    file1.close();
    return true;
}

void Widget::on_pushButtonClear_clicked()
{
    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setColumnCount(3);
//    ui->tableWidget->setHorizontalHeaderItem(0,
//                                             new QTableWidgetItem("String"));
//    ui->tableWidget->setHorizontalHeaderItem(1,
//                                             new QTableWidgetItem("RegExp"));
//    ui->tableWidget->setHorizontalHeaderItem(2,
//                                             new QTableWidgetItem("Pos"));
}
