# Playlist Models

This page documents the models used by the Spotify **Playlist API**. These structures represent the data for both full and simplified playlists, as well as the specialized objects used to track items within a playlist.

All models are located within the `Spotify::` namespace.

---

## Table of Contents

- [Playlist Track Management](#playlist-track-management)
- [Playlist Objects](#playlist-objects)
- [Paging Aliases](#paging-aliases)

---

## Playlist Track Management



### `PlaylistTrackObject`
Represents an item within a playlist. Unlike a standard track, this includes metadata about when and by whom the track was added.
- `added_at`: The date and time the track was added (ISO 8601).
- `added_by`: An `AddedByObject` containing the profile of the user who added the track.
- `is_local`: Whether the track is a local file uploaded by the user.
- `track`: A `std::variant` containing either a `TrackObject` or an `EpisodeObject`.

#### Type Accessors
Because playlists can contain both music and podcast episodes, use these accessors to retrieve the underlying data safely:
- `asTrack()`: Returns `std::shared_ptr<TrackObject>` or `nullptr`.
- `asEpisode()`: Returns `std::shared_ptr<EpisodeObject>` or `nullptr`.

---

## Playlist Objects



### `PlaylistObject`
The comprehensive version of a playlist, typically returned when fetching a single playlist by ID.
- `collaborative`: Whether the playlist owner allows others to modify the playlist.
- `description`: The playlist description (optional).
- `id` / `uri` / `href`: Standard Spotify identifiers.
- `images`: A vector of `ImageObject` (covers).
- `owner`: The `OwnerObject` (user) who created the playlist.
- `tracks`: A **full** `PagedPlaylistTrackObject` containing the actual list of tracks.
- `snapshot_id`: The version identifier for the current state of the playlist.

### `SimplifiedPlaylistObject`
A lightweight version of the playlist object, typically returned in lists (e.g., "Get User's Playlists").
- Contains the same metadata as the full object (`name`, `id`, `owner`).
- **Difference**: The `tracks` field is a `TrackCollectionObject`, which only provides a total count and a link to the tracks, rather than the list itself.

---

## Paging Aliases

These aliases simplify the usage of the generic `PagingObject` template for playlist-related responses.

### `PagedPlaylistTrackObject`
Equivalent to `PagingObject<PlaylistTrackObject>`. Used for the `tracks` field inside a full `PlaylistObject`.

### `PagedPlaylistObject`
Equivalent to `PagingObject<SimplifiedPlaylistObject>`. This is the standard return type when listing multiple playlists (e.g., searching for playlists or getting a user's library).

---

## Notes
- **Snapshots**: The `snapshot_id` is essential when making modification requests (like removing tracks) to ensure you are editing the correct version of the playlist.
- **Variants**: Always check `asTrack()` or `asEpisode()` when iterating through a playlist, as Spotify allows mixed-media playlists.
