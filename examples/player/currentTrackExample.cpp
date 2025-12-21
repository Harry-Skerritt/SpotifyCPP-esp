//
// Created by Harry Skerritt on 21/12/2025.
//
#include <spotify/auth/Auth.hpp>
#include <spotify/util/Tools.hpp>
#include <spotify/auth/AuthServer.h>
#include <spotify/core/Client.hpp>
#include "../ExampleUtils.hpp"

#include <cstdlib>


int main () {

    auto auth = Spotify::ExampleUtils::authenticateFromEnv();
    Spotify::Client client(auth);

    auto pb_opt = client.player().getCurrentlyPlayingTrack();


    if (!pb_opt.has_value()) {
        std::cout << "Nothing is playing (or private session is active)." << std::endl;
        return 0;
    }

    // Access the underlying object
    const auto& pb = *pb_opt;

    if (!pb.is_playing) {
        std::cout << "Playback is currently paused." << std::endl;
        return 0;
    }

    // handle both Track and Episode types
    std::visit([](auto&& arg) {
        if (arg) {
            // Check if the shared_ptr is valid
            std::cout << "Currently playing: " << arg->name;

            // If it's a TrackObject, it has an 'artists' vector
            using T = std::decay_t<decltype(*arg)>;
            if constexpr (std::is_same_v<T, Spotify::TrackObject>) {
                if (!arg->artists.empty()) {
                    std::cout << " by " << arg->artists[0].name;
                }
            }
            // If it's an EpisodeObject, it might have a 'show' name
            else if constexpr (std::is_same_v<T, Spotify::EpisodeObject>) {
                std::cout << " (Podcast Episode)";
            }

            std::cout << std::endl;
        }
    }, pb.item);

    return 0;
}