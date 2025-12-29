//
// Created by Harry Skerritt on 28/12/2025.
//

#ifndef SHOWSAPI_HPP
#define SHOWSAPI_HPP

#pragma once
#include <string>
#include <optional>
#include <iostream>
#include "spotify/util/Types.h"
#include "spotify/util/JsonMapping.hpp"
#include "spotify/api/BaseAPI.hpp"

namespace Spotify {

    class ShowsAPI : public BaseAPI {
    // Funcs
    public:

        explicit ShowsAPI(Client* client) : BaseAPI(client) {};

        // GET
        std::optional<ShowObject> getShow(const std::string& id, const std::optional<std::string>& market = std::nullopt) const;
        std::optional<ShowListObject> getShows(const std::vector<std::string>& ids, const std::optional<std::string>& market = std::nullopt) const;
        std::optional<PagedEpisodeObject> getShowEpisodes(const std::string& id, const std::optional<std::string>& market = std::nullopt,
            const std::optional<int>& limit = std::nullopt, const std::optional<int>& offset) const;
        std::optional<PagedSavedShowObject> getUserSavedShows(const std::optional<int>& limit = std::nullopt, const std::optional<int>& offset) const;
        std::optional<std::vector<bool>> checkUsersSavedShows(const std::vector<std::string>& ids) const;

        // PUT
        void saveShowsForUser(const std::vector<std::string>& ids) const;

        // DELETE
        void removeShowsForUser(const std::vector<std::string>& ids, const std::optional<std::string>& market = std::nullopt) const;

    };

}
#endif //SHOWSAPI_HPP
