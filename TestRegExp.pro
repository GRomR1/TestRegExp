#-------------------------------------------------
#
# Проект для проверки регулярных выражений в Qt
# Используется класс QRegExp:
# http://doc.crossplatform.ru/qt/4.6.x/qregexp.html
# http://doc.qt.io/qt-5/qregexp.html
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TestRegExp
TEMPLATE = app

SOURCES += main.cpp\
        widget.cpp

HEADERS  += widget.h

FORMS    += widget.ui
