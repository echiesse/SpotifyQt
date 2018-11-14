#ifndef SPOTIFYAPICLIENT_H
#define SPOTIFYAPICLIENT_H

#include <QString>

class SpotifyApiClient
{
    public:
        SpotifyApiClient(QString clientId, QString clientSecret);
        void requestToken();
        bool isAuthenticated();

        QString getAccessToken();


    private:
        QString accessToken;
        QString clientId;
        QString clientSecret;
        bool m_isAuthenticated;

        QByteArray genAuthorization();

};

#endif // SPOTIFYAPICLIENT_H
