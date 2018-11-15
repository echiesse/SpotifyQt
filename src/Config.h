#ifndef COMOPT_CONFIG_H
#define COMOPT_CONFIG_H

#include <string>
#include <fstream>
#include <map>
#include "util.h"

using namespace std;

class Config
{
    private:
        string fileName;
        map<string, string> config;
        
        void load();

    public:
        Config(string configFilePath);
        ~Config();

        void loadFromFile(string path);
        void save();

        string show();
        string getValue(string key);
        void setValue(string key, string value);

        string operator[](string key);
};

#endif // ** COMOPT_CONFIG_H **
