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
        PlaylistItem getItem() const;

    private slots:
        void on_btnRemove_clicked();

    private:
        Ui::PlaylistItemWidget *ui;
        PlaylistItem item;

    signals:
        void itemSelectedToRemove();
};

#endif // PLAYLISTITEMWIDGET_H
