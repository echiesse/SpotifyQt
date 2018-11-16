#include "Playlist.h"
#include "Functional.hpp"
#include "IOFunctions.h"
#include "request.h"
#include "util.h"

#include <QFile>
#include <fstream>
#include <string>
#include <vector>

using namespace ecs;


PlaylistItem::PlaylistItem()
{
}


PlaylistItem::PlaylistItem(TrackInfo track, QString localPath)
: track(track), localPath(localPath)
{
}


TrackInfo PlaylistItem::getTrack() const
{
    return track;
}


void PlaylistItem::setTrack(const TrackInfo& value)
{
    track = value;
}


QString PlaylistItem::getLocalPath() const
{
    return localPath;
}


void PlaylistItem::setLocalPath(const QString& value)
{
    localPath = value;
}


bool PlaylistItem::operator==(const PlaylistItem& other)
{
    return (
        localPath == other.localPath &&
        track == other.track
    );
}


//##############################################################################
Playlist::Playlist()
{

}


void Playlist::loadFromFile(QString path)
{
    const int ITEM_LINES = 5;
    vector<string> contents;
    loadLinesFromFile(&contents, path.toStdString());
    fmap(&contents, trim, contents);
    auto allLines = toQStringList(contents);

    while(allLines.size() >= ITEM_LINES)
    {
        auto lines = take(ITEM_LINES - 1, allLines);
        auto track = TrackInfo::createFromString(lines.join("\n"));
        auto localPath = allLines[ITEM_LINES - 1];

        allLines = drop(ITEM_LINES, allLines);
        items.push_back(PlaylistItem(track, localPath));
        while (allLines.size() > 0 && allLines[0].trimmed() == "")
        {
            allLines = drop(1, allLines);
        }
    }
}


void Playlist::saveToFile(QString path)
{
    saveTextToFile(show(), path);
}


QString Playlist::show()
{
    QString content;
    for(int i = 0; i < items.size(); ++i)
    {
        auto track = items[i].getTrack();
        content += track.show();
        content += "\n" + items[i].getLocalPath();
        content += "\n\n";
    }

    return content.trimmed();
}


void Playlist::addTrack(const TrackInfo& track)
{
    if (hasTrack(track)) return;

    auto fileName = track.getId() + ".mp3";
    if(track.getPreviewUrl() != "")
    {
        request req;
        auto previewData = req.get(track.getPreviewUrl());
        saveDataToFile(previewData, fileName);
    }
    else
    {
        fileName = "";
    }
    items.push_back(PlaylistItem(track, fileName));
}


void Playlist::removeItem(int index)
{
    if (index < 0 || index >= items.size()) return;

    auto path = items[index].getLocalPath();

    items.remove(index);

    // Defering so the file is not deleted in case of errors:
    QFile file (path);
    file.remove();
}


void Playlist::removeItem(const PlaylistItem& item)
{
    int index = indexOf(item);
    removeItem(index);
}


bool Playlist::hasTrack(const TrackInfo& track)
{
    return fany(
        [track](const PlaylistItem& item){return item.getTrack().getId() == track.getId();},
        items
    );
}


int Playlist::indexOf(const PlaylistItem& item)
{
    return items.indexOf(item);
}


int Playlist::count() const
{
    return items.size();
}


PlaylistItem& Playlist::operator[](int i)
{
    return items[i];
}
