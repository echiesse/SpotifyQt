#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDesktopServices>
#include <QMessageBox>
#include <QString>

#include "clientid.h"
#include "Config.h"
#include "IOFunctions.h"
#include "request.h"

extern Config config;
extern Config appState;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    spotify(config["CLIENT_ID"], config["CLIENT_SECRET"])
{
    ui->setupUi(this);
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


void MainWindow::on_btOk_clicked()
{
    ui->monitor->setText("Pesquisando música:");
    auto res = queryTrack();
    ui->monitor->append(res);
    ui->monitor->append("");
    ui->monitor->append("Pesquisa concluida !");
}


QString MainWindow::queryTrack()
{
    if (!spotify.isAuthenticated())
    {
        requestToken();
    }
    auto res = spotify.queryTracks(
        "Dona roupa",
        "track",
        "BR"
    );
    return res;
}


void MainWindow::requestToken()
{
    spotify.requestToken();
    appState.setValue("SPOTIFY_TOKEN", spotify.getAccessToken().toStdString());
    appState.save();
}


void MainWindow::testGetRequest()
{
    request req;
    QUrl url(ui->inputUrl->text());
    auto res = req.get(url);
    ui->monitor->setText("Resposta:");
    ui->monitor->append(res);
    ui->monitor->append("Fim !!");
}


void MainWindow::on_btCancel_clicked()
{
    close();
}

