//
// Created by Harry Skerritt on 29/12/2025.
//

#ifndef RESOURCEMODELS_HPP
#define RESOURCEMODELS_HPP

#pragma once

#include <string>
#include <vector>
#include <optional>
#include <variant>
#include <chrono>

#include "BaseModels.hpp"

namespace Spotify {

    // --- Forward Declarations - Main ---
    struct ArtistObject;
    struct AlbumObject;
    struct AudiobookObject;
    struct ChapterObject;
    struct TrackObject;
    struct ShowObject;
    struct EpisodeObject;

    /*
    // --- Forward Declarations - Simple ---
    struct SimplifiedArtistObject;
    struct SimplifiedAlbumObject;
    struct SimplifiedAudiobookObject;
    struct SimplifiedChapterObject;
    struct SimplifiedTrackObject;
    struct SimplifiedShowObject;
    struct SimplifiedEpisodeObject;
*/

    // --- Simplified Objects ---
    struct SimplifiedArtistObject {
        ExternalURL external_urls;
        std::string href;
        std::string id;
        std::string name;
        std::string type;
        std::string uri;
    };

    struct SimplifiedAlbumObject {
        std::string album_type;
        int total_tracks;
        std::vector<std::string> available_markets;
        ExternalURL external_urls;
        std::string href;
        std::string id;
        std::vector<ImageObject> images;
        std::string name;
        std::string release_date;
        std::string release_date_precision;
        RestrictionsObject restrictions;
        std::string type;
        std::string uri;
        std::vector<SimplifiedArtistObject> artists;
    };

    struct SimplifiedAudiobookObject {
        std::vector<AuthorObject> authors;
        std::vector<std::string> available_markets;
        std::vector<CopyrightObject> copyrights;
        std::string description;
        std::string html_description;
        std::string edition;
        bool is_explicit;
        ExternalURL external_urls;
        std::string href;
        std::string id;
        std::vector<ImageObject> images;
        std::vector<std::string> languages;
        std::string media_type;
        std::string name;
        std::vector<NarratorObject> narrators;
        std::string publisher;
        std::string type;
        std::string uri;
        int total_chapters;
    };

    struct SimplifiedChapterObject {
        std::optional<std::string> audio_preview_url; // Dep
        std::vector<std::string> available_markets;
        int chapter_number;
        std::string description;
        std::string html_description;
        int duration_ms;
        bool is_explicit;
        ExternalURL external_urls;
        std::string href;
        std::string id;
        std::vector<ImageObject> images;
        bool is_playable;
        std::vector<std::string> languages;
        std::string name;
        std::string release_date;
        std::string release_date_precision;
        ResumePointObject resume_point;
        std::string type;
        std::string uri;
        RestrictionsObject restrictions;
    };

    struct SimplifiedTrackObject {
        std::vector<SimplifiedArtistObject> artists;
        std::vector<std::string> available_markets;
        int disc_number;
        int duration_ms;
        bool is_explicit;
        ExternalURL external_urls;
        std::string href;
        std::string id;
        bool is_playable;
        LinkedFromObject linked_from;
        RestrictionsObject restrictions;
        std::string name;
        std::optional<std::string> preview_url; // Dep
        int track_number;
        std::string type;
        std::string uri;
        bool is_local;
    };

    struct SimplifiedShowObject {
        std::vector<std::string> available_markets;
        std::vector<CopyrightObject> copyrights;
        std::string description;
        std::string html_description;
        bool is_explicit;
        ExternalURL external_urls;
        std::string href;
        std::string id;
        std::vector<ImageObject> images;
        bool is_externally_hosted;
        std::vector<std::string> languages;
        std::string media_type;
        std::string name;
        std::string publisher;
        std::string type;
        std::string uri;
        int total_episodes;
    };

    struct SimplifiedEpisodeObject {
        std::optional<std::string> audio_preview_url; // Dep
        std::string description;
        std::string html_description;
        int duration_ms;
        bool is_explicit;
        ExternalURL external_urls;
        std::string href;
        std::string id;
        std::vector<ImageObject> images;
        bool is_externally_hosted;
        bool is_playable;
        std::string language; // Dep
        std::vector<std::string> languages;
        std::string name;
        std::string release_date;
        std::string release_date_precision;
        ResumePointObject resume_point;
        std::string type;
        std::string uri;
        RestrictionsObject restrictions;
    };

    // --- Paged Aliases - Simplified Objects ---
    using PagedAlbumObject = PagingObject<SimplifiedAlbumObject>;
    using PagedAudiobookObject = PagingObject<SimplifiedAudiobookObject>;
    using PagedChapterObject = PagingObject<SimplifiedChapterObject>;
    using PagedEpisodeObject = PagingObject<SimplifiedEpisodeObject>;
    using PagedTrackObject = PagingObject<SimplifiedTrackObject>;



    // --- Main Objects - Artists ---
    struct ArtistObject {
        ExternalURL external_urls;
        FollowersObject followers;
        std::vector<std::string> genres;
        std::string href;
        std::vector<ImageObject> images;
        std::string name;
        int popularity;
        std::string type;
        std::string uri;
    };

    struct ArtistListObject {
        std::vector<ArtistObject> artists;
    };


