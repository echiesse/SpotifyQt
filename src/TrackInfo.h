#ifndef TRACKINFO_H
#define TRACKINFO_H

#include <QString>

class TrackInfo
{
    public:
        TrackInfo(QString id, QString name, QString artist, QString previewUrl);
        QString show();

    private:
        QString id;
        QString name;
        QString artist;
        QString previewUrl;
};

#endif // TRACKINFO_H
