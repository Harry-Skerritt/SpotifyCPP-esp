//
// Created by Harry Skerritt on 22/12/2025.
//

#include "spotify/api/BaseAPI.hpp"
#include "spotify/core/Client.hpp"

namespace Spotify {

    std::string BaseAPI::tryGetAccessToken() const {
        try {
            return m_client->getAccessToken();
        }
        catch (const Spotify::Exception& e) {
            throw Spotify::Exception("API Request failed: Could not retrieve a valid Access Token. Details: " + std::string(e.what()));
        }
        catch (const std::exception& e) {
            throw Spotify::Exception("Internal System Error during token retrieval: " + std::string(e.what()));
        }
    }


}