# Enums

This page documents the `Spotify::` enums and their associated helper functions. These enums are used to provide type-safe parameters for API requests, such as searching for specific content types or filtering album groups.

All functions and enums are available via the `Spotify::` namespace.

---

## Table of Contents

- [Overview](#overview)
- [Include Groups](#include-groups)
- [Additional Types](#additional-types)
- [Search Types](#search-types)

---

## Overview

The Spotify Enums provide:
- Type-safe representation of Spotify API constants.
- Helper functions to convert enums into API-friendly strings.
- Batch processing utilities to convert vectors of enums into comma-separated strings (CSV).

---

## Include Groups

Used primarily when fetching an artist's albums to filter the relationship type.

### `IncludeGroups` Enum
| Value         | API String     | Description                                |
|---------------|----------------|--------------------------------------------|
| `Album`       | `"album"`      | Standard albums.                           |
| `Single`      | `"single"`     | Singles and EPs.                           |
| `AppearsOn`   | `"appears_on"` | Compilations where the artist is featured. |
| `Compilation` | `"compilation"`| Albums that are collections of tracks.     |

### Helper Functions

#### `includeGroupToString(const IncludeGroups group)`
Converts a single enum value to its string representation.

#### `buildIncludeGroupsString(const std::vector<IncludeGroups>& groups)`
Converts a list of groups into a comma-separated string for API queries.

**Example:**
```c++
using namespace Spotify;
std::vector<IncludeGroups> groups = {IncludeGroups::Album, IncludeGroups::Single};
std::string query = buildIncludeGroupsString(groups); 
query -> "album,single"
```

---
## Additional Types

Used in the Player API to specify which types of content should be returned (e.g., when getting the current playback state).

### `AdditionalType` Enum
| Value   | API String     | Description                           | 
|---------|----------------|---------------------------------------|
| Track   | "track"        | Return only music tracks              |
| Episode | "episode"      | Return only podcast episodes          |
| All     | "track,episode"| Return both music tracks and episodes |


### Helper Functions

#### `additionalTypeToString(const AdditionalType type)`
Converts an enum value to the string required by the additional_types query parameter.

Example:
```c++

std::string type = Spotify::additionalTypeToString(Spotify::AdditionalType::All);
// type -> "track,episode"
```

---

## Search Types

Defines the categories of data that can be queried through the Search API.

### `SearchType` Enum
| Value     | API String  |
|-----------|-------------|
| Album     | "album"     |
| Artist    | "artist"    |
| Playlist  | "playlist"  |
| Track     | "track"     |
| Show      | "show"      |
| Episode   | "episode"   |
| Audiobook | "audiobook" |

### Helper Functions

#### `searchTypeToString(const SearchType type)`

Converts a single search category to its string representation.

#### `buildSearchTypeString(const std::vector<SearchType>& types)`

Combines multiple search categories into a CSV string.

Example:
```c++

std::vector<Spotify::SearchType> searchFor = { Spotify::SearchType::Artist, Spotify::SearchType::Track };
std::string q = Spotify::buildSearchTypeString(searchFor);
// q -> "artist,track"

```

## Notes

- All string conversion functions are marked `inline` for performance.
- When using `buildIncludeGroupsString` or `buildSearchTypeString`, if the input vector is empty, an empty string is returned.
- These enums are essential for avoiding "stringly-typed" code and ensuring API compatibility.