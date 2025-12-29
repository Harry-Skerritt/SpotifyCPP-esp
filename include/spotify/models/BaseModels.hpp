//
// Created by Harry Skerritt on 29/12/2025.
//

#ifndef BASEMODELS_HPP
#define BASEMODELS_HPP

#pragma once

#include <string>
#include <vector>
#include <optional>
#include <variant>
#include <chrono>

namespace Spotify {

    struct ImageObject {
        std::string url;
        std::optional<int> height;
        std::optional<int> width;
    };

    struct CursorObject {
        std::string after;
        std::string before;
    };

    struct CopyrightObject {
        std::string text;
        std::string type;
    };

    struct ExternalURL {
        std::string spotify;
    };

    struct URIObject {
        std::string uri;
    };

    struct RestrictionsObject {
        std::string reason;
    };

    struct ExternalID {
        std::string isrc;
        std::string ean;
        std::string upc;
    };

    template <typename T>
    struct PagingObject {
        std::string href;
        int limit{};
        std::optional<std::string> next;
        std::optional<int> offset;
        std::optional<std::string> prev;
        int total{};
        std::vector<T> items;

        std::optional<CursorObject> cursors;
    };

    struct CategoryObject {
        std::string href;
        std::vector<ImageObject> icons;
        std::string id;
        std::string name;
    };

    struct MarketObject {
        std::vector<std::string> markets;
    };

    struct TimestampIDObject {
        std::string id;
        std::string added_at;
    };

    struct FollowersObject {
        std::optional<std::string> href;
        int total;
    };

    struct ExplicitContentObject {
        bool filter_enabled;
        bool filter_locked;
    };

    struct LinkedFromObject {
        ExternalURL external_urls;
        std::string href;
        std::string id;
        std::string type;
        std::string uri;
    };

    struct GenreObject { // Dep
        std::vector<std::string> genres;
    };


    struct ContextObject {
        std::string type;
        std::string href;
        ExternalURL external_urls;
        std::string uri;
    };

    struct ResumePointObject {
        bool fully_played;
        int resume_position_ms;
    };

    struct NarratorObject {
        std::string name;
    };

    struct AuthorObject {
        std::string name;
    };

    struct TrackCollectionObject {
        std::string href;
        int total;
    };

    struct OwnerObject {
        ExternalURL external_urls;
        std::string href;
        std::string id;
        std::string type;
        std::string uri;
        std::optional<std::string> display_name;
    };

    struct AddedByObject {
        ExternalURL external_urls;
        std::string href;
        std::string id;
        std::string type;
        std::string uri;
    };

}

#endif //BASEMODELS_HPP
