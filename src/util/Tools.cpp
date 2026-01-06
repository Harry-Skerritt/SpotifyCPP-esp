//
// Created by Harry Skerritt on 20/12/2025.
//
#include <algorithm>

#include "../../include/spotify/util/common/Tools.hpp"
#include "spotify/core/Errors.hpp"

#include <iomanip>
#include <iterator>
#include <cctype>


namespace Spotify {

    // --- TOOLS ---
    void Tools::loadEnv(const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            throw Spotify::Exception("Failed to load environment file: " + filename);
        }

        std::string line;
        while (std::getline(file, line)) {
            if (line.empty() || line[0] == '#') continue;
            auto pos = line.find('=');
            if (pos == std::string::npos) continue;

            std::string key = line.substr(0, pos);
            std::string value = line.substr(pos + 1);

            setenv(key.c_str(), value.c_str(), 1); // overwrite if exists
        }
    }


    static const std::string valid_markets[185] = {
        "AD","AE","AG","AL","AM","AO","AR","AT","AU","AZ",
        "BA","BB","BD","BE","BF","BG","BH","BI","BJ","BN",
        "BO","BR","BS","BT","BW","BY","BZ","CA","CD","CG",
        "CH","CI","CL","CM","CO","CR","CV","CW","CY","CZ",
        "DE","DJ","DK","DM","DO","DZ","EC","EE","EG","ES",
        "ET","FI","FJ","FM","FR","GA","GB","GD","GE","GH",
        "GM","GN","GQ","GR","GT","GW","GY","HK","HN","HR",
        "HT","HU","ID","IE","IL","IN","IQ","IS","IT","JM",
        "JO","JP","KE","KG","KH","KI","KM","KN","KR","KW",
        "KZ","LA","LB","LC","LI","LK","LR","LS","LT","LU",
        "LV","LY","MA","MC","MD","ME","MG","MH","MK","ML",
        "MN","MO","MR","MT","MU","MV","MW","MX","MY","MZ",
        "NA","NE","NG","NI","NL","NO","NP","NR","NZ","OM",
        "PA","PE","PG","PH","PK","PL","PR","PS","PT","PW",
        "PY","QA","RO","RS","RW","SA","SB","SC","SE","SG",
        "SI","SK","SL","SM","SN","SR","ST","SV","SZ","TD",
        "TG","TH","TJ","TL","TN","TO","TR","TT","TV","TW",
        "TZ","UA","UG","US","UY","UZ","VC","VE","VN","VU",
        "WS","XK","ZA","ZM","ZW"
    };

    bool Tools::isValidMarket(const std::string& market) {
        if (market.length() != 2) return false;

        std::string upper = market;
        std::transform(upper.begin(), upper.end(), upper.begin(),
                       [](unsigned char c){ return std::toupper(c); });

        // std::begin(array) works on both C-style arrays and vectors
        return std::binary_search(std::begin(valid_markets), std::end(valid_markets), upper);
    }

    std::string Tools::getISOTimestamp() {
        auto now = std::chrono::system_clock::now();
        std::time_t now_c = std::chrono::system_clock::to_time_t(now);

        char buf[25]; // Enough for "YYYY-MM-DDTHH:MM:SSZ"
        std::strftime(buf, sizeof(buf), "%Y-%m-%dT%H:%M:%SZ", std::gmtime(&now_c));

        return std::string(buf);
    }

    std::string Tools::formatMs(long long ms) {
        auto dur = std::chrono::milliseconds(ms);
        auto mins = std::chrono::duration_cast<std::chrono::minutes>(dur).count();
        auto secs = std::chrono::duration_cast<std::chrono::seconds>(dur).count() % 60;

        std::ostringstream oss;
        oss << mins << ":" << std::setw(2) << std::setfill('0') << secs;
        return oss.str();
    }

}

