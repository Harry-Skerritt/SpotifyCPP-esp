//
// Created by Harry Skerritt on 29/12/2025.
//

#ifndef USERMODELS_HPP
#define USERMODELS_HPP

#pragma once

#include <string>
#include <vector>
#include <optional>
#include <variant>
#include <chrono>

#include "BaseModels.hpp"

namespace Spotify {

    struct UserObject {
        std::string country;
        std::string display_name;
        std::string email;
        ExplicitContentObject explicit_content;
        ExternalURL external_urls;
        FollowersObject followers;
        std::string href;
        std::string id;
        std::vector<ImageObject> images;
        std::string product;
        std::string type;
        std::string uri;
    };

}
#endif //USERMODELS_HPP
