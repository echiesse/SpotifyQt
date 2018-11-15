#ifndef SPOTIFYAPICLIENT_H
#define SPOTIFYAPICLIENT_H

#include <QString>
#include <string>
#include <map>

using namespace std;

class SpotifyApiClient
{
    public:
        SpotifyApiClient(QString clientId, QString clientSecret);
        SpotifyApiClient(string clientId, string clientSecret);
        void requestToken();
        bool isAuthenticated();

        QString getAccessToken();
        //map<string, string> queryTracks(
        QString queryTracks(
            QString query,
            QString type,
            QString market,
            int limit = 10,
            int offset = 0
        );

    private:
        QString accessToken;
        QString clientId;
        QString clientSecret;
        bool m_isAuthenticated;

        QByteArray genAuthorization();
        QString tokenToHeader();

};

#endif // SPOTIFYAPICLIENT_H
