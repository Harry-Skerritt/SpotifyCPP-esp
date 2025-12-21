//
// Created by Harry Skerritt on 21/12/2025.
//

#ifndef PLAYERAPI_H
#define PLAYERAPI_H

#pragma once
#include <string>
#include <optional>
#include "spotify/util/Types.h"

namespace Spotify {

    class Client;

    class PlayerAPI {
    // Funcs
    public:

        explicit PlayerAPI(Client* client);

        std::optional<PlaybackObject> getCurrentlyPlayingTrack() const;
        bool pause();
        bool play();


    private:

    // Vars
    public:
    private:
        Client* m_client;

        const std::string BASE_PLAYER_URL = "https://api.spotify.com/v1/me/player/";



    };

}





#endif //PLAYERAPI_H
