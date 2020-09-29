#include <QDir>
#include "inputparamhandler.h"
#include "algorythmType.h"


InputParamHandler::InputParamHandler()
{
}

InputParamHandler& InputParamHandler::getInstance()
{
    static InputParamHandler instance;
    return instance;
}

bool InputParamHandler::parseParams(const QStringList &paramList)
{
    if (paramList.isEmpty() || paramList.count() == 1)
        return false;
    QStringList::const_iterator it = paramList.cbegin();
    it++;
    for(; it != paramList.cend(); it++)
    {
        if (*it == "-algorythm")
        {
            it++;
            bool isOk = true;
            int type = it->toInt(&isOk);
            if (isOk && type > static_cast<int>(algorythmType::unknown)
                     && type < static_cast<int>(algorythmType::count))
            {
                m_type = static_cast<algorythmType>(type);
                continue;
            }
            else
            {
                m_type = algorythmType::unknown;
                qWarning("algorythm is unknown");
            }
        }
        else
        {
            m_address = *it;
            QDir dir(m_address);
            if (!dir.exists())
            {
                qWarning("path is not correct!");
                return false;
            }
        }
    }
    return true;
}

algorythmType InputParamHandler::getBypassType()
{
    return m_type;
}

QString InputParamHandler::getAddress()
{
    return m_address;
}



