#include "SpotifyApiClient.h"

#include <QJsonDocument>
#include <QJsonObject>

#include "request.h"
#include "util.h"

SpotifyApiClient::SpotifyApiClient(QString clientId, QString clientSecret):
    clientId(clientId),
    clientSecret(clientSecret),
    m_isAuthenticated(false)
{
}


void SpotifyApiClient::requestToken()
{
    request req;
    QUrl url("https://accounts.spotify.com/api/token");

    ParamMap headers;
    headers["Content-Type"] = "application/x-www-form-urlencoded";
    headers["Authorization"] = genAuthorization();

    ParamMap data;
    data["grant_type"] =  "client_credentials";

    auto content = req.post(url, headers, data);
    qDebug() << "Token: " << content;

    QJsonDocument doc = QJsonDocument::fromJson(content);
    QJsonObject jObject = doc.object();

    accessToken = jObject["access_token"].toString();
    m_isAuthenticated = true;
}


QByteArray SpotifyApiClient::genAuthorization()
{
    auto authString = clientId + ":" + clientSecret;
    QByteArray authorization("Basic ");
    authorization += toBase64(authString);
    return authorization;
}


bool SpotifyApiClient::isAuthenticated()
{
    return m_isAuthenticated;
}


QString SpotifyApiClient::getAccessToken()
{
    return accessToken;
}
