#include "SearchWindow.h"
#include "ui_SearchWindow.h"
#include "Config.h"

#include "Functional.hpp"

extern Config config;
extern Config appState;


SearchWindow::SearchWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SearchWindow),
    spotify(config["CLIENT_ID"], config["CLIENT_SECRET"])
{
    ui->setupUi(this);
}


SearchWindow::~SearchWindow()
{
    delete ui;
}


void SearchWindow::on_btOk_clicked()
{
    this->close();
}


QString SearchWindow::queryTrack()
{
    return "Implement me";
}


void SearchWindow::requestToken()
{
    spotify.requestToken();
    appState.setValue("SPOTIFY_TOKEN", spotify.getAccessToken().toStdString());
    appState.save();
}


void SearchWindow::testQueryTrack()
{
    //ui->monitor->setText("Pesquisando música:");
    //auto res = queryTrack();
    //ui->monitor->append(res);
    //ui->monitor->append("");
    //ui->monitor->append("Pesquisa concluida !");
}


void SearchWindow::on_trackChosen(const TrackInfo& track)
{
    emit trackChosen(track);
    close();
}

void SearchWindow::on_btSearch_clicked()
{
    clearResults();

    if (!spotify.isAuthenticated())
    {
        requestToken();
    }

    auto tracks = spotify.queryTracks(
        ui->inputSearch->text(),
        "track",
        "BR"
    );

    showSearchResults(tracks);
}


SearchResultWidget* SearchWindow::widgetFromTrack(const TrackInfo& track)
{
    auto widget = SearchResultWidget::newFromTrack(track, ui->resultsContainer);
    auto artistName = track.getArtist();
    widget->setArtist(artistName);
    widget->setTrackName(track.getName());
    connect(
        widget, &SearchResultWidget::trackChosen,
        this, &SearchWindow::on_trackChosen
    );
    return widget;
}


void SearchWindow::showSearchResults(const QVector<TrackInfo>& tracks)
{
    QVector<SearchResultWidget*> widgets;
    fmap(
        &widgets,
        [this](const TrackInfo& track){return this->widgetFromTrack(track);},
        tracks
    );

    for (int i = 0; i < widgets.count(); ++i)
    {
        auto widget = widgets[i];
        widget->move(0, i * widget->height());
        widget->show();
    }
}


void SearchWindow::clearResults()
{
    while(QWidget* widget = ui->resultsContainer->findChild<QWidget*>())
    {
        widget->setParent(nullptr);
        delete widget;
    }
}
