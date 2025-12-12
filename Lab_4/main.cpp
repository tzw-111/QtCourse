#include "mastarview.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MastarView w;
    w.show();
    return a.exec();
}
