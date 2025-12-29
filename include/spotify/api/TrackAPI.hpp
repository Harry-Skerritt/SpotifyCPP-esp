//
// Created by Harry Skerritt on 22/12/2025.
//

#ifndef TRACKAPI_HPP
#define TRACKAPI_HPP

#pragma once
#include <string>
#include <optional>
#include <iostream>
#include "spotify/util/Types.h"
#include "spotify/util/JsonMapping.hpp"
#include "spotify/api/BaseAPI.hpp"


namespace Spotify {

    class TrackAPI : public BaseAPI {
    // Funcs
    public:

        explicit TrackAPI(Client* client) : BaseAPI(client) {};

        // GET
        [[nodiscard]] std::optional<TrackObject> getTrack(const std::string& id, const std::optional<std::string>& market = std::nullopt) const;
        [[nodiscard]] std::optional<TrackListObject> getTracks(const std::vector<std::string>& ids, const std::optional<std::string>& market = std::nullopt) const;
        [[nodiscard]] std::optional<PagedSavedTrackObject> getUserSavedTracks(const std::optional<std::string>& market = std::nullopt,
            const std::optional<int>& limit = std::nullopt, const std::optional<int>& offset = std::nullopt) const;
        [[nodiscard]] std::optional<std::vector<bool>> checkUsersSavedTracks(const std::vector<std::string>& ids) const;

        // PUT
        void saveTracksForUser(const std::vector<std::string>& ids) const;
        void saveTracksForUser(const std::vector<TimestampIDObject>& timestamped_ids) const;

        // DELETE
        void removeUsersSavedTracks(std::vector<std::string> ids) const;


    // Vars
    private:
        const std::string BASE_TRACK_URL = "https://api.spotify.com/v1/tracks";
        const std::string BASE_TRACK_USER_URL = "https://api.spotify.com/v1/me/tracks";

    };

}


#endif //TRACKAPI_HPP
