//By Samuel PP Silveira, Centro Federal de Educação Tecnológica de Minas Gerais, 2017

#include "cvinputdata.h"
#include <QApplication>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon("icon.jpg"));
    CVInputData w;
    w.show();

    return a.exec();
}
