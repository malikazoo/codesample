#include "mainwindow.h"
#include <QApplication>
#include "filterregister.h"

//FilterRegister registry;

#include "filterfactory.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
