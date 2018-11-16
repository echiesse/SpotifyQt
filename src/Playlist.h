#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <QVector>
#include "TrackInfo.h"

class PlaylistItem
{
    private:
        TrackInfo track;
        QString localPath;

    public:
        PlaylistItem();
        PlaylistItem(TrackInfo track, QString localPath);
        TrackInfo getTrack() const;
        void setTrack(const TrackInfo& value);
        QString getLocalPath() const;
        void setLocalPath(const QString& value);
        bool operator==(const PlaylistItem& other);
};

class Playlist
{
    private:
        QVector<PlaylistItem> items;

    public:
        Playlist();
        void loadFromFile(QString path);
        void saveToFile(QString path);
        QString show();

        void addTrack(const TrackInfo& track);
        void removeItem(int index);
        void removeItem(const PlaylistItem& item);
        bool hasTrack(const TrackInfo& track);
        int count() const;
        PlaylistItem& operator[](int i);
        int indexOf(const PlaylistItem& item);
};

#endif // PLAYLIST_H
