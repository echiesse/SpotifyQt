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

void SearchResultWidget::on_pushButton_clicked()
{
    emit trackChosen(TrackInfo(
        "",
        ui->lblTrackName->text(),
        ui->lblTrackArtist->text(),
        ""
    ));
}


void SearchResultWidget::setArtist(QString artistName)
{
    ui->lblTrackArtist->setText(artistName);
}


void SearchResultWidget::setTrackName(QString trackName)
{
    ui->lblTrackName->setText(trackName);
}
