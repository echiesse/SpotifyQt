#ifndef REQUESTS_H
#define REQUESTS_H

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QString>
#include <QUrlQuery>

typedef QMap<QString, QString> ParamMap;
typedef QMapIterator<QString, QString> ParamMapIterator;

class request : public QObject
{
    Q_OBJECT

    private:
        QNetworkAccessManager manager;
        bool isFinished;
        bool hasError;
        void reset();
        QByteArray processReply(QNetworkReply *reply);
        QByteArray handleSuccess(QNetworkReply* reply);
        QByteArray handleRedirect(QNetworkReply* reply);
        QByteArray handle400(QNetworkReply* reply);
        QByteArray handle500(QNetworkReply* reply);
        QNetworkRequest buildRequest(QUrl url, ParamMap headers);
        QNetworkRequest buildRequest(QUrl url);
        QUrlQuery buildPostData(ParamMap data);

    public:
        request();
        QByteArray get(QUrl url, ParamMap headers);
        QByteArray get(QUrl url);
        QByteArray post(QUrl url, ParamMap headers, ParamMap data);
        static ParamMap emptyHeader();

};

#endif // REQUESTS_H
