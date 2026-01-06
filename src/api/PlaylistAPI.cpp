//
// Created by Harry Skerritt on 24/12/2025.
//

#include <utility>

#include "spotify/api/PlaylistAPI.hpp"


#include "spotify/core/Client.hpp"
#include "spotify/core/Endpoints.hpp"
#include "../../include/spotify/util/web/Http.hpp"
#include "../../include/spotify/util/parse/JsonMapping.hpp"
#include "../../include/spotify/util/common/Tools.hpp"



namespace Spotify {

    // --- GET ---
    PlaylistObject PlaylistAPI::getPlaylist(
        const std::string &playlist_id,
        const std::optional<std::string> &market,
        const std::optional<std::string> &fields,
        const std::optional<AdditionalType> &additional_types) const
    {
        std::string url = Endpoints::PLAYLISTS + "/" + playlist_id;

        std::vector<std::string> params;

        if (market.has_value() &&  !market->empty() && Tools::isValidMarket(*market)) {
            params.push_back("market=" + detail::urlEncode(*market));
        }

        if (fields.has_value() && !fields->empty()) {
            params.push_back("fields=" + detail::urlEncode(*fields));
        }

        if (additional_types.has_value()) {
            params.push_back("additional_types=" + detail::urlEncode(additionalTypeToString(*additional_types)));
        }

        if (!params.empty()) {
            url += "?";
            for (size_t i = 0; i < params.size(); i++) {
                url += params[i];
                if (i < params.size() - 1) url += "&";
            }
        }

        return fetchAndParse<PlaylistObject>(url);
    }

    PagedPlaylistTrackObject PlaylistAPI::getPlaylistItems(
        const std::string &playlist_id,
        const std::optional<std::string> &market,
        const std::optional<std::string>& fields,
        const std::optional<int> &limit,
        const std::optional<int> &offset,
        const std::optional<AdditionalType>& additional_types) const
    {
        std::string url = Endpoints::PLAYLISTS + "/" + playlist_id + "/tracks";

        std::vector<std::string> params;

        if (market.has_value() &&  !market->empty() && Tools::isValidMarket(*market)) {
            params.push_back("market=" + detail::urlEncode(*market));
        }

        if (fields.has_value() && !fields->empty()) {
            params.push_back("fields=" + detail::urlEncode(*fields));
        }

        if (limit && detail::inRange(*limit, 1, 50)) {
            params.push_back("limit=" + std::to_string(*limit));
        }

        if (offset && offset >= 0) {
            params.push_back("offset=" + std::to_string(*offset));
        }

        if (additional_types.has_value()) {
            params.push_back("additional_types=" + detail::urlEncode(additionalTypeToString(*additional_types)));
        }

        if (!params.empty()) {
            url += "?";
            for (size_t i = 0; i < params.size(); i++) {
                url += params[i];
                if (i < params.size() - 1) url += "&";
            }
        }

        return fetchAndParse<PagedPlaylistTrackObject>(url);
    }

    PagedPlaylistObject PlaylistAPI::getCurrentUsersPlaylists(
        const std::optional<int> &limit,
        const std::optional<int> &offset) const
    {
        std::string url = Endpoints::MY_PLAYLISTS;

        std::vector<std::string> params;

        if (limit && detail::inRange(*limit, 1, 50)) {
            params.push_back("limit=" + std::to_string(*limit));
        }

        if (offset && offset >= 0) {
            params.push_back("offset=" + std::to_string(*offset));
        }

        if (!params.empty()) {
            url += "?";
            for (size_t i = 0; i < params.size(); i++) {
                url += params[i];
                if (i < params.size() - 1) url += "&";
            }
        }

        return fetchAndParse<PagedPlaylistObject>(url);
    }

    PagedPlaylistObject PlaylistAPI::getUsersPlaylists(
        const std::string &user_id,
        const std::optional<int> &limit,
        const std::optional<int> &offset) const
    {
        std::string url = Endpoints::USERS + "/" + user_id + "/playlists";

        std::vector<std::string> params;

        if (limit && detail::inRange(*limit, 1, 50)) {
            params.push_back("limit=" + std::to_string(*limit));
        }

        if (offset && offset >= 0) {
            params.push_back("offset=" + std::to_string(*offset));
        }

        if (!params.empty()) {
            url += "?";
            for (size_t i = 0; i < params.size(); i++) {
                url += params[i];
                if (i < params.size() - 1) url += "&";
            }
        }

        return fetchAndParse<PagedPlaylistObject>(url);
    }

    std::vector<ImageObject> PlaylistAPI::getPlaylistCoverImage(const std::string &playlist_id) const {

        std::string url = Endpoints::PLAYLISTS + "/" + playlist_id + "/images";

        return fetchAndParse<std::vector<ImageObject> >(url);
    }



    // --- PUT ---
#include <ArduinoJson.h>

    void PlaylistAPI::changePlaylistDetails(
        const std::string &playlist_id,
        const std::optional<std::string> &name,
        const std::optional<bool> &is_public,
        const std::optional<std::string> &description,
        const std::optional<bool> &is_collaborative) const
    {
        std::string url = Endpoints::PLAYLISTS + "/" + playlist_id;
        JsonDocument doc;

        if (name.has_value()) doc["name"] = *name;
        if (is_public.has_value()) doc["public"] = *is_public;
        if (description.has_value()) doc["description"] = *description;
        if (is_collaborative.has_value()) doc["collaborative"] = *is_collaborative;

        std::string body;
        serializeJson(doc, body);
        (void)sendAction("PUT", url, body);
    }

