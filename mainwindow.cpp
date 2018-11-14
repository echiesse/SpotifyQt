#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDesktopServices>
#include <QMessageBox>
#include <QString>

#include "clientid.h"
#include "request.h"
#include "SpotifyApiClient.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
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
    requestToken();
}


void MainWindow::requestToken()
{
    SpotifyApiClient client(CLIENT_ID, CLIENT_SECRET);
    client.requestToken();
    ui->monitor->setText("Resposta:");
    ui->monitor->append(QString("Token = ") + client.getAccessToken());
    ui->monitor->append("Fim !!");
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

