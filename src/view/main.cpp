#include "view.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    s21::View w;
    w.show();
    return a.exec();
}
