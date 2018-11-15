#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include "SpotifyApiClient.h"
#include "TrackInfo.h"

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
    void onTrackChosen(const TrackInfo& track);

private:
    Ui::MainWindow *ui;
    void testGetRequest();
};

#endif // MAINWINDOW_H