//
// Created by Harry Skerritt on 18/12/2025.
//

#include "spotify/auth/Auth.hpp"

#include "spotify/core/Errors.hpp"
#include "spotify/core/Endpoints.hpp"


namespace Spotify {

    Auth::Auth(const ClientCredentials& keys) {
        if (keys.client_id.empty() || keys.client_secret.empty()) {
            throw LogicException("ClientCredentials cannot be empty");
        }
        m_credentials = keys;
    }

    std::string Auth::createAuthoriseURL(
        const std::string& redirect_uri,
        const std::vector<Scope>& scopes,
        const std::optional<std::string>& state)
    {
        if (redirect_uri.empty()) throw LogicException("Redirect URI cannot be empty.");

        std::string scope_str = buildScopeString(scopes);
        auto actual_state = state.value_or(detail::generateRandomState());
        m_redirectUri = redirect_uri;

        std::ostringstream oss;
        oss << "?response_type=code"
        << "&client_id=" << detail::urlEncode(m_credentials.client_id)
        << "&scope=" << detail::urlEncode(scope_str)
        << "&redirect_uri=" << detail::urlEncode(redirect_uri)
        << "&state=" << detail::urlEncode(actual_state);

        return Endpoints::AUTHORISE + oss.str();
    }

    void Auth::exchangeCode(const std::string &code) {
        if (code.empty()) throw LogicException("Authorization Code cannot be empty.");

        std::ostringstream post_fields;
        post_fields << "code=" << detail::urlEncode(code)
                    << "&redirect_uri=" << detail::urlEncode(m_redirectUri)
                    << "&grant_type=authorization_code";

        HTTP::HeaderMap headers;
        headers["Content-Type"] = "application/x-www-form-urlencoded";
        headers["Authorization"] = "Basic " + encodeClientCredentials();

        auto result = HTTP::post(Endpoints::TOKEN, "", post_fields.str(), headers, true);
        ErrorHandler::verifyResponse(result);

        buildAuthResponse(result.body);
    }

    void Auth::refreshAccessToken(const std::optional<std::string>& refresh_token) {
        std::string token = refresh_token.value_or(m_refresh_token);
        if (token.empty()) throw LogicException("No refresh token available");

        std::string body = "grant_type=refresh_token&refresh_token=" + detail::urlEncode(token);

        HTTP::HeaderMap headers;
        headers["Content-Type"] = "application/x-www-form-urlencoded";
        headers["Authorization"] = "Basic " + encodeClientCredentials();


        auto result = HTTP::post(Endpoints::TOKEN, "", body, headers);
        ErrorHandler::verifyResponse(result);

        buildAuthResponse(result.body);
    }

    // Getters
    std::string Auth::getAccessToken() {
        if (isTokenExpired()) {
            refreshAccessToken();
        }
        return m_authResponse.access_token;
    }


    // --- PRIVATE ---
    AuthResponse Auth::buildAuthResponse(const std::string &json_str) {
        // 1. Allocate a buffer for the JSON (Auth responses are small, ~1KB is plenty)
        JsonDocument doc;
        DeserializationError error = deserializeJson(doc, json_str);

        // 2. Handle Parse Errors (Replaces catch block)
        if (error) {
            throw Spotify::ParseException("Failed to build AuthResponse: " + std::string(error.c_str()), json_str);
        }

        AuthResponse response;

        // 3. Map basic fields with safe fallbacks
        response.access_token = doc["access_token"] | "";
        response.token_type   = doc["token_type"] | "";
        response.scope        = doc["scope"] | "";

        // 4. Handle Expiration Time
        int expires_in = doc["expires_in"] | 3600; // Default to 1 hour if missing
        response.expire_time = std::chrono::system_clock::now() + std::chrono::seconds(expires_in);

        // 5. Handle Refresh Token
        // Spotify only sends a refresh_token on the first authorization, not on refreshes
        if (doc.containsKey("refresh_token")) {
            m_refresh_token = doc["refresh_token"].as<std::string>();
            response.refresh_token = m_refresh_token;
        } else {
            // Carry over the existing token from our class member
            response.refresh_token = m_refresh_token;
        }

        response.response_code = HTTPStatus_Code::OK;
        response.response_code = HTTPStatus_Code::OK;
        m_authResponse = response;

        return response;
    }

    // HELPERS
    std::string Auth::encodeClientCredentials() const {
        std::string client_creds = m_credentials.client_id + ":" +  m_credentials.client_secret;
        std::string encoded = base64_encode(client_creds);
        return encoded;
    }

    bool Auth::isTokenExpired() const {
        return std::chrono::system_clock::now() >= m_authResponse.expire_time;
    }
}



