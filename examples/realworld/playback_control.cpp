//
// Created by Harry Skerritt on 01/01/2026.
//

#include <spotify/spotify.hpp>

using namespace Spotify;

// Example CLI Spotify Playback Controller
// Shows how to authenticate, retrieve the currently playing state
// Shows how to extract allowed actions and perform non-read actions such as play/pause


// Helper function
// Returns the next RepeatState in sequence: Off -> Context -> Track -> Off
// Wraps around automatically using modulo arithmetic
RepeatState nextRepeatState(RepeatState state) {
    return static_cast<RepeatState>(
        (static_cast<int>(state) + 1) % 3
    );
}

int main() {
    std::cout << "Starting " << getLibraryName()
             << " v" << getLibraryVersion() << std::endl;
    std::cout << "Copyright (c) 2025 Harry Skerritt" << std::endl;
    std::cout << "--------------------------------------------" << "\n" << std::endl;

    bool suppress = true; // Suppress console output during auth flow (optional)

    try {
        // Load Client Key and Secret from .env file
        // Either replace the path below with a path to your .env or hardcode the values to client_key and client_secret
        // Note: Make sure to keep your keys safe!
        std::string env_path = "/Volumes/Data/Code/C++/2025/SpotifyAPILib/.env";
        Tools::loadEnv(env_path);

        const char* client_key = std::getenv("SPOTIFY_CLIENT_KEY");
        const char* client_secret = std::getenv("SPOTIFY_CLIENT_SECRET");

        // Handle keys being absent
        if (!client_key || !client_secret) {
            throw std::runtime_error("SPOTIFY_CLIENT_KEY or SECRET not found in environment.");
        }

        // Create the authentication object
        Auth auth( {client_key, client_secret} );

        // Generate the authorisation url - Replace the redirectUri with the one for your spotify app
        auto url = auth.createAuthoriseURL(
            "http://127.0.0.1:8888/callback",
            {
                Scope::UserModifyPlaybackState,
                Scope::UserReadPlaybackState
            });


        // Open the URL and authenticate
        AuthServer::openBrowser(url);

        // Automatically handle the code coming in to the redirectURI
        std::string code = AuthServer::waitForCode(
            "127.0.0.1", 8888, std::nullopt, suppress);

        // Exchange the code for an authentication token
        auth.exchangeCode(code);

        // Show success message is enabled
        if (!suppress) {
            std::cout << "Authorization successful!" << std::endl;
        }

        // ************************************************************
        // *  Everything is successfully authenticated at this point  *
        // ************************************************************

        // Create a client
        Client client(auth);

        // The following variables track the current state for options such as shuffling
        bool is_shuffling;
        RepeatState repeat_state;
        bool is_playing;


        // The following variables indicate whether the current device allows each action
        // e.g. can_skip_forward = true if skipping to next track is allowed
        bool can_shuffle, can_repeat, can_skip_forward, can_skip_backward, can_play, can_pause;

        // Get the current player state - assign necessary values
        auto playback_state = client.player().getPlaybackState();
        if (playback_state.has_value()) {
            is_shuffling = playback_state->shuffle_state;
            repeat_state = playback_state->repeat_state;
            is_playing   = playback_state->is_playing;

            // Get the current player actions - assign values
            can_shuffle       = playback_state->actions.toggling_shuffle;
            can_skip_forward  = playback_state->actions.skipping_next;
            can_skip_backward = playback_state->actions.skipping_prev;
            can_play          = playback_state->actions.resuming;
            can_pause         = playback_state->actions.pausing;
            can_repeat        = playback_state->actions.toggling_repeat_context ||
                                 playback_state->actions.toggling_repeat_track;
        } else {
            std::cout << "Nothing is playing!!" << std::endl;
            return 0;
        }

        // Get the users input to allow player control until quit
        bool is_running = true;
        while (is_running) {

            // Clear screen and move cursor to top (ANSI escape codes)
            std::cout << "\033[2J\033[H";

            // Output the options
            std::cout << "--- Playback Controls ---" << std::endl;

            if (is_playing)
                std::cout << "  1. Pause " << std::endl;
            else
                std::cout << "  1. Play " << std::endl;

            if (can_skip_forward) std::cout << "  2. Skip Forward " << std::endl;
            if (can_skip_backward) std::cout << "  3. Skip Backward " << std::endl;
            if (can_shuffle) std::cout << "  4. Toggle Shuffle " << std::endl;
            if (can_repeat) std::cout << "  5. Toggle Repeat " << std::endl;
            std::cout << "  6. Quit App " << std::endl;

            std::cout << "Choose an option (1-6): ";
            std::string option_str;
            std::getline(std::cin, option_str);

            // Validate the input is a number
            int option = -1;
            try {
                option = std::stoi(option_str);
            }
            catch (const std::invalid_argument&) {
                std::cout << "Invalid input! Please enter a number.\n";
                continue;
            }
            catch (const std::out_of_range&) {
                std::cout << "Number out of range! Try again.\n";
                continue;
            }

            // Validate the input is within range
            if (option > 6 || option < 1) {
                std::cout << "Invalid option! - Try Again" << std::endl;
                continue;
            }

            // Handle the input by calling the right api endpoint
            switch (option) {
                case 1:
                    if (is_playing && can_pause) client.player().pausePlayback();
                    else if (!is_playing && can_play) client.player().startPlayback();
                    else std::cout << "Action not allowed on this device!" << std::endl;
                    break;
                case 2:
                    if (can_skip_forward) client.player().skipToNext();
                    else std::cout << "Cannot skip forward - Action not allowed on this device!" << std::endl;
                    break;
                case 3:
                    if (can_skip_backward) client.player().skipToPrevious();
                    else std::cout << "Cannot skip backwards - Action not allowed on this device!" << std::endl;
                    break;
                case 4:
                    if (can_shuffle) client.player().togglePlaybackShuffle(!is_shuffling);
                    else std::cout << "Cannot Shuffle - Action not allowed on this device!" << std::endl;
                    break;
                case 5:
                    if (can_repeat) client.player().setRepeatMode(nextRepeatState(repeat_state));
                    else std::cout << "Cannot Repeat - Action not allowed on this device!" << std::endl;
                    break;
                case 6:
                    is_running = false;
                    break;
                default: break;
            }

            // Get the current player state to keep in sync if another device alters
            playback_state = client.player().getPlaybackState();
            if (playback_state.has_value()) {
                is_shuffling = playback_state->shuffle_state;
                repeat_state = playback_state->repeat_state;
                is_playing   = playback_state->is_playing;

                can_shuffle       = playback_state->actions.toggling_shuffle;
                can_skip_forward  = playback_state->actions.skipping_next;
                can_skip_backward = playback_state->actions.skipping_prev;
                can_play          = playback_state->actions.resuming;
                can_pause         = playback_state->actions.pausing;
                can_repeat        = playback_state->actions.toggling_repeat_context ||
                                     playback_state->actions.toggling_repeat_track;
            } else {
                std::cout << "Nothing is playing!!" << std::endl;
                return 0;
            }
        }
    }
    // Catch any errors and display them in the console
    catch (const APIException& e) {
        std::cerr << "\n[Spotify API Error] Status: " << e.status()
                  << "\nReason: " << e.reason()
                  << "\nMessage: " << e.message() << std::endl;
        throw;
    }
    catch (const NetworkException& e) {
        std::cerr << "\n[Network Error] " << e.what() << std::endl;
        throw;
    }
    catch (const LogicException& e) {
        std::cerr << "\n[Configuration Error] " << e.what() << std::endl;
        throw;
    }
    catch (const Exception& e) {
        std::cerr << "\n[Library Error] " << e.what() << std::endl;
        throw;
    }
    catch (const std::exception& e) {
        std::cerr << "\n[Standard Exception] " << e.what() << std::endl;
        throw;
    }

    return 0;
}

