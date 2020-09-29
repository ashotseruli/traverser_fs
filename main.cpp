#include <QCoreApplication>
#include "inputparamhandler.h"
#include "traverser.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    if (!InputParamHandler::getInstance().parseParams(a.arguments()))
       qWarning("Input Params are incorrect!");
    else
    {
        Traverser traverser;
        traverser.traverse(InputParamHandler::getInstance().getAddress(),
                           InputParamHandler::getInstance().getBypassType());
    }
    return a.exec();
}
