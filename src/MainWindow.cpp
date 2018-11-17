#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QDesktopServices>
#include <QFile>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QMessageBox>
#include <QString>

#include "Config.h"
#include "IOFunctions.h"
#include "request.h"
#include "SearchWindow.h"
#include "PlaylistItemWidget.h"


extern Config config;
extern Config appState;

using namespace ecs;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    loadPlaylist();
}


MainWindow::~MainWindow()
{
    delete ui;
}


int showMessageBox(QString text)
{
    QMessageBox msgBox;
    msgBox.setText(text);
    msgBox.setInformativeText("Do you want to save your changes?");
    msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Save);
    return msgBox.exec();
}


void MainWindow::on_btSearch_clicked()
{
    auto searchWindow = new SearchWindow(this);
    connect(
        searchWindow, &SearchWindow::trackChosen,
        this, &MainWindow::onTrackChosen
    );
    searchWindow->setWindowModality(Qt::ApplicationModal);
    searchWindow->show();
}


void MainWindow::on_btPlay_clicked()
{
    auto player = new QMediaPlayer(this);
    auto pl = new QMediaPlaylist(player);
    for (int i = 0; i < playlist.count(); ++i)
    {
        auto path = playlist[i].getLocalPath();
        pl->addMedia(QUrl::fromLocalFile(path));
    }
    pl->setCurrentIndex(1);
    player->setVolume(50);
    qDebug() << "Playing ..." ;
    player->play();

    delete player;
    qDebug() << "Playlist finished" ;
}


void MainWindow::onMediaError(QMediaPlayer::Error error)
{
    qDebug() << error;
}


void MainWindow::onTrackChosen(const TrackInfo& track)
{
    playlist.addTrack(track);
    savePlaylist();
    showPlaylist();
}


void MainWindow::testGetRequest()
{
#ifdef ECS_DEBUG
    request req;
    QUrl url("http://example.com");
    auto res = req.get(url);
    ui->monitor->setText("Resposta:");
    ui->monitor->append(res);
    ui->monitor->append("Fim !!");
#endif
}


void MainWindow::savePlaylist()
{
    auto path = config["PLAYLIST_FILE"];
    playlist.saveToFile(toQString(path));
}


void MainWindow::loadPlaylist()
{
    auto path = config["PLAYLIST_FILE"];
    if(! fileExists(path))
    {
        saveTextToFile("", path);
    }
    playlist.loadFromFile(QString(path.c_str()));
    showPlaylist();
}


void MainWindow::showPlaylist()
{
#ifdef ECS_DEBUG
    ui->monitor->setText(playlist.show());
#endif

    removeAllChildren(ui->playlist->widget());
    for (int i = 0; i < playlist.count(); ++i)
    {
        auto item = playlist[i];
        auto widget = new PlaylistItemWidget(ui->playlist->widget());
        widget->setItem(item);
        widget->move(0, i * widget->height());
        widget->show();
        connect(
            widget, &PlaylistItemWidget::itemSelectedToRemove,
            this, &MainWindow::removePlaylistItem
        );
    }
}


void MainWindow::removePlaylistItem()
{
    auto widget = qobject_cast<PlaylistItemWidget*>(sender());
    auto item = widget->getItem();

    playlist.removeItem(item);
    deleteWidget(widget);

    savePlaylist();
    showPlaylist();
}
