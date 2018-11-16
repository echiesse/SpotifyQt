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
        bool hasTrack(const TrackInfo& track);
};

#endif // PLAYLIST_H
