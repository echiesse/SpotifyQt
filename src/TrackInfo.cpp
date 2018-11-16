#include "TrackInfo.h"

#include <QStringList>

TrackInfo::TrackInfo(QString id, QString name, QString artist, QString previewUrl)
    : id(id), name(name), artist(artist), previewUrl(previewUrl)
{
}


TrackInfo::TrackInfo(): id(""), name(""), artist(""), previewUrl("")
{
}


QString TrackInfo::show() const
{
    QString ret;
    ret += id + "\n";
    ret += name + "\n";
    ret += previewUrl + "\n";
    ret += artist;
    return ret;
}


void TrackInfo::loadFromString(const QString& content)
{
    auto lines = content.trimmed().split("\n");
    id = lines[0].trimmed();
    name = lines[1].trimmed();
    previewUrl = lines[2].trimmed();
    artist = lines[3].trimmed();
}


TrackInfo* TrackInfo::newFromString(const QString& content)
{
    auto ret = new TrackInfo();
    ret->loadFromString(content);
    return ret;
}


TrackInfo TrackInfo::createFromString(const QString& content)
{
    TrackInfo ret;
    ret.loadFromString(content);
    return ret;
}


QString TrackInfo::getId() const
{
    return id;
}


QString TrackInfo::getName() const
{
    return name;
}


QString TrackInfo::getArtist() const
{
    return artist;
}


QString TrackInfo::getPreviewUrl() const
{
    return previewUrl;
}


bool TrackInfo::isEmpty() const
{
    return (
        id == "" &&
        name == "" &&
        artist == "" &&
        previewUrl == ""
    );
}


