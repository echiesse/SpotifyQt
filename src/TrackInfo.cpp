#include "TrackInfo.h"

TrackInfo::TrackInfo(QString id, QString name, QString artist, QString previewUrl)
    : id(id), name(name), artist(artist), previewUrl(previewUrl)
{

}


QString TrackInfo::show()
{
    QString ret;
    ret += id + "\n";
    ret += name + "\n";
    ret += previewUrl + "\n";
    ret += artist;
    return ret;
}
