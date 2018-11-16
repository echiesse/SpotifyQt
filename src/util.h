#ifndef UTIL_H
#define UTIL_H

#include <list>
#include <map>
#include <string>
#include <vector>

#include <QByteArray>
#include <QString>
#include <QVector>

using namespace std;

//typedef vector<string>     VectorStrings;
//typedef list<string>       ListaStrings;
typedef map<string,string> StringMap;
typedef map<string,string>::iterator StringMapIterator;
typedef string(strOperator)(string str);

QByteArray toBase64(QString string);
QString toQString(string str);
QStringList toQStringList(const QVector<QString>& sVector);
QStringList toQStringList(const vector<string>& sVector);

string toUpper(string str);
string toLower(string str);
string trim(string str);
vector<string> split(string str, string sep);
vector<string> splitLines(string str);
map<string, string> toStringMap(string keyValueList, string valueSeparator, string comentStr);
string intToStr(int val);
int strToInt(string str);


//##############################################################################
// Templates:

//******************************************************************************
// Conversão de formato:

template <typename T>
vector<T> listToVector(list<T> lista)
{
    vector<T> ret;
    typename list<T>::iterator it;
    for(it=lista.begin(); it!=lista.end(); ++it)
    {
        ret.push_back(*it);
    }
    return ret;
}

template <typename T>
list<T> vectorToList(vector<T> vet)
{
    list<T> ret;
    size_t i;
    for(i=0; i<vet.size(); ++i)
    {
        ret.push_back(vet[i]);
    }
    return ret;
}

#endif // UTIL_H
