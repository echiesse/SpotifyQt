#ifndef __ECS_IO_FUNCTIONS_H__
#define __ECS_IO_FUNCTIONS_H__

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <list>

#include "util.h"

namespace ecs
{

using namespace std;


enum IOStatus
{
    STATUS_OK,
    STATUS_ERROR_OPENING_FILE,
    STATUS_ERROR_READING_FILE,
    STATUS_ERROR_SAVING_FILE,
    STATUS_ERROR_FILE_NOT_FOUND,
    STATUS_ERROR_ALOC_MEMORIA,
    STATUS_ERROR_CREATING_DIR,
};

using namespace std;

// Interface pública:

IOStatus loadStringMap(StringMap *mapa, string fileName, string separator, string comentStr);
IOStatus loadTextFromFile(string *text, string fileName);
IOStatus saveTextToFile(const string &text, string fileName);
IOStatus createDir(string nomeDir);
IOStatus loadLinesFromFile(vector<string> *list, string fileName);
bool fileExists(string path);
bool dirExists(string path);


} /** namespace ecs **/

#endif // ** __ECS_IO_FUNCTIONS_H__ **
