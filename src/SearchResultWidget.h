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

    public:
        explicit SearchResultWidget(QWidget *parent = nullptr);
        ~SearchResultWidget();
        void setArtist(QString artistName);
        void setTrackName(QString trackName);

    private:
        Ui::SearchResultWidget *ui;

    signals:
        void trackChosen(const TrackInfo& track);

    private slots:
        void on_pushButton_clicked();
};

#endif // SEARCHRESULTWIDGET_H
