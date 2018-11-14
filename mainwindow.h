#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

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

    void testGetRequest();
    void requestToken();
};

#endif // MAINWINDOW_H
