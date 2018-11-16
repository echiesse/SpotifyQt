#include "SearchResultWidget.h"
#include "ui_SearchResultWidget.h"

SearchResultWidget::SearchResultWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SearchResultWidget)
{
    ui->setupUi(this);
}


SearchResultWidget::~SearchResultWidget()
{
    delete ui;
}


SearchResultWidget* SearchResultWidget::newFromTrack(const TrackInfo& track, QWidget* parent)
{
    auto widget = new SearchResultWidget(parent);
    widget->ui->lblTrackName->setText(track.getName());
    widget->ui->lblTrackArtist->setText(track.getArtist());
    widget->track = track;
    return widget;
}


void SearchResultWidget::on_pushButton_clicked()
{
    emit trackChosen(this->track);
}


void SearchResultWidget::setArtist(QString artistName)
{
    ui->lblTrackArtist->setText(artistName);
}


void SearchResultWidget::setTrackName(QString trackName)
{
    ui->lblTrackName->setText(trackName);
}
