#ifndef SEARCHWINDOW_H
#define SEARCHWINDOW_H

#include <QMainWindow>
#include "SpotifyApiClient.h"
#include "TrackInfo.h"

namespace Ui {
class SearchWindow;
}

class SearchWindow : public QMainWindow
{
        Q_OBJECT

    public:
        explicit SearchWindow(QWidget *parent = nullptr);
        ~SearchWindow();

    private:
        Ui::SearchWindow *ui;
        SpotifyApiClient spotify;
        QString queryTrack();
        void requestToken();
        void testQueryTrack();

    private slots:
        void on_btOk_clicked();
        void on_trackChosen(const TrackInfo& track);

    signals:
        void trackChosen(const TrackInfo& track);
        //void trackChosen();

};

#endif // SEARCHWINDOW_H
