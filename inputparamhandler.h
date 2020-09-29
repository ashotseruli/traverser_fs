#ifndef PARAMHANDLER_H
#define PARAMHANDLER_H

#include<QStringList>
#include "algorythmType.h"

class InputParamHandler
{
public:
    static InputParamHandler& getInstance();
    bool parseParams(const QStringList& paramList);
    algorythmType getBypassType();
    QString getAddress();

private:
    InputParamHandler();
    InputParamHandler(const InputParamHandler&) = delete;
    InputParamHandler& operator=(InputParamHandler&) = delete;

    algorythmType m_type = algorythmType::inDepth;
    QString m_address = "";
};

#endif // PARAMHANDLER_H
