#include "IOFunctions.h"
#include <windows.h>
#include "util.h"

namespace ecs
{

using namespace std;

IOStatus loadStringMap(
    map<string, string> *mapa,
    string fileName,
    string valueSeparator,
    string comentStr)
{
    string content;
    IOStatus ret = loadTextFromFile(&content, fileName);
    if(ret == STATUS_OK)
    {
        *mapa = toStringMap(content, valueSeparator, comentStr);
    }
    return ret;
}


IOStatus loadTextFromFile(string *text, string fileName)
{
    char *buffer;
    int fileSize;

    fstream file;
    file.open(fileName.c_str(),ios::in | ios::binary);
    if(file.fail())
    {
        return STATUS_ERROR_OPENING_FILE;
    }

    file.seekg(0, ios_base::end);
    fileSize = file.tellg();
    file.seekg(0, ios_base::beg);

    buffer = new char[fileSize+1];
    file.read(buffer, fileSize);
    if(file.fail()) // => Ocorreu um erro
    {
        return STATUS_ERROR_READING_FILE;
    }

    buffer[fileSize] = '\0';
    *text = buffer;
    delete[] buffer;
    file.close();
    return STATUS_OK;
}


IOStatus saveTextToFile(const string &text, string fileName)
{
    fstream file;
    file.open(fileName.c_str(), ios::out);
    if(file.fail())
    {
        return STATUS_ERROR_OPENING_FILE;
    }

    file << text;
    if(file.fail()) // => Ocorreu um erro
    {
        return STATUS_ERROR_READING_FILE;
    }

    file.close();
    return STATUS_OK;
}


//******************************************************************************
// Funções de utilidade para o módulo

IOStatus loadLinesFromFile(vector<string> *list, string fileName)
{
    string text;
    IOStatus status;
    status = loadTextFromFile(&text, fileName);
    if(status != STATUS_OK) return status;

    *list = splitLines(text);
    return STATUS_OK;
}


bool fileExists(string path)
{
	bool ret = false;
	WIN32_FIND_DATAA findData;
    if(FindFirstFileA((LPCSTR)path.c_str(), &findData) != INVALID_HANDLE_VALUE)
	{
		ret = true;
	}

	return ret;
}


bool dirExists(string path)
{
    return fileExists(path);
}


IOStatus createDir(string path)
{
    IOStatus ret = STATUS_OK;
    if(CreateDirectoryA((LPCSTR)path.c_str(), nullptr) == 0)
    {
        ret = STATUS_ERROR_CREATING_DIR;
    }
    return ret;
}


// Qt extensions:
IOStatus saveDataToFile(const QByteArray& data, QString fileName)
{
    fstream file(fileName.toStdString(), ios::out | ios::binary);
    if (!file.is_open()) return STATUS_ERROR_OPENING_FILE;

    file.write(data.data(), data.size());
    if (file.bad()) return STATUS_ERROR_SAVING_FILE;

    file.close();
    return STATUS_OK;
}


IOStatus saveTextToFile(const QString& text, QString fileName)
{
    return saveTextToFile(text.toStdString(), fileName.toStdString());
}

}
