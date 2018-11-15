#include "Config.h"
#include "IOFunctions.h"

using namespace ecs;

Config::Config(string configFilePath)
{
    if (! fileExists(configFilePath))
    {
        saveTextToFile("", configFilePath);
    }
    this->fileName = configFilePath;
    load();
}


Config::~Config()
{
}


void Config::load()
{
    string content;
    loadTextFromFile(&content, fileName);
    config = toStringMap(content, "=", "#");
}


void Config::loadFromFile(string path)
{
    this->fileName = path;
    load();
}


void Config::save()
{
    saveTextToFile(show(), fileName);
}


string Config::show()
{
    string content;
    for (auto it = config.begin(); it != config.end(); ++it)
    {
        content += it->first + " = " + it->second + "\n";
    }
    return content;
}


string Config::getValue(string key)
{
    load();
    string ret;
    StringMap::const_iterator it = config.find(key);
    if(it == config.end())
    {
        ret = "";
    }
    else
    {
        ret = it->second;
    }
    return ret;
}


void Config::setValue(string key, string value)
{
    config[key] = value;
}


string Config::operator[](string key)
{
    return getValue(key);
}
