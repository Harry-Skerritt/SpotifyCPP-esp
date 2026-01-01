# Types

This folder contains all type definitions used in the library. These structures and enumerations represent the data models returned by the Spotify Web API, ensuring type-safe interactions with tracks, albums, playlists, and user data.

---

## Core Types

| Module    | Description                                                                      | Link                                        |
|-----------|----------------------------------------------------------------------------------|---------------------------------------------|
| **Auth**  | Types related to the authentication (Client Credentials & Code Flow).            | [View Documentation](/docs/Types/Auth.md)   |
| **Scope** | Enumeration of Spotify API permission scopes used during authentication.         | [View Documentation](/docs/Types/Scope.md)  |
| **Enums** | Type-safe enumerations for search categories, album groups, and player modes.    | [View Documentation](/docs/Types/Enums.md)  |

---

## Data Objects

These objects represent the actual resources and data structures returned by Spotify endpoints.

| Module              | Description                                                                           | Link                                                           |
|---------------------|---------------------------------------------------------------------------------------|----------------------------------------------------------------|
| **Base Models**     | Core building blocks: Images, Followers, Copyrights, and the generic Paging template. | [View Documentation](/docs/Types/DataModels/BaseModels.md)     |
| **Resource Models** | The primary catalog: Artists, Albums, Tracks, Shows, and Episodes.                    | [View Documentation](/docs/Types/DataModels/ResourceModels.md) |
| **Player Models**   | Playback state, device management, and user queue structures.                         | [View Documentation](/docs/Types/DataModels/PlayerModels.md)   |
| **Playlist Models** | Full and simplified playlist objects, including playlist track metadata.              | [View Documentation](/docs/Types/DataModels/PlaylistModels.md) |
| **Search Models**   | A unified result wrapper for multi-type search queries.                               | [View Documentation](/docs/Types/DataModels/SearchModels.md)   |
| **User Models**     | Public and private user profile information.                                          | [View Documentation](/docs/Types/DataModels/UserModels.md)     |

---

## Notes

- **Simplified vs Full**: Many resources (like Albums and Artists) have both "Simplified" and "Full" variants. Simplified versions are typically used when the object is nested inside another list.
- **Variant Usage**: Player and Playlist items use `std::variant` to handle cases where a result could be either a **Track** or a **Podcast Episode**.
- **Paging**: Most list-based results are wrapped in a `PagingObject<T>`, which includes the current items, the total available, and links to next/previous pages.