    void PlaylistAPI::replacePlaylistItems(
        const std::string &playlist_id,
        const std::vector<std::string> &uris) const
    {
        std::string url = Endpoints::PLAYLISTS + "/" + playlist_id + "/tracks";
        // Spotify expects a JSON array of URIs for the 'uris' key in a PUT request
        JsonDocument doc;
        JsonArray array = doc["uris"].to<JsonArray>();
        for (const auto &uri : uris) {
            array.add(uri);
        }

        std::string body;
        serializeJson(doc, body);
        (void)sendAction("PUT", url, body);
    }

    void PlaylistAPI::reorderPlaylistItems(
        const std::string& playlist_id,
        const int &range_start,
        const int &insert_before,
        const std::optional<int> &range_length,
        const std::optional<std::string> &snapshot_id) const
    {
        std::string url = Endpoints::PLAYLISTS + "/" + playlist_id + "/tracks";
        JsonDocument doc;

        doc["range_start"] = range_start;
        doc["insert_before"] = insert_before;
        if (range_length.has_value()) doc["range_length"] = *range_length;
        if (snapshot_id.has_value()) doc["snapshot_id"] = *snapshot_id;

        std::string body;
        serializeJson(doc, body);
        (void)sendAction("PUT", url, body);
    }

    void PlaylistAPI::addCustomPlaylistCover(
        const std::string &playlist_id,
        const std::string &image_path) const
    {
        std::string raw_image_data;
        bool is_url (image_path.rfind("http://", 0) == 0 || image_path.rfind("https://", 0) == 0);

        if (is_url) {
            // Is URL
            auto result = HTTP::getImage(image_path);

            if (result.code != HTTPStatus_Code::OK) {
                throw APIException({static_cast<int>(result.code), "Failed to download image from URL", "IMAGE_DOWNLOAD_FAILED"});
            }

            raw_image_data = result.body;
        } else {
            // Is File
            std::ifstream file(image_path, std::ios::binary);
            if (!file.is_open()) {
                throw LogicException("Could not open local image file: " + image_path);
            }
            std::stringstream buffer;
            buffer << file.rdbuf();
            raw_image_data = buffer.str();
        }

        if (raw_image_data.size() > 256 * 1024) {
            throw LogicException("Image too large (Max 256KB). Provided size: " +  std::to_string(raw_image_data.size() / 1024) + "KB");
        }
        std::string base64_image = base64_encode(raw_image_data);

        std::string url = Endpoints::PLAYLISTS + "/" + playlist_id + "/images";

        std::map<std::string, std::string> extra_headers = {{ "Content-Type", "image/jpeg"} };


        (void)sendAction("PUT", url, base64_image, extra_headers);
    }



    // --- POST ---
    void PlaylistAPI::addItemsToPlaylist(
    const std::string &playlist_id,
    const std::vector<std::string> &uris,
    const std::optional<int> &position) const
{
    if (uris.empty() || uris.size() > 100) {
        throw LogicException("You must provide between 1 and 100 URIs.");
    }

    std::string url = Endpoints::PLAYLISTS + "/" + playlist_id + "/tracks";
    JsonDocument doc;
    JsonArray array = doc["uris"].to<JsonArray>();
    for (const auto &uri : uris) {
        array.add(uri);
    }

    if (position.has_value()) doc["position"] = *position;

    std::string body;
    serializeJson(doc, body);
    (void)sendAction("POST", url, body);
}

std::optional<PlaylistObject> PlaylistAPI::createPlaylist(
    const std::string &user_id,
    const std::string &name,
    const std::optional<bool> &is_public,
    const std::optional<bool> &is_collaborative,
    const std::optional<std::string> &description) const
{
    std::string url = Endpoints::USERS + "/" + user_id + "/playlists";
    JsonDocument doc;

    doc["name"] = name;
    if (is_public.has_value()) doc["public"] = *is_public;
    if (is_collaborative.has_value()) doc["collaborative"] = *is_collaborative;
    if (description.has_value() && !description->empty()) doc["description"] = *description;

    std::string requestBody;
    serializeJson(doc, requestBody);

    // Use the sendAction helper to get the raw response
    auto responseBody = sendAction("POST", url, requestBody);

    if (responseBody.has_value() && !responseBody->empty()) {
        // Manually parse the returned PlaylistObject using ArduinoJson
        JsonDocument responseDoc;
        DeserializationError error = deserializeJson(responseDoc, *responseBody);

        if (error) {
            throw ParseException("Failed to parse created playlist JSON", *responseBody);
        }

        PlaylistObject playlist;
        from_json(responseDoc.as<JsonVariantConst>(), playlist);
        return playlist;
    }

    return std::nullopt;
}

void PlaylistAPI::removePlaylistItems(
    const std::string &playlist_id,
    const std::vector<URIObject> &tracks,
    const std::optional<std::string> &snapshot_id) const
{
    std::string url = Endpoints::PLAYLISTS + "/" + playlist_id + "/tracks";
    JsonDocument doc;
    JsonArray track_array = doc["tracks"].to<JsonArray>();

    for (const auto &track : tracks) {
        JsonObject obj = track_array.add<JsonObject>();
        obj["uri"] = track.uri;
    }

    if (snapshot_id.has_value() && !snapshot_id->empty()) {
        doc["snapshot_id"] = *snapshot_id;
    }

    std::string body;
    serializeJson(doc, body);
    (void)sendAction("DELETE", url, body);
}

}