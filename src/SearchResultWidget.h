#ifndef SEARCHRESULTWIDGET_H
#define SEARCHRESULTWIDGET_H

#include <QWidget>
#include "TrackInfo.h"

namespace Ui {
class SearchResultWidget;
}

class SearchResultWidget : public QWidget
{
        Q_OBJECT

    private:
        Ui::SearchResultWidget *ui;
        TrackInfo track;

    public:
        explicit SearchResultWidget(QWidget *parent = nullptr);
        ~SearchResultWidget();
        static SearchResultWidget* newFromTrack(
            const TrackInfo& track,
            QWidget* parent = nullptr
        );

        void setArtist(QString artistName);
        void setTrackName(QString trackName);

    signals:
        void trackChosen(const TrackInfo& track);

    private slots:
        void on_pushButton_clicked();
};

#endif // SEARCHRESULTWIDGET_H
