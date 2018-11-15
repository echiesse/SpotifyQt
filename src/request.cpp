#include <windows.h>
#include <sstream>
#include <string>

#include <QEventLoop>

#include "request.h"

using std::string;
using std::stringstream;

request::request() :
    manager(this),
    isFinished(false),
    hasError(false)
{
}


void request::reset()
{
    hasError = false;
    isFinished = false;
}


QByteArray request::get(QUrl url)
{
    return get(url, emptyHeader(), ParamMap());
}


QByteArray request::get(QUrl url, ParamMap headers, ParamMap params)
{
    reset();
    QNetworkReply* reply;
    QUrlQuery queryString = buildPostData(params); // TODO: buildPostData tem que mudar de nome <<<<<
    QString qs = queryString.toString(QUrl::FullyEncoded).toUtf8();
    url.setQuery(qs);
    QNetworkRequest request = buildRequest(url, headers);
    reply = manager.get(request);
    return processReply(reply);
}


QByteArray request::post(QUrl url, ParamMap headers, ParamMap data)
{
    reset();
    QNetworkReply* reply;
    QNetworkRequest request = buildRequest(url, headers);
    QUrlQuery postData = buildPostData(data);
    reply = manager.post(
        request,
        postData.toString(QUrl::FullyEncoded).toUtf8()
    );
    return processReply(reply);
}


QByteArray request::processReply(QNetworkReply *reply)
{
    QEventLoop waitLoop;
    connect(
        reply, &QNetworkReply::finished,
        &waitLoop, &QEventLoop::quit
    );
    waitLoop.exec();

    QByteArray ret;

    int errorCode = reply->error();
    if (errorCode != QNetworkReply::NoError)
    {
        QString msg("errorString: ");
        msg += reply->errorString();
        qDebug() << msg;
        return msg.toUtf8();
    }
    else
    {
        qint32 httpStatusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();

        if (httpStatusCode >= 200 && httpStatusCode < 300) // OK
        {
            ret = handleSuccess(reply);
        }
        else if (httpStatusCode >= 300 && httpStatusCode < 400) // 300 Redirect
        {
            ret = handleRedirect(reply);
        }
        else if (httpStatusCode >= 400 && httpStatusCode < 500) // 400 Error
        {
            ret = handle400(reply);
        }
        else if (httpStatusCode >= 500 && httpStatusCode < 600) // 500 Internal Server Error
        {
            ret = handle500(reply);
        }
        else
        {
            qDebug() << "Status code invalid! " << httpStatusCode;
        }
    }

    delete reply;

    return ret;
}


QByteArray request::handleSuccess(QNetworkReply* reply)
{
    return reply->readAll();
}


QByteArray request::handleRedirect(QNetworkReply* reply)
{
    QUrl relativeUrl = reply->attribute(QNetworkRequest::RedirectionTargetAttribute).toUrl();
    QUrl redirectUrl = reply->url().resolved(relativeUrl);
    return this->get(redirectUrl);
}


QByteArray request::handle400(QNetworkReply* reply)
{
    auto statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    qDebug() << "handle400: " << statusCode; //<<<<<
    stringstream buffer;
    buffer << statusCode << " Error!";
    return QByteArray(buffer.str().c_str());
}


QByteArray request::handle500(QNetworkReply* reply)
{
    auto statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    qDebug() << "handle500: " << statusCode; //<<<<<
    stringstream buffer;
    buffer << statusCode << " Error!";
    return buffer.str().c_str();
}


QUrlQuery request::buildPostData(ParamMap data)
{
    QUrlQuery postData;
    ParamMapIterator iterator(data);

    while (iterator.hasNext())
    {
        iterator.next();
        postData.addQueryItem(iterator.key(), iterator.value());
    }
    return postData;
}


QNetworkRequest request::buildRequest(QUrl url)
{
    return buildRequest(url, emptyHeader());
}


QNetworkRequest request::buildRequest(QUrl url, ParamMap headers)
{
    QNetworkRequest request;
    request.setUrl(url);

    if (!headers.isEmpty())
    {
        ParamMapIterator iterator(headers);
        while (iterator.hasNext())
        {
            iterator.next();
            request.setRawHeader(
                QByteArray::fromStdString(iterator.key().toStdString()),
                QByteArray::fromStdString(iterator.value().toStdString())
            );
        }
    }

    return request;
}


ParamMap request::emptyHeader()
{
    return ParamMap();
}
