# Player Models

This page documents the models used by the Spotify **Player API**. These structures manage playback state, device control, and the user's playback queue. They are designed to handle both music tracks and podcast episodes through C++ type-safe variants.

All models are located within the `Spotify::` namespace.

---

## Table of Contents

- [Enums](#enums)
- [Device Management](#device-management)
- [Playback State](#playback-state)
- [Queue Management](#queue-management)
- [Request Properties](#request-properties)

---

## Enums

### `RepeatState`
Represents the current repeat mode of the player.
- `Track`: The current track is repeating.
- `Context`: The current context (album/playlist) is repeating.
- `Off`: Repeat is disabled.

---

## Device Management

### `DeviceObject`
Represents a Spotify Connect compatible device (e.g., Phone, Computer, Smart Speaker).
- `id`: Unique identifier for the device (optional).
- `is_active`: Whether the device is currently controlling playback.
- `is_private_session`: Whether the device is in a private session.
- `name`: Human-readable name (e.g., "Kitchen Speaker").
- `type`: Device type (e.g., "Computer", "Smartphone").
- `volume_percent`: Current volume (0-100).
- `supports_volume`: Whether the volume can be controlled via the API.

### `DeviceListObject`
A simple container for a list of available devices returned by the API.
- `devices`: A `std::vector` of `DeviceObject`.

---

## Playback State



### `PlaybackObject`
The full state of the user's player, including progress and active item.
- `device`: The currently active `DeviceObject`.
- `repeat_state`: The current `RepeatState`.
- `shuffle_state`: Whether shuffle is enabled.
- `item`: A `std::variant` containing either a `TrackObject` or an `EpisodeObject`.
- `progress_ms`: Progress into the current track in milliseconds.
- `is_playing`: Whether the player is currently unpaused.
- `actions`: An `ActionsObject` describing what the user is allowed to do (e.g., can they skip?).

#### Type Accessors
Use these to safely access the currently playing item without manually checking the variant:
- `asTrack()`: Returns `std::shared_ptr<TrackObject>` or `nullptr`.
- `asEpisode()`: Returns `std::shared_ptr<EpisodeObject>` or `nullptr`.

---

## Queue Management



### `QueueObject`
Represents the user's current track queue.
- `currently_playing`: A `PlayableItem` representing the current song/episode.
- `queue`: A `std::vector` of `PlayableItem` objects waiting to be played.

### `PlayableItem` (Inner Struct)
A wrapper around a track/episode variant.
- `asTrack()` / `asEpisode()`: Helper accessors to retrieve the underlying object.
- `name()`: A convenience function that returns the name of the item regardless of its type.

---

## Request Properties

### `StartPlaybackProperties`
Used as a parameter when triggering playback.
- `context_uri`: The album, artist, or playlist to start playing.
- `uris`: An array of specific track/episode URIs to play.
- `offset`: Where in the context to start (e.g., a specific track position).
- `position_ms`: The millisecond seek position to start from.

### `RecentlyPlayedTracksObject`
An alias for `PagingObject<PlayHistoryObject>`, used to track user history.

---

## Notes
- **Smart Pointers**: The Player models use `std::shared_ptr` for items within `std::variant`. This ensures memory efficiency and easy integration with other API modules.
- **Variant Handling**: Because Spotify allows both Tracks and Episodes in the queue, you should always check the result of `asTrack()` or `asEpisode()` before dereferencing.