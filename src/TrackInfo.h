#ifndef TRACKINFO_H
#define TRACKINFO_H

#include <QString>

class TrackInfo
{
    public:
        TrackInfo();
        TrackInfo(QString id, QString name, QString artist, QString previewUrl);
        static TrackInfo* newFromString(const QString& content);
        static TrackInfo createFromString(const QString& content);

        QString show() const;
        QString getId() const;
        QString getName() const;
        QString getArtist() const;
        QString getPreviewUrl() const;
        bool isEmpty() const;
        void loadFromString(const QString& content);
        bool operator==(const TrackInfo& other);

    private:
        QString id;
        QString name;
        QString artist;
        QString previewUrl;
};

#endif // TRACKINFO_H
