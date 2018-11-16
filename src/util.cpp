#include "util.h"
#include "Functional.hpp"

#include <QByteArray>
#include <QString>
#include <sstream>
#include <string>


QByteArray toBase64(QString string)
{
    QByteArray ba;
    ba.append(string);
    return ba.toBase64();
}


QString toQString(string str)
{
    return QString(str.c_str());
}


QStringList toQStringList(const QVector<QString>& sVector)
{
    QStringList ret;
    for (int i = 0; i < sVector.size(); ++i)
    {
        ret.append(sVector[i]);
    }
    return ret;
}


QStringList toQStringList(const vector<string>& sVector)
{
    QStringList ret;
    for (size_t i = 0; i < sVector.size(); ++i)
    {
        ret.push_back(sVector[i].c_str());
    }
    return ret;
}


string toUpper(string str)
{
    size_t length = str.size();
    size_t i;

    for(i = 0; i < length; ++i)
    {
        str[i] = static_cast<char>(toupper(str[i]));
    }
    return str;
}


string toLower(string str)
{
    size_t length = str.size();
    size_t i;

    for(i = 0; i < length; ++i)
    {
        str[i] = static_cast<char>(tolower(str[i]));
    }
    return str;
}


string trim(string str)
{
    size_t i = 0;
    while(!isgraph(str[i]) && i < str.size())
    {
        ++i;
    }
    if(i == str.size())
    {
        str = "";
        return str;
    }

    size_t j = 0;
    while(i < str.size())
    {
        str[j] = str[i];
        ++i;
        ++j;
    }
    str.resize(j);

    if(j == 0)return str;

    --j;
    while(!isgraph(str[j]))
    {
        --j;
    }
    ++j;
    str.resize(j);
    return str;
}


vector<string> split(string str, string sep)
{
    vector<string> ret;
    size_t length;

    size_t ini = 0;
    size_t end = 0;
    while(end != string::npos)
    {
        end = str.find(sep,ini);
        length = (end == string::npos) ? end : (end - ini);
        ret.push_back(str.substr(ini, length));
        ini = end + 1;
    }
    return ret;
}


vector<string> splitLines(string str)
{
    return split(str, "\n");
}


map<string, string> toStringMap(string keyValueList, string valueSeparator, string comentStr)
{
    string key;
    string value;
    string line;
    map<string, string> ret;

    vector<string> temp = split(keyValueList, "\n");
    fmap(&temp, trim, temp);

    size_t separatorPos;
    vector<string>::iterator it;
    for(it = temp.begin(); it != temp.end(); ++it)
    {
        line = *it;

        // Remover comentários:
        size_t posComent = line.find(comentStr);
        line = line.substr(0, posComent);
        // Ignora a line se estiver comentada:
        if(trim(line).empty()) continue;

        // Achar o separador. Ignorar a line se não encontrar:
        separatorPos = line.find(valueSeparator);
        if(separatorPos == string::npos) continue;

        // Montar o mapa:
        key = trim(line.substr(0, separatorPos));
        value = trim(line.substr(separatorPos + 1));
        ret[key] = value;
    }

    return ret;
}


//******************************************************************************
// Conversão de tipos:

string intToStr(int val)
{
    stringstream sStr;
    sStr << val;
    return sStr.str();
}


int strToInt(string str)
{
    return strtol(str.c_str(), nullptr, 10);
}


void removeAllChildren(QWidget* widget, QString objectName)
{
    while(QWidget* child = widget->findChild<QWidget*>())
    {
        if (objectName == "" || child->objectName() == objectName)
        {
            deleteWidget(child);
        }
    }
}

void deleteWidget(QWidget* widget)
{
    widget->setParent(nullptr);
    delete widget;
}
