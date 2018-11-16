#ifndef PLAYLISTITEMWIDGET_H
#define PLAYLISTITEMWIDGET_H

#include "Playlist.h"
#include <QWidget>

namespace Ui {
class PlaylistItemWidget;
}

class PlaylistItemWidget : public QWidget
{
        Q_OBJECT

    public:
        explicit PlaylistItemWidget(QWidget *parent = nullptr);
        ~PlaylistItemWidget();
        void setItem(const PlaylistItem& item);

    private:
        Ui::PlaylistItemWidget *ui;
        PlaylistItem item;
};

#endif // PLAYLISTITEMWIDGET_H
