# Resource Models

This page documents the primary catalog models for the Spotify API. These structures represent major resources such as **Artists**, **Albums**, **Tracks**, **Shows**, **Episodes**, and **Audiobooks**.

The library distinguishes between **Full Objects** (containing comprehensive details) and **Simplified Objects** (used in lists or child references to save bandwidth).

All models are located within the `Spotify::` namespace.

---

## Table of Contents

- [Overview](#overview)
- [Artist Models](#artist-models)
- [Album Models](#album-models)
- [Track Models](#track-models)
- [Show and Episode Models](#show-and-episode-models)
- [Audiobook and Chapter Models](#audiobook-and-chapter-models)
- [Library and History Models](#library-and-history-models)

---

## Overview

Spotify resources usually come in two flavors:
1.  **Simplified Objects**: Contain basic information (ID, Name, URI) and are typically found inside other objects (e.g., a simplified artist inside an album).
2.  **Full Objects**: Contain all available metadata, including popularity, genres, and nested paging objects for children (e.g., tracks within an album).



---

## Artist Models

### `SimplifiedArtistObject`
Basic artist information.
- `id`, `name`, `uri`, `external_urls`.

### `ArtistObject` (Full)
Comprehensive artist data.
- Includes all simplified fields plus:
- `followers`: Total count of followers.
- `genres`: List of associated genres.
- `images`: Artist profile pictures.
- `popularity`: A value from 0 to 100.

---

## Album Models

### `SimplifiedAlbumObject`
Basic album data, often found in search results or track references.
- `album_type`: (e.g., "album", "single", "compilation").
- `artists`: A vector of `SimplifiedArtistObject`.
- `release_date` and `release_date_precision`.

### `AlbumObject` (Full)
Comprehensive album data.
- Includes all simplified fields plus:
- `tracks`: A `PagedTrackObject` containing the album's tracks.
- `copyrights`: Legal copyright information.
- `label`: The record label name.

---

## Track Models

### `SimplifiedTrackObject`
Basic track information found within an album object.
- `duration_ms`, `is_explicit`, `track_number`, `disc_number`.
- `is_playable`: Whether the track can be played in the current market.



### `TrackObject` (Full)
Comprehensive track data.
- Includes all simplified fields plus:
- `album`: The `SimplifiedAlbumObject` this track belongs to.
- `popularity`: Popularity score (0-100).
- `external_ids`: Identifiers like ISRC.

---

## Show and Episode Models

### `SimplifiedShowObject` / `ShowObject`
Represent podcasts or "shows."
- `publisher`, `media_type`, `total_episodes`.
- Full version includes nested `PagedEpisodeObject`.

### `SimplifiedEpisodeObject` / `EpisodeObject`
Represent individual podcast episodes.
- `duration_ms`, `release_date`, `resume_point`.
- Full version includes a reference to the parent `SimplifiedShowObject`.



---

## Audiobook and Chapter Models

### `AudiobookObject`
Information about an audiobook.
- `authors`, `narrators`, `publisher`, `total_chapters`.
- Includes nested `PagedChapterObject`.

### `ChapterObject`
A specific chapter within an audiobook.
- `chapter_number`, `duration_ms`, `resume_point`.

---

## Library and History Models

### `Saved` Objects
Used when fetching items from the "Your Library" section. These wrap a full resource with an "added_at" timestamp.
- `SavedTrackObject`
- `SavedAlbumObject`
- `SavedShowObject`
- `SavedEpisodeObject`

### `PlayHistoryObject`
Used for the "Recently Played" endpoint.
- `track`: The `TrackObject` played.
- `played_at`: Timestamp of playback.
- `context`: The `ContextObject` (e.g., the playlist or album) the track was played in.

---

## Notes
- **Paging Aliases**: This header defines several aliases like `PagedTrackObject` and `PagedArtistObject` to make handling long lists of results more intuitive.
- **Market Restrictions**: Many objects contain `available_markets` or a `RestrictionsObject` to indicate if content is available in a specific geographic region.