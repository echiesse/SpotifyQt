#include "TrackInfo.h"

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
