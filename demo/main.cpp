#include <QtGui/QApplication>
#include "mainview.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    mainView w;
    w.show();
    return a.exec();
}