    // --- Main Objects - Albums ---
    struct AlbumObject {
        std::string album_type;
        int total_tracks;
        std::vector<std::string> available_markets;
        ExternalURL external_urls;
        std::string href;
        std::string id;
        std::vector<ImageObject> images;
        std::string name;
        std::string release_date;
        std::string release_date_precision;
        RestrictionsObject restrictions;
        std::string type;
        std::string uri;
        std::vector<SimplifiedArtistObject> artists;
        PagedTrackObject tracks;
        std::vector<CopyrightObject> copyrights;
        ExternalID external_ids;
        std::vector<std::string> genres; // dep
        std::string label;
        int popularity;
    };

    struct AlbumListObject {
        std::vector<AlbumObject> albums;
    };

    struct SavedAlbumObject {
        std::string added_at;
        AlbumObject album;
    };


    // --- Main Objects - Audiobooks ---
    struct AudiobookObject {
        std::vector<AuthorObject> authors;
        std::vector<std::string> available_markets;
        std::vector<CopyrightObject> copyrights;
        std::string description;
        std::string html_description;
        std::string edition;
        bool is_explicit;
        ExternalURL external_urls;
        std::string href;
        std::string id;
        std::vector<ImageObject> images;
        std::vector<std::string> languages;
        std::string media_type;
        std::string name;
        std::vector<NarratorObject> narrators;
        std::string publisher;
        std::string type;
        std::string uri;
        int total_chapters;
        PagedChapterObject chapters;
    };

    struct AudiobookListObject {
        std::vector<AudiobookObject> audiobooks;
    };


    // --- Main Objects - Chapters ---
    struct ChapterObject {
        std::optional<std::string> audio_preview_url; // Dep
        std::vector<std::string> available_markets;
        int chapter_number;
        std::string description;
        std::string html_description;
        int duration_ms;
        bool is_explicit;
        ExternalURL external_urls;
        std::string href;
        std::string id;
        std::vector<ImageObject> images;
        bool is_playable;
        std::vector<std::string> languages;
        std::string name;
        std::string release_date;
        std::string release_date_precision;
        ResumePointObject resume_point;
        std::string type;
        std::string uri;
        RestrictionsObject restrictions;
        SimplifiedAudiobookObject audiobook;
    };

    struct ChapterListObject {
        std::vector<ChapterObject> chapters;
    };


    // --- Main Objects - Tracks ---
    struct TrackObject {
        SimplifiedAlbumObject album;
        std::vector<SimplifiedArtistObject> artists;
        std::vector<std::string> available_markets;
        int disc_number;
        int duration_ms;
        bool is_explicit;
        ExternalID external_ids;
        ExternalURL external_urls;
        std::string href;
        std::string id;
        bool is_playable;
        LinkedFromObject linked_from;
        RestrictionsObject restrictions;
        std::string name;
        int popularity;
        std::optional<std::string> preview_url; // Dep
        int track_number;
        std::string type;
        std::string uri;
        bool is_local;
    };

    struct TrackListObject {
        std::vector<TrackObject> tracks;
    };

    struct SavedTrackObject {
        std::string added_at;
        TrackObject track;
    };

    struct PlayHistoryObject {
        TrackObject track;
        std::string played_at;
        ContextObject context;
    };


    // --- Main Objects - Shows ---
    struct ShowObject {
        std::vector<std::string> available_markets;
        std::vector<CopyrightObject> copyrights;
        std::string description;
        std::string html_description;
        bool is_explicit;
        ExternalURL external_urls;
        std::string href;
        std::string id;
        std::vector<ImageObject> images;
        bool is_externally_hosted;
        std::vector<std::string> languages;
        std::string media_type;
        std::string name;
        std::string publisher;
        std::string type;
        std::string uri;
        int total_episodes;
        PagedEpisodeObject episodes;
    };

    struct ShowListObject {
        std::vector<ShowObject> shows;
    };

    struct SavedShowObject {
        std::string added_at;
        ShowObject show;
    };


    // --- Main Objects - Episodes ---
    struct EpisodeObject {
        std::optional<std::string> audio_preview_url; // Dep
        std::string description;
        std::string html_description;
        int duration_ms;
        bool is_explicit;
        ExternalURL external_urls;
        std::string href;
        std::string id;
        std::vector<ImageObject> images;
        bool is_externally_hosted;
        bool is_playable;
        std::string language; // Dep
        std::vector<std::string> languages;
        std::string name;
        std::string release_date;
        std::string release_date_precision;
        ResumePointObject resume_point;
        std::string type;
        std::string uri;
        RestrictionsObject restrictions;
        SimplifiedShowObject show;
    };

    struct EpisodeListObject {
        std::vector<EpisodeObject> episodes;
    };

    struct SavedEpisodeObject {
        std::string added_at;
        EpisodeObject episode;
    };



    // --- Paged Aliases - Main ---
    using PagedArtistObject = PagingObject<ArtistObject>;
    using PagedCategoryObject = PagingObject<CategoryObject>;
    using PagedSavedAlbumObject = PagingObject<SavedAlbumObject>;
    using PagedSavedEpisodeObject = PagingObject<SavedEpisodeObject>;
    using PagedSavedShowObject = PagingObject<SavedShowObject>;
    using PagedSavedTrackObject = PagingObject<SavedTrackObject>;


}

#endif //RESOURCEMODELS_HPP
