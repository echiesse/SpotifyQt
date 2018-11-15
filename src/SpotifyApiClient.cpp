#include "SpotifyApiClient.h"

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

#include "request.h"
#include "util.h"
#include "TrackInfo.h"

SpotifyApiClient::SpotifyApiClient(QString clientId, QString clientSecret):
    clientId(clientId),
    clientSecret(clientSecret),
    m_isAuthenticated(false)
{
}


SpotifyApiClient::SpotifyApiClient(std::string clientId, std::string clientSecret):
    clientId(toQString(clientId)),
    clientSecret(toQString(clientSecret)),
    m_isAuthenticated(false)
{
}


// API calls:
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


QString SpotifyApiClient::queryTracks(
//map<string, string> SpotifyApiClient::queryTracks(
    QString query,
    QString type,
    QString market,
    int limit,
    int offset)
{
    auto results = map<string, string>();
    QUrl url("https://api.spotify.com/v1/search");
    request req;
    ParamMap params;
    params["q"] = query;
    params["type"] = type;
    params["market"] = market;
    params["limit"] = toQString(intToStr(limit));
    params["offset"] = toQString(intToStr(offset));

    ParamMap headers;
    headers["Accept"] = "application/json";
    headers["Content-Type"] = "application/json";
    headers["Authorization"] = tokenToHeader();

    auto content = req.get(url, headers, params);
    QString ret;

    // Parsear o json resultante:
    QJsonDocument doc = QJsonDocument::fromJson(content);
    QJsonObject jObject = doc.object();
    auto tracks = jObject["tracks"].toObject();
    auto items = tracks["items"].toArray();
    for(int i = 0; i < items.size(); ++i)
    {
        QJsonObject item = items[i].toObject();
        auto id = item["id"].toString();
        auto name = item["name"].toString();
        auto preview_url = item["preview_url"].toString();
        auto artists = item["artists"].toArray();
        auto artist = artists[0].toObject()["name"].toString();
        TrackInfo track(id, name, artist, preview_url);
        ret += track.show() + "\n\n";
    }

    return ret;
}


QString SpotifyApiClient::tokenToHeader()
{
    return "Bearer " + accessToken;
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
