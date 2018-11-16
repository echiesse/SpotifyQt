#include "Playlist.h"
#include "Functional.hpp"
#include "IOFunctions.h"
#include "request.h"
#include "util.h"

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


//void Playlist::removeTrack(const TrackInfo& track)
//{
//    if (hasTrack(track));
//}


void Playlist::removeItem(int index)
{
    if (index >= items.size()) return;

    QVector<PlaylistItem>::iterator pos = items.begin();
    for(int i = 0; i < items.size(); ++i)
    {
        ++pos;
    }
    items.erase(pos);
}


bool Playlist::hasTrack(const TrackInfo& track)
{
    return fany(
        [track](const PlaylistItem& item){return item.getTrack().getId() == track.getId();},
        items
    );
}

