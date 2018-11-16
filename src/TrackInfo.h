#ifndef TRACKINFO_H
#define TRACKINFO_H

#include <QString>

class TrackInfo
{
    public:
        TrackInfo();
        TrackInfo(QString id, QString name, QString artist, QString previewUrl);
        QString show() const;
        QString getId() const;
        QString getName() const;
        QString getArtist() const;
        QString getPreviewUrl() const;
        bool isEmpty() const;

    private:
        QString id;
        QString name;
        QString artist;
        QString previewUrl;
};

#endif // TRACKINFO_H
