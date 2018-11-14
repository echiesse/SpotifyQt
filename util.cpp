#include "util.h"

#include <QByteArray>
#include <QString>


QByteArray toBase64(QString string)
{
    QByteArray ba;
    ba.append(string);
    return ba.toBase64();
}
