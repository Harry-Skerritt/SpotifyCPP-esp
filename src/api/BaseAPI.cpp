//
// Created by Harry Skerritt on 22/12/2025.
//

#include "spotify/api/BaseAPI.hpp"
#include "spotify/core/Client.hpp"

namespace Spotify {

    std::string BaseAPI::tryGetAccessToken() const {
        try {
            return m_client->getAccessToken();
        } catch (...) {
            std::cerr << "CRITICAL: Crash during AccessToken retrieval!" << std::endl;
            throw;
        }
    }


}