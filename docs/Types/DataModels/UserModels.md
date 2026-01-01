# User Models

This page documents the models used to represent Spotify users. These structures contain profile information, account preferences, and social metadata.

All models are located within the `Spotify::` namespace.

---

## Table of Contents

- [User Structure](#user-structure)
- [Field Details](#field-details)

---

## User Structure



### `UserObject`
The primary object representing a Spotify user. This model is used for both the current authenticated user (Private Profile) and other Spotify users (Public Profile).

| Field | Type | Description |
| :--- | :--- | :--- |
| `id` | `std::string` | The Spotify user ID for the user. |
| `display_name` | `std::string` | The name displayed on the user's profile. |
| `uri` | `std::string` | The Spotify URI for the user. |
| `email` | `std::string` | The user's email address (requires `user-read-email` scope). |
| `country` | `std::string` | The country of the user, as set in their account (requires `user-read-private` scope). |
| `product` | `std::string` | The user's Spotify subscription level: `premium`, `free`, etc. (requires `user-read-private` scope). |
| `images` | `std::vector<ImageObject>` | The user's profile images. |
| `followers` | `FollowersObject` | Information about the followers of the user. |
| `explicit_content` | `ExplicitContentObject` | The user's explicit content settings. |
| `external_urls` | `ExternalURL` | Known external URLs for this user. |
| `href` | `std::string` | A link to the Web API endpoint providing full details of the user. |
| `type` | `std::string` | The object type: `"user"`. |

---

## Field Details

### Private vs. Public Profiles
Depending on the scopes granted during authentication, certain fields in the `UserObject` may be empty or unavailable:

* **Public Profile**: Contains `display_name`, `external_urls`, `followers`, `href`, `id`, `images`, `type`, and `uri`.
* **Private Profile**: (Requires `user-read-private` and `user-read-email` scopes) Adds `country`, `email`, `explicit_content`, and `product`.



---

## Notes

* **Display Name**: Note that `display_name` can be empty if the user has not set a specific name.
* **Product**: The `product` field is particularly useful for identifying if a user has access to features like offline play or ad-free listening in your application logic.