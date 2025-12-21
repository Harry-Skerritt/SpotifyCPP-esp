//
// Created by Harry Skerritt on 21/12/2025.
//

#ifndef CLIENT_H
#define CLIENT_H

#pragma once
#include <string>
#include "spotify/auth/Auth.hpp"
#include "spotify/api/PlayerAPI.hpp"



namespace Spotify {
    class Client {
    // Funcs
    public:
        explicit Client(Auth& auth);
        ~Client() = default;

        [[nodiscard]] std::string getAccessToken() const;

        PlayerAPI player();

    private:

    // Vars
    public:
        const std::string BASE_API_URL = "https://api.spotify.com/v1/";

    private:
        Auth& m_auth;

    };

}



#endif //CLIENT_H
