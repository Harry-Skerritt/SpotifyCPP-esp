# Base Models

This page documents the core structural models used by the Spotify API. These structs represent the building blocks for more complex objects like Tracks, Albums, and Playlists.

All models are located within the `Spotify::` namespace and are designed to map directly to Spotify's JSON response objects.

---

## Table of Contents

- [Core Objects](#core-objects)
- [Identification and URLs](#identification-and-urls)
- [Paging and Cursors](#paging-and-cursors)
- [Content Restrictions and Meta](#content-restrictions-and-meta)
- [Narrative and Audio Content](#narrative-and-audio-content)

---

## Core Objects

### `ImageObject`
Represents an image file associated with a resource (e.g., Album Art, Profile Picture).
- `url`: The source URL of the image.
- `height`: The image height in pixels (optional).
- `width`: The image width in pixels (optional).

### `FollowersObject`
Information about the followers of a user or artist.
- `href`: A link to the Web API endpoint providing full details of the followers (usually `null`).
- `total`: The total number of followers.

### `ExplicitContentObject`
User-specific settings for explicit content filtering.
- `filter_enabled`: True if explicit content is filtered.
- `filter_locked`: True if the filter setting is locked (e.g., by parental controls).

---

## Identification and URLs

### `ExternalURL`
Contains external URLs for the resource.
- `spotify`: The Spotify Web URL for the resource (e.g., `https://open.spotify.com/...`).

### `URIObject`
A simple wrapper for a Spotify URI.
- `uri`: The resource identifier (e.g., `spotify:track:ID`).

### `ExternalID`
Known external identifiers for a track.
- `isrc`: International Standard Recording Code.
- `ean`: International Article Number.
- `upc`: Universal Product Code.

### `OwnerObject` / `AddedByObject`
Represents a user or entity that owns or added a resource.
- Includes standard identification fields: `id`, `uri`, `href`, `type`, and `external_urls`.
- `display_name`: The name shown on the Spotify profile (optional).

---

## Paging and Cursors



### `PagingObject<T>`
A generic template used for any API response that returns a list of items.
- `items`: A `std::vector` of the specific resource type (`T`).
- `limit`: The maximum number of items requested.
- `next` / `prev`: URLs to the next or previous page of results.
- `offset`: The index of the first item in the current page.
- `total`: Total number of items available in the full collection.

### `CursorObject`
Used specifically for cursor-based paging (e.g., "Recently Played").
- `after`: The cursor to use as a key to find the next page of items.
- `before`: The cursor to use as a key to find the previous page of items.

---

## Content Restrictions and Meta

### `RestrictionsObject`
Part of a resource that describes why it may be unavailable.
- `reason`: The reason for the restriction (e.g., `"market"`, `"product"`, `"explicit"`).

### `CopyrightObject`
Copyright information for a release.
- `text`: The copyright text.
- `type`: The type of copyright: `C` (the copyright) or `P` (the sound recording performance copyright).

### `ContextObject`
The context in which a track is playing (e.g., a specific Playlist or Album).
- Includes `type`, `href`, `uri`, and `external_urls`.

---

## Narrative and Audio Content

### `ResumePointObject`
The playback position of an episode or audiobook for the current user.
- `fully_played`: Whether the episode has been finished.
- `resume_position_ms`: The position in milliseconds where the user left off.

### `NarratorObject` / `AuthorObject`
Identifies the individuals associated with an Audiobook or Chapter.
- `name`: The name of the narrator or author.

### `TrackCollectionObject`
A simplified object representing a collection of tracks (e.g., inside an Album or Playlist).
- `href`: Link to the full track list.
- `total`: Count of tracks in the collection.

---

## Notes
- **Template Usage**: The `PagingObject` is designed to be used as `PagingObject<TrackObject>`, `PagingObject<ArtistObject>`, etc.
- **Optionals**: Fields marked with `std::optional` may be null in the Spotify API response (e.g., `height` and `width` on images).