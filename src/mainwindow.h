#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include "SpotifyApiClient.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btOk_clicked();
    void on_btCancel_clicked();

private:
    Ui::MainWindow *ui;
    SpotifyApiClient spotify;
    void testGetRequest();
    void requestToken();
    QString queryTrack();
};

#endif // MAINWINDOW_H
