# Search Models

This page documents the models used for Spotify **Search API** results. The search endpoint is unique because it can return multiple types of data (tracks, artists, albums, etc.) in a single response. These models wrap standard resource paging objects into a single, unified search result structure.

All models are located within the `Spotify::` namespace.

---

## Table of Contents

- [Search Result Structure](#search-result-structure)
- [Search Paging Aliases](#search-paging-aliases)

---

## Search Result Structure



### `SearchObject`
The top-level object returned by a search query. It contains optional paging objects for each requested resource type. If a specific type was not requested in the search query, that field will be `std::nullopt`.

| Field | Type | Description |
| :--- | :--- | :--- |
| `tracks` | `std::optional<SearchTrackObject>` | Paged list of full Track objects. |
| `artists` | `std::optional<SearchArtistObject>` | Paged list of full Artist objects. |
| `albums` | `std::optional<SearchAlbumObject>` | Paged list of simplified Album objects. |
| `playlists` | `std::optional<SearchPlaylistObject>` | Paged list of simplified Playlist objects. |
| `shows` | `std::optional<SearchShowsObject>` | Paged list of simplified Show objects. |
| `episodes` | `std::optional<SearchEpisodesObject>` | Paged list of simplified Episode objects. |
| `audiobook` | `std::optional<SearchAudioBookObject>` | Paged list of simplified Audiobook objects. |

---

## Search Paging Aliases

These aliases are specialized versions of the `PagingObject<T>` template. They represent a single "page" of results for a specific resource type within the search response.



| Alias | Underlying Type |
| :--- | :--- |
| `SearchTrackObject` | `PagingObject<TrackObject>` |
| `SearchArtistObject` | `PagingObject<ArtistObject>` |
| `SearchAlbumObject` | `PagingObject<SimplifiedAlbumObject>` |
| `SearchPlaylistObject` | `PagingObject<SimplifiedPlaylistObject>` |
| `SearchShowsObject` | `PagingObject<SimplifiedShowObject>` |
| `SearchEpisodesObject` | `PagingObject<SimplifiedEpisodeObject>` |
| `SearchAudioBookObject` | `PagingObject<SimplifiedAudiobookObject>` |

---

## Notes

- **Optional Handling**: Because the search API allows you to search for one or many types (e.g., just tracks, or tracks + artists), you must always check if the field `has_value()` before accessing the results.
- **Resource Depth**: Note that `tracks` and `artists` return **Full Objects**, while albums and other media types return **Simplified Objects** as per the Spotify API specification.