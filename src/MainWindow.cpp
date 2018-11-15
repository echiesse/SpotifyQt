#include "MainWindow.h"
#include "ui_mainwindow.h"

#include <QDesktopServices>
#include <QMessageBox>
#include <QString>

#include "Config.h"
#include "IOFunctions.h"
#include "request.h"
#include "searchwindow.h"

extern Config config;
extern Config appState;

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
    auto searchWindow = new SearchWindow(this);
    connect(
        searchWindow, &SearchWindow::trackChosen,
        this, &MainWindow::onTrackChosen
    );
    searchWindow->setWindowModality(Qt::ApplicationModal);
    searchWindow->show();
}


void MainWindow::onTrackChosen(const TrackInfo& track)
{
    ui->monitor->setText(track.show());
}

void MainWindow::testGetRequest()
{
    request req;
    QUrl url("http://example.com");
    auto res = req.get(url);
    ui->monitor->setText("Resposta:");
    ui->monitor->append(res);
    ui->monitor->append("Fim !!");
}


void MainWindow::on_btCancel_clicked()
{
    close();
}

