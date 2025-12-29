//
// Created by Harry Skerritt on 29/12/2025.
//

#ifndef SEARCHMODELS_HPP
#define SEARCHMODELS_HPP

#pragma once

#include <string>
#include <vector>
#include <optional>
#include <variant>
#include <chrono>

#include "BaseModels.hpp"
#include "ResourceModels.hpp"

namespace Spotify {

    using SearchTrackObject = PagingObject<TrackObject>;
    using SearchArtistObject = PagingObject<ArtistObject>;
    using SearchAlbumObject = PagingObject<SimplifiedAlbumObject>;
    using SearchPlaylistObject = PagingObject<SimplifiedPlaylistObject>;
    using SearchShowsObject = PagingObject<SimplifiedShowObject>;
    using SearchEpisodesObject = PagingObject<SimplifiedEpisodeObject>;
    using SearchAudioBookObject = PagingObject<SimplifiedAudiobookObject>;


    struct SearchObject {
        std::optional<SearchTrackObject> tracks;
        std::optional<SearchArtistObject> artists;
        std::optional<SearchAlbumObject> albums;
        std::optional<SearchPlaylistObject> playlists;
        std::optional<SearchShowsObject> shows;
        std::optional<SearchEpisodesObject> episodes;
        std::optional<SearchAudioBookObject> audiobook;
    };

}

#endif //SEARCHMODELS_HPP
