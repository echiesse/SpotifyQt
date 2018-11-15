#ifndef SEARCHWINDOW_H
#define SEARCHWINDOW_H

#include <QMainWindow>
#include "SearchResultWidget.h"
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
        SearchResultWidget* widgetFromTrack(const TrackInfo& track);
        void showSearchResults(const QVector<TrackInfo>& tracks);

    private slots:
        void on_btOk_clicked();
        void on_trackChosen(const TrackInfo& track);

        void on_btSearch_clicked();

    signals:
        void trackChosen(const TrackInfo& track);
        //void trackChosen();

};

#endif // SEARCHWINDOW_H
