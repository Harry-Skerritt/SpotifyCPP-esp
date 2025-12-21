//
// Created by Harry Skerritt on 21/12/2025.
//

#include "spotify/core/Client.hpp"


Spotify::Client::Client(Auth& auth) : m_auth(auth) { }

std::string Spotify::Client::getAccessToken() const {
    return m_auth.getAccessToken();
}

// APIs

Spotify::PlayerAPI Spotify::Client::player() {
    return PlayerAPI(this);
}
