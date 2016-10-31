#include <QApplication>
#include "logserver.h"
#include <vld.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    CLogServer logServer;

    if(!logServer.Init())
        return 0;

     return a.exec();;
}
