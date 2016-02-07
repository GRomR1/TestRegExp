#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QRegExp>
#include <QString>
#include <QDebug>
#include <QDateTime>
#include <QFile>
#include <QTextCodec>
#include <QTableWidget>
#include <QByteArray>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void on_lineEditRegExp_returnPressed();
    void on_lineEditString_returnPressed();
    void on_pushButton_clicked();
    void on_lineEditRegExp_textChanged(const QString &arg1);
    void on_lineEditString_textChanged(const QString &arg1);
    void on_pushButtonSave_clicked();

    void on_pushButtonClear_clicked();

private:
    Ui::Widget *ui;

    void checkString(QRegExp r, QString s);
    bool saveToCsv(QString fname, QTableWidget *tbl);

};

#endif // WIDGET_H
