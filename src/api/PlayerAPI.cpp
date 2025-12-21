//
// Created by Harry Skerritt on 21/12/2025.
//

#include "spotify/api/PlayerAPI.hpp"

#include "nlohmann/json.hpp"
#include "spotify/core/Client.hpp"
#include "spotify/util/Http.hpp"

Spotify::PlayerAPI::PlayerAPI(Client *client) : m_client(client) { }

// --- GET ---
std::optional<Spotify::PlaybackObject> Spotify::PlayerAPI::getPlaybackState() const {
    if (!m_client) return std::nullopt;

    std::string token = tryGetAccessToken();
    auto result = HTTP::get((BASE_PLAYER_URL), token);


    if (result.code == RFC2616_Code::NO_CONTENT || result.code != RFC2616_Code::OK) {
        std::cerr << WebTools::getHttpStatusText((int)result.code)<< std::endl;
        return std::nullopt;
    }

    // Successfully received a body
    if (result.body.empty()) {
        std::cerr << "CRITICAL: No body received from request!" << std::endl;
        return std::nullopt;
    }


    try {
        auto data = nlohmann::json::parse(result.body);
        return data.get<Spotify::PlaybackObject>();

    } catch (const nlohmann::json::exception& e) {
        std::cerr << "JSON Mapping failed: " << e.what() << std::endl;
        return std::nullopt;
    }
}

std::optional<Spotify::DeviceListObject> Spotify::PlayerAPI::getAvailableDevices() const {
    if (!m_client) return std::nullopt;

    std::string token = tryGetAccessToken();
    auto result = HTTP::get((BASE_PLAYER_URL + "/devices"), token);


    if (result.code == RFC2616_Code::NO_CONTENT || result.code != RFC2616_Code::OK) {
        std::cerr << WebTools::getHttpStatusText((int)result.code)<< std::endl;
        return std::nullopt;
    }

    // Successfully received a body
    if (result.body.empty()) {
        std::cerr << "CRITICAL: No body received from request!" << std::endl;
        return std::nullopt;
    }

    try {
        auto data = nlohmann::json::parse(result.body);
        return data.get<Spotify::DeviceListObject>();

    } catch (const nlohmann::json::exception& e) {
        std::cerr << "JSON Mapping failed: " << e.what() << std::endl;
        return std::nullopt;
    }
}

std::optional<Spotify::PlaybackObject> Spotify::PlayerAPI::getCurrentlyPlayingTrack() const {
    if (!m_client) return std::nullopt;

    std::string token = tryGetAccessToken();
    auto result = HTTP::get((BASE_PLAYER_URL + "/currently-playing"), token);

    if (result.code == RFC2616_Code::NO_CONTENT || result.code != RFC2616_Code::OK) {
        std::cerr << WebTools::getHttpStatusText((int)result.code)<< std::endl;
        return std::nullopt;
    }

    // Successfully received a body
    if (result.body.empty()) {
        std::cerr << "CRITICAL: No body received from request!" << std::endl;
        return std::nullopt;
    }

    try {
        auto data = nlohmann::json::parse(result.body);
        return data.get<Spotify::PlaybackObject>();

    } catch (const nlohmann::json::exception& e) {
        std::cerr << "JSON Mapping failed: " << e.what() << std::endl;
        return std::nullopt;
    }
}

std::optional<Spotify::RecentlyPlayedTracksObject> Spotify::PlayerAPI::getRecentlyPlayedTracks() const {
    if (!m_client) return std::nullopt;

    std::string token = tryGetAccessToken();
    auto result = HTTP::get((BASE_PLAYER_URL + "/currently-playing"), token);

    if (result.code == RFC2616_Code::NO_CONTENT || result.code != RFC2616_Code::OK) {
        std::cerr << WebTools::getHttpStatusText((int)result.code)<< std::endl;
        return std::nullopt;
    }

    // Successfully received a body
    if (result.body.empty()) {
        std::cerr << "CRITICAL: No body received from request!" << std::endl;
        return std::nullopt;
    }

    try {
        auto data = nlohmann::json::parse(result.body);
        return data.get<Spotify::RecentlyPlayedTracksObject>();

    } catch (const nlohmann::json::exception& e) {
        std::cerr << "JSON Mapping failed: " << e.what() << std::endl;
        return std::nullopt;
    }
}

std::optional<Spotify::QueueObject> Spotify::PlayerAPI::getUsersQueue() const {
    if (!m_client) return std::nullopt;

    std::string token = tryGetAccessToken();
    auto result = HTTP::get((BASE_PLAYER_URL + "/currently-playing"), token);

    if (result.code == RFC2616_Code::NO_CONTENT || result.code != RFC2616_Code::OK) {
        std::cerr << WebTools::getHttpStatusText((int)result.code)<< std::endl;
        return std::nullopt;
    }

    // Successfully received a body
    if (result.body.empty()) {
        std::cerr << "CRITICAL: No body received from request!" << std::endl;
        return std::nullopt;
    }

    try {
        auto data = nlohmann::json::parse(result.body);
        return data.get<Spotify::QueueObject>();

    } catch (const nlohmann::json::exception& e) {
        std::cerr << "JSON Mapping failed: " << e.what() << std::endl;
        return std::nullopt;
    }
}


// --- POST ---


// --- PUT ---

// --- PRIVATE ---
std::string Spotify::PlayerAPI::tryGetAccessToken() const {
    try {
        return m_client->getAccessToken();
    } catch (...) {
        std::cerr << "CRITICAL: Crash during AccessToken retrieval!" << std::endl;
        throw;
    }
}

