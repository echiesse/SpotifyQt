#include "SearchWindow.h"
#include "ui_searchwindow.h"
#include "SearchResultWidget.h"
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
    auto searchResult = new SearchResultWidget(ui->container);
    searchResult->setArtist("Michael Jackson");
    searchResult->setTrackName("Beat It");
    connect(
        searchResult, &SearchResultWidget::trackChosen,
        this, &SearchWindow::on_trackChosen
    );
    auto searchResult2 = new SearchResultWidget(ui->container);
    searchResult2->setArtist("Roupa Nova");
    searchResult2->setTrackName("Dona");
    searchResult2->move(0, searchResult->height());
    connect(
        searchResult2, &SearchResultWidget::trackChosen,
        this, &SearchWindow::on_trackChosen
    );
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
    if (!spotify.isAuthenticated())
    {
        requestToken();
    }
    auto tracks = spotify.queryTracks(
        "Dona roupa",
        "track",
        "BR"
    );

    QVector<QString> results;
    fmap(&results, [](TrackInfo t){return t.show();}, tracks);
    auto slist = toQStringList(results);

    return slist.join("\n\n") + "\n\n";
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
