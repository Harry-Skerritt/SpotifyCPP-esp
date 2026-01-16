//
// Created by Harry Skerritt on 08/01/2026.
//

#include "./spotify/extensions/VisualAPI.hpp"

namespace Spotify::Extensions {

    // Helper
    Colour VisualAPI::parseHex(const std::string& hexStr) {
        if (hexStr.length() < 8) return {0, 0, 0};

        uint32_t value;
        std::stringstream ss;
        ss << std::hex << hexStr.substr(2); // Skips 0x
        ss >> value;

        return Colour {
            static_cast<uint8_t>((value >> 16) & 0xFF),
            static_cast<uint8_t>((value >> 8) & 0xFF),
            static_cast<uint8_t>(value & 0xFF)
        };
    }

    // --- Average Colour ---
    Colour VisualAPI::getAverageColour(const std::string &imageUrl) {
        const std::string encodedImageUrl = detail::urlEncode(imageUrl);
        const std::string requestUrl = "https://avaerage-color-api.vercel.app/api/average?url=" + encodedImageUrl;

        auto response = HTTP::get(requestUrl, "");
        ErrorHandler::verifyResponse(response);

        JsonDocument doc;

        DeserializationError error = deserializeJson(doc, response.body);

        if (error) {
            throw Spotify::Exception("VisualAPI: Failed to parse average colour: " + std::string(error.c_str()));

        }

        if (!doc.containsKey("average")) {
            throw Spotify::Exception("VisualAPI: 'average' key missing in response");
        }

        const char* avgHex = doc["average"];

        if (avgHex == nullptr) {
            throw Spotify::Exception("VisualAPI: 'average' value is null or not a string");
        }

        return parseHex(std::string(avgHex));
    }

    Colour VisualAPI::getAverageColour(const Spotify::ImageObject &image) {
        return getAverageColour(image.url);
    }


    // --- Average Colour Palette ---
    AveragePalette VisualAPI::getAverageImagePalette(const std::string &imageUrl) {
        const std::string encodedImageUrl = detail::urlEncode(imageUrl);
        const std::string requestUrl = "https://avaerage-color-api.vercel.app/api/average?url=" + encodedImageUrl;

        auto response = HTTP::get(requestUrl, "");
        ErrorHandler::verifyResponse(response);

        JsonDocument doc;
        DeserializationError error = deserializeJson(doc, response.body);

        if (error) {
            throw Spotify::Exception("VisualAPI: Failed to parse average colour palette: " + std::string(error.c_str()));
        }

        const char* a  = doc["average"];
        const char* d1 = doc["darker_1"];
        const char* d2 = doc["darker_2"];
        const char* l1 = doc["lighter_1"];
        const char* l2 = doc["lighter_2"];

        if (!a || !d1 || !d2 || !l1 || !l2) {
            throw Spotify::Exception("VisualAPI: One or more palette keys are missing in the JSON response");
        }

        return AveragePalette {
            parseHex(a),
            parseHex(d1),
            parseHex(d2),
            parseHex(l1),
            parseHex(l2)
        };
    }

    AveragePalette VisualAPI::getAverageImagePalette(const Spotify::ImageObject &image) {
        return getAverageImagePalette(image.url);
    }


    // --- Vibrant Colour ---
    Colour VisualAPI::getVibrantColour(const std::string &imageUrl) {
        const std::string encodedImageUrl = detail::urlEncode(imageUrl);
        const std::string requestUrl = "https://avaerage-color-api.vercel.app/api/vibrant?url=" + encodedImageUrl;

        auto response = HTTP::get(requestUrl, "");
        ErrorHandler::verifyResponse(response);

        JsonDocument doc;

        DeserializationError error = deserializeJson(doc, response.body);

        if (error) {
            throw Spotify::Exception("VisualAPI: Failed to parse vibrant colour: " + std::string(error.c_str()));

        }

        if (!doc.containsKey("vibrant")) {
            throw Spotify::Exception("VisualAPI: 'vibrant' key missing in response");
        }

        const char* avgHex = doc["vibrant"];

        if (avgHex == nullptr) {
            throw Spotify::Exception("VisualAPI: 'vibrant' value is null or not a string");
        }

        return parseHex(std::string(avgHex));
    }

    Colour VisualAPI::getVibrantColour(const Spotify::ImageObject &image) {
        return getVibrantColour(image.url);
    }


    // --- Vibrant Colour Palette ---
    VibrantPalette VisualAPI::getVibrantImagePalette(const std::string &imageUrl) {
        const std::string encodedImageUrl = detail::urlEncode(imageUrl);
        const std::string requestUrl = "https://avaerage-color-api.vercel.app/api/vibrant?url=" + encodedImageUrl;

        auto response = HTTP::get(requestUrl, "");
        ErrorHandler::verifyResponse(response);

        JsonDocument doc;
        DeserializationError error = deserializeJson(doc, response.body);

        if (error) {
            throw Spotify::Exception("VisualAPI: Failed to parse vibrant colour palette: " + std::string(error.c_str()));
        }

        const char* v  = doc["vibrant"];
        const char* d1 = doc["darker_1"];
        const char* d2 = doc["darker_2"];
        const char* l1 = doc["lighter_1"];
        const char* l2 = doc["lighter_2"];

        if (!v || !d1 || !d2 || !l1 || !l2) {
            throw Spotify::Exception("VisualAPI: One or more palette keys are missing in the JSON response");
        }

        return VibrantPalette {
            parseHex(v),
            parseHex(d1),
            parseHex(d2),
            parseHex(l1),
            parseHex(l2)
        };
    }

    VibrantPalette VisualAPI::getVibrantImagePalette(const Spotify::ImageObject &image) {
        return getVibrantImagePalette(image.url);
    }
}
