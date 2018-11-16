#include "PlaylistItemWidget.h"
#include "ui_PlaylistItemWidget.h"

PlaylistItemWidget::PlaylistItemWidget(QWidget *parent) :
QWidget(parent),
ui(new Ui::PlaylistItemWidget)
{
    ui->setupUi(this);
}


PlaylistItemWidget::~PlaylistItemWidget()
{
    delete ui;
}


void PlaylistItemWidget::setItem(const PlaylistItem& item)
{
    this->item = item;
    ui->lblTrack->setText(item.getTrack().getName());
    ui->lblArtist->setText(item.getTrack().getArtist());
}

PlaylistItem PlaylistItemWidget::getItem() const
{
    return item;
}


void PlaylistItemWidget::on_btnRemove_clicked()
{
    emit itemSelectedToRemove();
}
