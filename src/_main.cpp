#include <Geode/Geode.hpp>
#include <Geode/ui/GeodeUI.hpp>

#include "zip_file.hpp"

using namespace geode::prelude;

#define REMOVE_UI getMod()->getSettingValue<bool>("REMOVE_UI")

//here is a custom shared level format ".level" like ".gmd2", saves sfx and almost all level values.
namespace level {

    auto LOADED_FILES_CHECKPOINTS = std::map<std::filesystem::path, size_t>{};

    matjson::Value jsonFromLevel(GJGameLevel* level) {
        level = level ? level : GJGameLevel::create();
        matjson::Value json;
        json["levelID"] = level->m_levelID.value();
        json["levelName"] = level->m_levelName.c_str();
        json["levelDesc"] = level->m_levelDesc.c_str();
        json["levelString"] = level->m_levelString.c_str();
        json["creatorName"] = level->m_creatorName.c_str();
        json["recordString"] = level->m_recordString.c_str();
        json["uploadDate"] = level->m_uploadDate.c_str();
        json["updateDate"] = level->m_updateDate.c_str();
        json["unkString1"] = level->m_unkString1.c_str();
        json["unkString2"] = level->m_unkString2.c_str();
        { // CCPoint m_unkPoint
            matjson::Value pt;
            pt["x"] = level->m_unkPoint.x;
            pt["y"] = level->m_unkPoint.y;
            json["unkPoint"] = pt;
        }
        json["userID"] = level->m_userID.value();
        json["accountID"] = level->m_accountID.value();
        json["difficulty"] = static_cast<int>(level->m_difficulty);
        json["audioTrack"] = level->m_audioTrack;
        json["songID"] = level->m_songID;
        json["levelRev"] = level->m_levelRev;
        json["unlisted"] = level->m_unlisted;
        json["friendsOnly"] = level->m_friendsOnly;
        json["objectCount"] = level->m_objectCount.value();
        json["levelIndex"] = level->m_levelIndex;
        json["ratings"] = level->m_ratings;
        json["ratingsSum"] = level->m_ratingsSum;
        json["downloads"] = level->m_downloads;
        json["isEditable"] = level->m_isEditable;
        json["gauntletLevel"] = level->m_gauntletLevel;
        json["gauntletLevel2"] = level->m_gauntletLevel2;
        json["workingTime"] = level->m_workingTime;
        json["workingTime2"] = level->m_workingTime2;
        json["lowDetailMode"] = level->m_lowDetailMode;
        json["lowDetailModeToggled"] = level->m_lowDetailModeToggled;
        json["disableShakeToggled"] = level->m_disableShakeToggled;
        json["selected"] = level->m_selected;
        json["localOrSaved"] = level->m_localOrSaved;
        json["disableShake"] = level->m_disableShake;
        json["isVerified"] = level->m_isVerified.value();
        json["isVerifiedRaw"] = level->m_isVerifiedRaw;
        json["isUploaded"] = level->m_isUploaded;
        json["hasBeenModified"] = level->m_hasBeenModified;
        json["levelVersion"] = level->m_levelVersion;
        json["gameVersion"] = level->m_gameVersion;
        json["attempts"] = level->m_attempts.value();
        json["jumps"] = level->m_jumps.value();
        json["clicks"] = level->m_clicks.value();
        json["attemptTime"] = level->m_attemptTime.value();
        json["chk"] = level->m_chk;
        json["isChkValid"] = level->m_isChkValid;
        json["isCompletionLegitimate"] = level->m_isCompletionLegitimate;
        json["normalPercent"] = level->m_normalPercent.value();
        json["orbCompletion"] = level->m_orbCompletion.value();
        json["newNormalPercent2"] = level->m_newNormalPercent2.value();
        json["practicePercent"] = level->m_practicePercent;
        json["likes"] = level->m_likes;
        json["dislikes"] = level->m_dislikes;
        json["levelLength"] = level->m_levelLength;
        json["featured"] = level->m_featured;
        json["isEpic"] = level->m_isEpic;
        json["levelFavorited"] = level->m_levelFavorited;
        json["levelFolder"] = level->m_levelFolder;
        json["dailyID"] = level->m_dailyID.value();
        json["demon"] = level->m_demon.value();
        json["demonDifficulty"] = level->m_demonDifficulty;
        json["stars"] = level->m_stars.value();
        json["autoLevel"] = level->m_autoLevel;
        json["coins"] = level->m_coins;
        json["coinsVerified"] = level->m_coinsVerified.value();
        json["password"] = level->m_password.value();
        json["originalLevel"] = level->m_originalLevel.value();
        json["twoPlayerMode"] = level->m_twoPlayerMode;
        json["failedPasswordAttempts"] = level->m_failedPasswordAttempts;
        json["firstCoinVerified"] = level->m_firstCoinVerified.value();
        json["secondCoinVerified"] = level->m_secondCoinVerified.value();
        json["thirdCoinVerified"] = level->m_thirdCoinVerified.value();
        json["starsRequested"] = level->m_starsRequested;
        json["showedSongWarning"] = level->m_showedSongWarning;
        json["starRatings"] = level->m_starRatings;
        json["starRatingsSum"] = level->m_starRatingsSum;
        json["maxStarRatings"] = level->m_maxStarRatings;
        json["minStarRatings"] = level->m_minStarRatings;
        json["demonVotes"] = level->m_demonVotes;
        json["rateStars"] = level->m_rateStars;
        json["rateFeature"] = level->m_rateFeature;
        json["rateUser"] = level->m_rateUser.c_str();
        json["dontSave"] = level->m_dontSave;
        json["levelNotDownloaded"] = level->m_levelNotDownloaded;
        json["requiredCoins"] = level->m_requiredCoins;
        json["isUnlocked"] = level->m_isUnlocked;
        { // CCPoint m_lastCameraPos
            matjson::Value pt;
            pt["x"] = level->m_lastCameraPos.x;
            pt["y"] = level->m_lastCameraPos.y;
            json["lastCameraPos"] = pt;
        }
        json["fastEditorZoom"] = level->m_fastEditorZoom;
        json["lastBuildTab"] = level->m_lastBuildTab;
        json["lastBuildPage"] = level->m_lastBuildPage;
        json["lastBuildGroupID"] = level->m_lastBuildGroupID;
        json["levelType"] = static_cast<int>(level->m_levelType);
        json["M_ID"] = level->m_M_ID;
        json["tempName"] = level->m_tempName.c_str();
        json["capacityString"] = level->m_capacityString.c_str();
        json["highObjectsEnabled"] = level->m_highObjectsEnabled;
        json["unlimitedObjectsEnabled"] = level->m_unlimitedObjectsEnabled;
        json["personalBests"] = level->m_personalBests.c_str();
        json["timestamp"] = level->m_timestamp;
        json["listPosition"] = level->m_listPosition;
        json["songIDs"] = level->m_songIDs.c_str();
        json["sfxIDs"] = level->m_sfxIDs.c_str();
        json["field_54"] = level->m_54;
        json["bestTime"] = level->m_bestTime;
        json["bestPoints"] = level->m_bestPoints;
        json["k111"] = level->m_k111;
        json["unkString3"] = level->m_unkString3.c_str();
        json["unkString4"] = level->m_unkString4.c_str();
        return json;
    }

    void updateLevelByJson(const matjson::Value& json, GJGameLevel* level) {
        //log::debug("{} update by json: {}", level, json.dump());
#define asInt(member, ...) level->m_##member = __VA_ARGS__(json[#member""].asInt().unwrapOr(static_cast<int>(level->m_##member)));
#define asSeed(member) level->m_##member = json[#member""].as<int>().unwrapOr(level->m_##member.value());
#define asString(member) level->m_##member = json[#member""].asString().unwrapOr(level->m_##member.data()).data();
#define asDouble(member) level->m_##member = json[#member""].asDouble().unwrapOr(level->m_##member);
#define asBool(member) level->m_##member = json[#member""].asBool().unwrapOr(level->m_##member);

        asSeed(levelID);
        asString(levelName);// = json["levelName"].().().c_str();
        asString(levelDesc);// = json["levelDesc"].asString().unwrapOr().c_str();
        asString(levelString);// = json["levelString"].asString().unwrapOr().c_str();
        asString(creatorName);// = json["creatorName"].asString().unwrapOr().c_str();
        asString(recordString);// = json["recordString"].asString().unwrapOr().c_str();
        asString(uploadDate);// = json["uploadDate"].asString().unwrapOr().c_str();
        asString(updateDate);// = json["updateDate"].asString().unwrapOr().c_str();
        asString(unkString1);// = json["unkString1"].asString().unwrapOr().c_str();
        asString(unkString2);// = json["unkString2"].asString().unwrapOr().c_str();
        { // CCPoint m_unkPoint
            matjson::Value pt = json["unkPoint"];
            asDouble(unkPoint.x);// = pt["x"].asDouble().unwrapOr();
            asDouble(unkPoint.y);// = pt["y"].asDouble().unwrapOr();
        }
        asSeed(userID);// = json["userID"].asInt().unwrapOr();
        asSeed(accountID);// = json["accountID"].asInt().unwrapOr();
        asInt(difficulty, static_cast<GJDifficulty>);// = (json["difficulty"].asInt().unwrapOr());
        asInt(audioTrack);// = json["audioTrack"].asInt().unwrapOr();
        asInt(songID);// = json["songID"].asInt().unwrapOr();
        asInt(levelRev);// = json["levelRev"].asInt().unwrapOr();
        asBool(unlisted);// = json["unlisted"].asBool().unwrapOr();
        asBool(friendsOnly);// = json["friendsOnly"].asBool().unwrapOr();
        asSeed(objectCount);// = json["objectCount"].asInt().unwrapOr();
        asInt(levelIndex);// = json["levelIndex"].asInt().unwrapOr();
        asInt(ratings);// = json["ratings"].asInt().unwrapOr();
        asInt(ratingsSum);// = json["ratingsSum"].asInt().unwrapOr();
        asInt(downloads);// = json["downloads"].asInt().unwrapOr();
        asBool(isEditable);// = json["isEditable"].asBool().unwrapOr();
        asBool(gauntletLevel);// = json["gauntletLevel"].asBool().unwrapOr();
        asBool(gauntletLevel2);// = json["gauntletLevel2"].asBool().unwrapOr();
        asInt(workingTime);// = json["workingTime"].asInt().unwrapOr();
        asInt(workingTime2);// = json["workingTime2"].asInt().unwrapOr();
        asBool(lowDetailMode);// = json["lowDetailMode"].asBool().unwrapOr();
        asBool(lowDetailModeToggled);// = json["lowDetailModeToggled"].asBool().unwrapOr();
        asBool(disableShakeToggled);// = json["disableShakeToggled"].asBool().unwrapOr();
        asBool(selected);// = json["selected"].asBool().unwrapOr();
        asBool(localOrSaved);// = json["localOrSaved"].asBool().unwrapOr();
        asBool(disableShake);// = json["disableShake"].asBool().unwrapOr();
        asSeed(isVerified);// = json["isVerified"].asInt().unwrapOr();
        asBool(isVerifiedRaw);// = json["isVerifiedRaw"].asBool().unwrapOr();
        asBool(isUploaded);// = json["isUploaded"].asBool().unwrapOr();
        asBool(hasBeenModified);// = json["hasBeenModified"].asBool().unwrapOr();
        asInt(levelVersion);// = json["levelVersion"].asInt().unwrapOr();
        asInt(gameVersion);// = json["gameVersion"].asInt().unwrapOr();
        asSeed(attempts);// = json["attempts"].asInt().unwrapOr();
        asSeed(jumps);// = json["jumps"].asInt().unwrapOr();
        asSeed(clicks);// = json["clicks"].asInt().unwrapOr();
        asSeed(attemptTime);// = json["attemptTime"].asInt().unwrapOr();
        asInt(chk);// = json["chk"].asInt().unwrapOr();
        asBool(isChkValid);// = json["isChkValid"].asBool().unwrapOr();
        asBool(isCompletionLegitimate);// = json["isCompletionLegitimate"].asBool().unwrapOr();
        asSeed(normalPercent);// = json["normalPercent"].asInt().unwrapOr();
        asSeed(orbCompletion);// = json["orbCompletion"].asInt().unwrapOr();
        asSeed(newNormalPercent2);// = json["newNormalPercent2"].asInt().unwrapOr();
        asInt(practicePercent);// = json["practicePercent"].asInt().unwrapOr();
        asInt(likes);// = json["likes"].asInt().unwrapOr();
        asInt(dislikes);// = json["dislikes"].asInt().unwrapOr();
        asInt(levelLength);// = json["levelLength"].asInt().unwrapOr();
        asInt(featured);// = json["featured"].asInt().unwrapOr();
        asInt(isEpic);// = json["isEpic"].asInt().unwrapOr();
        asBool(levelFavorited);// = json["levelFavorited"].asBool().unwrapOr();
        asInt(levelFolder);// = json["levelFolder"].asInt().unwrapOr();
        asSeed(dailyID);// = json["dailyID"].asInt().unwrapOr();
        asSeed(demon);// = json["demon"].asInt().unwrapOr();
        asInt(demonDifficulty);// = json["demonDifficulty"].asInt().unwrapOr();
        asSeed(stars);// = json["stars"].asInt().unwrapOr();
        asBool(autoLevel);// = json["autoLevel"].asBool().unwrapOr();
        asInt(coins);// = json["coins"].asInt().unwrapOr();
        asSeed(coinsVerified);// = json["coinsVerified"].asInt().unwrapOr();
        asSeed(password);// = json["password"].asInt().unwrapOr();
        asSeed(originalLevel);// = json["originalLevel"].asInt().unwrapOr();
        asBool(twoPlayerMode);// = json["twoPlayerMode"].asBool().unwrapOr();
        asInt(failedPasswordAttempts);// = json["failedPasswordAttempts"].asInt().unwrapOr();
        asSeed(firstCoinVerified);// = json["firstCoinVerified"].asInt().unwrapOr();
        asSeed(secondCoinVerified);// = json["secondCoinVerified"].asInt().unwrapOr();
        asSeed(thirdCoinVerified);// = json["thirdCoinVerified"].asInt().unwrapOr();
        asInt(starsRequested);// = json["starsRequested"].asInt().unwrapOr();
        asBool(showedSongWarning);// = json["showedSongWarning"].asBool().unwrapOr();
        asInt(starRatings);// = json["starRatings"].asInt().unwrapOr();
        asInt(starRatingsSum);// = json["starRatingsSum"].asInt().unwrapOr();
        asInt(maxStarRatings);// = json["maxStarRatings"].asInt().unwrapOr();
        asInt(minStarRatings);// = json["minStarRatings"].asInt().unwrapOr();
        asInt(demonVotes);// = json["demonVotes"].asInt().unwrapOr();
        asInt(rateStars);// = json["rateStars"].asInt().unwrapOr();
        asInt(rateFeature);// = json["rateFeature"].asInt().unwrapOr();
        asString(rateUser);// = json["rateUser"].asString().unwrapOr().c_str();
        asBool(dontSave);// = json["dontSave"].asBool().unwrapOr();
        asBool(levelNotDownloaded);// = json["levelNotDownloaded"].asBool().unwrapOr();
        asInt(requiredCoins);// = json["requiredCoins"].asInt().unwrapOr();
        asBool(isUnlocked);// = json["isUnlocked"].asBool().unwrapOr();
        { // CCPoint m_lastCameraPos
            matjson::Value pt = json["lastCameraPos"];
            asDouble(lastCameraPos.x);// = pt["x"].asDouble().unwrapOr();
            asDouble(lastCameraPos.y);// = pt["y"].asDouble().unwrapOr();
        }
        asDouble(fastEditorZoom);// = json["fastEditorZoom"].asDouble().unwrapOr();
        asInt(lastBuildTab);// = json["lastBuildTab"].asInt().unwrapOr();
        asInt(lastBuildPage);// = json["lastBuildPage"].asInt().unwrapOr();
        asInt(lastBuildGroupID);// = json["lastBuildGroupID"].asInt().unwrapOr();
        asInt(levelType, static_cast<GJLevelType>);// = (json["levelType"].asInt().unwrapOr());
        asInt(M_ID);// = json["M_ID"].asInt().unwrapOr();
        asString(tempName);// = json["tempName"].asString().unwrapOr().c_str();
        asString(capacityString);// = json["capacityString"].asString().unwrapOr().c_str();
        asBool(highObjectsEnabled);// = json["highObjectsEnabled"].asBool().unwrapOr();
        asBool(unlimitedObjectsEnabled);// = json["unlimitedObjectsEnabled"].asBool().unwrapOr();
        asString(personalBests);// = json["personalBests"].asString().unwrapOr().c_str();
        asInt(timestamp);// = json["timestamp"].asInt().unwrapOr();
        asInt(listPosition);// = json["listPosition"].asInt().unwrapOr();
        asString(songIDs);// = json["songIDs"].asString().unwrapOr().c_str();
        asString(sfxIDs);// = json["sfxIDs"].asString().unwrapOr().c_str();
        //asInt(54);// = json["field_54"].asInt().unwrapOr();
        asInt(bestTime);// = json["bestTime"].asInt().unwrapOr();
        asInt(bestPoints);// = json["bestPoints"].asInt().unwrapOr();
        asInt(k111);// = json["k111"].asInt().unwrapOr();
        asString(unkString3);// = json["unkString3"].asString().unwrapOr().c_str();
        asString(unkString4);// = json["unkString4"].asString().unwrapOr().c_str();

#undef asInt//(member, ...) level->m_##member = __VA_ARGS__(json[#member""].asInt().unwrapOr(static_cast<int>(level->m_##member)));
#undef asSeed//(member) level->m_##member = json[#member""].as<int>().unwrapOr(level->m_##member.value());
#undef asString//(member) level->m_##member = json[#member""].asString().unwrapOr(level->m_##member.data()).data();
#undef asDouble//(member) level->m_##member = json[#member""].asDouble().unwrapOr(level->m_##member);
#undef asBool//(member) level->m_##member = json[#member""].asBool().unwrapOr(level->m_##member);
    }

    geode::Result<matjson::Value> exportLevelFile(
        GJGameLevel* level,
        std::filesystem::path const& to
    ) {
        if (!level) return Err("level ptr is null.");
        if (!typeinfo_cast<GJGameLevel*>(level)) return Err("level ptr is not GJGameLevel typed in RTTI.");

        miniz_cpp::zip_file file;

        auto json = jsonFromLevel(level);
        file.writestr("_data.json", json.dump());

        //primary song id isnt 0
        if (level->m_songID) {
            //path
            std::filesystem::path path = MusicDownloadManager::sharedState()->pathForSong(
                level->m_songID
            ).c_str();
            path = CCFileUtils::get()->fullPathForFilename(path.string().c_str(), 0).c_str();
            //add if exists
            if (fileExistsInSearchPaths(path.string().c_str())) {
                file.write(path.string(), std::filesystem::path(path).filename().string());
            }
        }

        //fe the ids from list
        for (auto id : string::split(level->m_songIDs, ",")) {
            //path
            std::filesystem::path path = MusicDownloadManager::sharedState()->pathForSong(
                utils::numFromString<int>(id).unwrapOrDefault()
            ).c_str();
            path = CCFileUtils::get()->fullPathForFilename(path.string().c_str(), 0).c_str();
            //add if exists
            if (fileExistsInSearchPaths(path.string().c_str())) {
                file.write(path.string(), std::filesystem::path(path).filename().string());
            };
        }

        //fe the ids from list
        for (auto id : string::split(level->m_sfxIDs, ",")) {
            //path
            std::filesystem::path path = MusicDownloadManager::sharedState()->pathForSFX(
                utils::numFromString<int>(id).unwrapOrDefault()
            ).c_str();
            path = CCFileUtils::get()->fullPathForFilename(path.string().c_str(), 0).c_str();
            //add if exists
            if (fileExistsInSearchPaths(path.string().c_str())) {
                file.write(path.string(), std::filesystem::path(path).filename().string());
            }
        }

        file.save(to.string());

        return Ok(json);
    };

    geode::Result<GJGameLevel*> importLevelFile(
        std::filesystem::path const& from,
        GJGameLevel* level = GJGameLevel::create()
    ) {
        if (!level) return Err("level ptr is null.");
        if (!typeinfo_cast<GJGameLevel*>(level)) return Err("level ptr is not GJGameLevel typed in RTTI.");

        miniz_cpp::zip_file file(from.string());

        auto tempFile = (dirs::getTempDir() / GEODE_MOD_ID"-unzip.temp");

        GEODE_UNWRAP_INTO(auto data, matjson::parse(file.read("_data.json")));
        updateLevelByJson(data, level);

        log::debug("data from zip: {}", data.dump());

        //primary song id isnt 0
        if (level->m_songID) {
            //path
            std::filesystem::path path = MusicDownloadManager::sharedState()->pathForSong(level->m_songID).c_str();
            path = CCFileUtils::get()->fullPathForFilename(path.string().c_str(), 0).c_str();
            if (!fileExistsInSearchPaths(path.string().c_str())) {
                auto atzip = std::filesystem::path(path).filename().string();
                auto str = file.read(file.getinfo(atzip));
                std::vector<uint8_t> bin(str.begin(), str.end());
                GEODE_UNWRAP(file::writeBinary(path, bin));
            };
        }

        for (auto id : string::split(level->m_songIDs, ",")) {
            //path
            std::filesystem::path path = MusicDownloadManager::sharedState()->pathForSong(
                utils::numFromString<int>(id).unwrapOrDefault()
            ).c_str();
            path = CCFileUtils::get()->fullPathForFilename(path.string().c_str(), 0).c_str();
            //add if exists
            if (!fileExistsInSearchPaths(path.string().c_str())) {
                auto atzip = std::filesystem::path(path).filename().string();
                auto str = file.read(file.getinfo(atzip));
                std::vector<uint8_t> bin(str.begin(), str.end());
                GEODE_UNWRAP(file::writeBinary(path, bin));
            }
        }

        for (auto id : string::split(level->m_sfxIDs, ",")) {
            //path
            std::filesystem::path path = MusicDownloadManager::sharedState()->pathForSFX(
                utils::numFromString<int>(id).unwrapOrDefault()
            ).c_str();
            path = CCFileUtils::get()->fullPathForFilename(path.string().c_str(), 0).c_str();
            //add if exists
            if (!fileExistsInSearchPaths(path.string().c_str())) {
                auto atzip = std::filesystem::path(path).filename().string();
                auto str = file.read(file.getinfo(atzip));
                std::vector<uint8_t> bin(str.begin(), str.end());
                GEODE_UNWRAP(file::writeBinary(path, bin));
            }
        }

        return Ok(level);
    };

    auto forceStats(
        GJGameLevel* level,
        bool verified = false, bool basic = true, bool online = true, bool bests = true,
        GJGameLevel* refLevel = GJGameLevel::create()
    ) {
        //verified
        if (verified) {
            level->m_coinsVerified = refLevel->m_coinsVerified;
            level->m_firstCoinVerified = refLevel->m_firstCoinVerified;
            level->m_secondCoinVerified = refLevel->m_secondCoinVerified;
            level->m_thirdCoinVerified = refLevel->m_thirdCoinVerified;
            level->m_isVerified = refLevel->m_isVerified;
            level->m_isVerifiedRaw = refLevel->m_isVerifiedRaw;
        }
        //basic
        if (basic) {
            level->m_attempts = refLevel->m_attempts;
            level->m_jumps = refLevel->m_jumps;
            level->m_clicks = refLevel->m_clicks;
            level->m_attemptTime = refLevel->m_attemptTime;
            level->m_normalPercent = refLevel->m_normalPercent;
            level->m_orbCompletion = refLevel->m_orbCompletion;
            level->m_newNormalPercent2 = refLevel->m_newNormalPercent2;
            level->m_practicePercent = refLevel->m_practicePercent;
        };
        //online
        if (online) {
            level->m_likes = refLevel->m_likes;
            level->m_dislikes = refLevel->m_dislikes;
            level->m_starRatings = refLevel->m_starRatings;
            level->m_starRatingsSum = refLevel->m_starRatingsSum;
            level->m_maxStarRatings = refLevel->m_maxStarRatings;
            level->m_minStarRatings = refLevel->m_minStarRatings;
            level->m_demonVotes = refLevel->m_demonVotes;
            level->m_rateStars = refLevel->m_rateStars;
            level->m_rateFeature = refLevel->m_rateFeature;
        }
        //bests
        if (bests) {
            level->m_bestTime = refLevel->m_bestTime;
            level->m_bestPoints = refLevel->m_bestPoints;
            level->m_personalBests = refLevel->m_personalBests.c_str();
        }
        return level;
    }

    auto forceStatsFrom(GJGameLevel* level, GJGameLevel* refLevel) {
        return forceStats(
            level, 1, 1, 1, 1,
            refLevel
        );
    }

}

namespace mle {

    GJGameLevel* tryLoadFromFiles(GJGameLevel* level, int customLvlID = 0, bool appendSubDir = false) {
        auto levelID = customLvlID ? customLvlID : level->m_levelID;
        auto subdir = appendSubDir ? "levels/" : "";

        auto levelFileName = fmt::format("{}{}.level", subdir, levelID);
        if (fileExistsInSearchPaths(levelFileName.c_str())) {
            auto path = CCFileUtils::get()->fullPathForFilename(levelFileName.c_str(), 0);
            level = level::importLevelFile(path.c_str()).unwrapOr(level);
        }
        else log::debug("don't exists in searchpaths: {}", levelFileName.c_str());

        if (!appendSubDir) return tryLoadFromFiles(level, customLvlID, true);
        return level;
    };

    GJGameLevel* tryLoadFromFiles(int customLvlID) {
        return tryLoadFromFiles(GJGameLevel::create(), customLvlID);
    }

    std::vector<int> getListingIDs() {
        auto rtn = std::vector<int>();

        for (auto entry : string::split(getMod()->getSettingValue<std::string>("LEVELS_LISTING"), ",")) {
            //sequence
            if (string::contains(entry, ":")) {
                auto seq = string::split(entry, ":");
                auto start = utils::numFromString<int>(seq[0]).unwrapOr(0);
                auto end = utils::numFromString<int>(seq[1]).unwrapOr(0);
                bool ew = start > end;//1:-22
                for (int q = start; ew ? q != (end - 1) : q != (end + 1); ew ? --q : ++q) {
                    auto id = q;
                    //log::debug("{} (\"{}\")", id, entry);
                    rtn.push_back(id);
                }
            }
            //single id
            else {
                auto id = utils::numFromString<int>(entry).unwrapOr(0);
                //log::debug("{} (\"{}\")", id, entry);
                rtn.push_back(id);
            }
        }

        return rtn;
    }

}

// genius name
class ConfigureLevelFileDataPopup : public geode::Popup<LevelEditorLayer*, std::filesystem::path> {
protected:
    bool setup(LevelEditorLayer* editor, std::filesystem::path related_File) override {

        auto scroll = ScrollLayer::create({
            this->m_buttonMenu->getContentSize().width * 0.86f,
            this->m_buttonMenu->getContentSize().height - 10.5f,
            });
        scroll->ignoreAnchorPointForPosition(0);
        this->m_buttonMenu->addChildAtPosition(scroll, Anchor::Center, { 0.f, 0.0f });

        auto json = level::jsonFromLevel(editor->m_level);
        for (auto asd : json) {
            auto key = asd.getKey().value_or("unnamed obj");
            if (string::containsAny(key, { "levelString" })) continue;

            auto layer = CCLayerColor::create({ 0,0,0,42 });
            layer->setContentWidth(scroll->getContentWidth());
            layer->setContentHeight(34.000f);

            if (string::containsAny(key, { "difficulty","stars","requiredCoins","Name","song","sfx","Track" })) layer->setOpacity(90);

            auto keyLabel = SimpleTextArea::create(key);
            keyLabel->setAnchorPoint({ 0.f, 0.5f });
            layer->addChildAtPosition(keyLabel, Anchor::Left, { 12, 0 });

            auto keyInputErr = SimpleTextArea::create("")->getLines()[0];
            keyInputErr->setColor(ccRED);
            keyInputErr->setZOrder(2);
            keyInputErr->setScale(0.6f);
            layer->addChildAtPosition(keyInputErr, Anchor::BottomLeft, { 6.f, 12.f });

            auto keyValInput = TextInput::create(132.f, key, keyLabel->getFont());

            keyValInput->setString(asd.dump());
            keyValInput->setCallback([json, key, editor, keyInputErr](auto str) { //INPUT CALLBACK

                keyInputErr->setString("");

                auto parse = matjson::parse(str);
                if (parse.isOk()) {
                    auto copy = matjson::Value(json);
                    copy[key] = parse.unwrapOrDefault();
                    level::updateLevelByJson(copy, editor->m_level);
                }
                else {
                    if (parse.err().has_value()) keyInputErr->setString(("parse err: " + parse.err().value().message).c_str());
                };

                }); //INPUT CALLBACK

            auto bgSize = keyValInput->getBGSprite()->getContentSize();
            keyValInput->getBGSprite()->setSpriteFrame(CCSprite::create("groundSquare_18_001.png")->displayFrame());
            keyValInput->getBGSprite()->setContentSize(bgSize);

            layer->addChildAtPosition(keyValInput, Anchor::Right, { -72.f, 0 });

            layer->setZOrder(scroll->m_contentLayer->getChildrenCount());
            layer->setTag(scroll->m_contentLayer->getChildrenCount());
            scroll->m_contentLayer->addChild(layer);
        }
        scroll->m_contentLayer->setLayout(RowLayout::create()
            ->setGrowCrossAxis(1)
            ->setAxisReverse(1)
        );
        scroll->scrollToTop();

        auto bottomMenuPaddingX = 6.f;
        auto bottomMenuY = -16.f;

        CCMenuItemSpriteExtra* save_level = CCMenuItemExt::createSpriteExtra(
            SimpleTextArea::create("SAVE LEVEL")->getLines()[0],
            [editor, related_File](auto) {
                editor->getLevelString();
                auto pause = EditorPauseLayer::create(editor);
                pause->saveLevel();
                auto result = level::exportLevelFile(editor->m_level, related_File);
                if (result.isErr()) Notification::create(
                    "failed to export level: " + result.err().value_or("unknown error"),
                    NotificationIcon::Error
                )->show();
                else Notification::create("level saved to file!", NotificationIcon::Info)->show();
            }
        );
        save_level->m_scaleMultiplier = 0.95;
        save_level->setID("save_level"_spr);
        save_level->setAnchorPoint({ 1.f, 0.5f });
        this->m_buttonMenu->addChildAtPosition(save_level, Anchor::BottomRight, { -bottomMenuPaddingX, bottomMenuY });

        CCMenuItemSpriteExtra* sort = CCMenuItemExt::createSpriteExtra(
            SimpleTextArea::create("move to top main levels related values")->getLines()[0],
            [scroll](auto) {
                findFirstChildRecursive<CCLayerColor>(scroll->m_contentLayer, [](auto me) {
                    if (me->getOpacity() == 90) me->setZOrder(me->getZOrder() == me->getTag() ? -1 : me->getTag());
                    return false;
                    });
                scroll->m_contentLayer->updateLayout();
                scroll->scrollToTop();
            }
        );
        sort->m_scaleMultiplier = 0.97;
        sort->setID("sort"_spr);
        sort->setAnchorPoint({ 0.f, 0.5f });
        this->m_buttonMenu->addChildAtPosition(sort, Anchor::BottomLeft, { bottomMenuPaddingX, bottomMenuY });

        auto bottomMenuBG = CCScale9Sprite::create("groundSquare_01_001.png");
        bottomMenuBG->setColor(ccBLACK);
        bottomMenuBG->setOpacity(190);
        bottomMenuBG->setID("bottomMenuBG"_spr);
        bottomMenuBG->setContentSize({
                this->m_buttonMenu->getContentSize().width,
                22.000f
            });
        bottomMenuBG->setZOrder(-1);
        this->m_buttonMenu->addChildAtPosition(bottomMenuBG, Anchor::Bottom, { 0.f, bottomMenuY });

        this->m_mainLayer->setPositionY(this->m_mainLayer->getPositionY() + fabs(bottomMenuY / 2));

        return true;
    }

public:
    static ConfigureLevelFileDataPopup* create(LevelEditorLayer* editor, std::filesystem::path related_File) {
        auto ret = new ConfigureLevelFileDataPopup();
        if (ret->initAnchored(410.000f, 262.000f, editor, related_File)) {
            ret->autorelease();
            return ret;
        }
        delete ret;
        return nullptr;
    }
};

void ModLoaded() {
    auto sp = std::vector<std::filesystem::path>{};
    sp.push_back(getMod()->getSaveDir());
    sp.push_back(getMod()->getConfigDir());
    sp.push_back(getMod()->getResourcesDir());
    sp.push_back(getMod()->getPersistentDir());
    for (auto p : sp) CCFileUtils::get()->addPriorityPath(p.string().c_str());
}
$on_mod(Loaded) { ModLoaded(); }

#include <Geode/modify/LocalLevelManager.hpp>
class $modify(MLE_LocalLevelManager, LocalLevelManager) {

    inline static gd::unordered_map<int, matjson::Value> m_mainLevelsInJSON;

    bool init() {
        if (!LocalLevelManager::init()) return false;

        log::debug("loading .level files by list {}", mle::getListingIDs());
        for (auto id : mle::getListingIDs()) {

            log::debug("loading level {}", id);

            auto level = GJGameLevel::create();
            level->m_levelName = "level is not loaded";
            level = mle::tryLoadFromFiles(level, id);

            log::debug("{}", level->m_levelName.c_str());
            if (std::string(level->m_levelName.c_str()) != "level is not loaded") {

                log::debug("loaded level {}", id);

                if (std::string(level->m_levelString.c_str()).empty()) void();
                else m_mainLevels[id] = level->m_levelString;

                log::debug("level {} string size is {}", id, std::string(level->m_levelString.c_str()).size());

                m_mainLevelsInJSON[id] = level::jsonFromLevel(level);

                log::debug("level {} json size is {}", id, m_mainLevelsInJSON[id].dump().size());
            }
            else log::debug(".level file for {} was not founded", id);
        }

        return false;
    }

};

#include <Geode/modify/GameLevelManager.hpp>
class $modify(MLE_GameLevelManager, GameLevelManager) {

    GJGameLevel* getMainLevel(int levelID, bool dontGetLevelString) {
        auto level = GameLevelManager::getMainLevel(levelID, dontGetLevelString);

        if (MLE_LocalLevelManager::m_mainLevelsInJSON.contains(levelID)) {
            /*log::debug(
                "MLE_LocalLevelManager::m_mainLevelsInJSON[{}]->{}", 
                levelID, MLE_LocalLevelManager::m_mainLevelsInJSON[levelID].dump()
            );*/
            auto loadedLevel = GJGameLevel::create();
            level::updateLevelByJson(MLE_LocalLevelManager::m_mainLevelsInJSON[levelID], loadedLevel);
            //xd
            level->m_levelString = loadedLevel->m_levelString.c_str();
            level->m_stars = (loadedLevel->m_stars.value());
            level->m_requiredCoins = loadedLevel->m_requiredCoins;
            level->m_levelName = loadedLevel->m_levelName;
            level->m_audioTrack = loadedLevel->m_audioTrack;
            level->m_demon = (loadedLevel->m_demon.value());
            level->m_twoPlayerMode = loadedLevel->m_twoPlayerMode;
            level->m_difficulty = loadedLevel->m_difficulty;
            level->m_capacityString = loadedLevel->m_capacityString;
            level->m_levelID = (levelID);
            level->m_timestamp = loadedLevel->m_timestamp;
            level->m_levelLength = loadedLevel->m_levelLength;
        };

        level->m_levelID = levelID; // -1, -2 for listing exists. no default id pls
        level->m_levelType = GJLevelType::Local;
        level->m_levelString = dontGetLevelString ? "" : level->m_levelString.c_str();

        return level;
    };

};

#include <Geode/modify/LevelTools.hpp>
class $modify(MLE_LevelTools, LevelTools) {

    static bool verifyLevelIntegrity(gd::string p0, int p1) {
        LevelTools::verifyLevelIntegrity(p0, p1);//huh
        return 1;
    }

};
#if 0
#include <Geode/modify/LevelSelectLayer.hpp>
class $modify(MLE_LevelSelectExt, LevelSelectLayer) {

    inline static int LastPlayedPage;
    inline static int LastPlayedPageLevelID;
    inline static int ForceNextTo;

    struct Fields {
        EventListener<Task<Result<std::filesystem::path>>> m_pickListener;
    };

    virtual void keyDown(cocos2d::enumKeyCodes p0) {
        LevelSelectLayer::keyDown(p0);
        if (this) if (auto a = getParent()) if (auto scroll = typeinfo_cast<BoomScrollLayer*>(a->getParent())) {
            MLE_LevelSelectExt::ForceNextTo = scroll->pageNumberForPosition(this->getPosition());
        }
    }

    bool init(int page) {
        /*
        log::debug("page={}", aw);
        log::debug("BoomScrollLayerExt::LastPlayedPage={}", BoomScrollLayerExt::LastPlayedPage);
        log::debug("BoomScrollL::LastPlayedPageLevelID={}", BoomScrollLayerExt::LastPlayedPageLevelID);
        :                             page=332
        BoomScrollL::LastPlayedPageLevelID=333
        BoomScrollLayerExt::LastPlayedPage=0
        */
        if (page + 1 == MLE_LevelSelectExt::LastPlayedPageLevelID) {
            page = MLE_LevelSelectExt::LastPlayedPage;
        };

        if (ForceNextTo) {
            page = ForceNextTo;
            ForceNextTo = 0;
        }

        if (!LevelSelectLayer::init(page)) return false;

        //bottom-center-menu
        if (!REMOVE_UI) {
            auto menu = CCMenu::create();
            this->addChild(menu);

            CCMenuItemSpriteExtra* settings = CCMenuItemExt::createSpriteExtra(
                SimpleTextArea::create("open mod settings")->getLines()[0],
                [this](auto) {
                    openSettingsPopup(getMod(), 1);
                }
            );
            settings->setID("settings"_spr);
            menu->addChild(settings);

            CCMenuItemSpriteExtra* reload_levels_cache = CCMenuItemExt::createSpriteExtra(
                SimpleTextArea::create("reload levels cache")->getLines()[0],
                [this](auto) {
                    LocalLevelManager::get()->init();
                    this->getParent()->addChild(LevelSelectLayer::create(this->m_scrollLayer->m_page));
                    this->removeFromParent();
                    Notification::create("local level manager was reinitialized", NotificationIcon::Info)->show();
                }
            );
            reload_levels_cache->setID("reload_levels_cache"_spr);
            menu->addChild(reload_levels_cache);

            CCMenuItemSpriteExtra* load_level = CCMenuItemExt::createSpriteExtra(
                SimpleTextArea::create("open .level file")->getLines()[0],
                [this](auto) {
                    auto IMPORT_PICK_OPTIONS = file::FilePickOptions{
                        std::nullopt, {{ "Extended Shared Level File", { "*.level" } }}
                    };
                    //IMPORT_PICK_OPTIONS.defaultPath;
                    m_fields->m_pickListener.bind([this](Task<Result<std::filesystem::path>>::Event* event)
                        {
                            if (auto result = event->getValue()) if (result->isOk()) {
                                auto path = result->unwrap();
                                path = string::endsWith(path.string(), ".level") ? path : std::filesystem::path(path.string() + ".level");
                                auto level_import = level::importLevelFile(path);
                                if (level_import.isOk()) {
                                    auto level = level_import.unwrapOrDefault();
                                    auto pages = CCArray::create();
                                    pages->addObject(LevelInfoLayer::create(level, 0));
                                    pages->addObject(EditLevelLayer::create(level));
                                    pages->addObject([level] {
                                        auto a = LevelPage::create(level);
                                        a->updateDynamicPage(level);
                                        return a;
                                        }());
                                    auto layer = BoomScrollLayer::create(pages, 0, 0);
                                    layer->m_extendedLayer->runAction(CCSequence::create(
                                        CCEaseBackOut::create(CCMoveBy::create(1.0f, { -42.f, 0.f })),
                                        CCEaseExponentialIn::create(CCMoveBy::create(0.5f, { 42.f, 0.f })),
                                        CallFuncExt::create([layer] { layer->moveToPage(layer->m_page); }),
                                        nullptr
                                    ));
                                    layer->addChild(createLayerBG(), -36);
                                    auto hideaway = [layer](std::string id) {while (auto background = layer->getChildByIDRecursive(id)) {
                                        background->setVisible(0);
                                        background->setID("hidden-" + id);
                                    }};
                                    hideaway("background");
                                    hideaway("bottom-left-art");
                                    hideaway("bottom-right-art");
                                    if (auto a1 = layer->getChildByIDRecursive("LevelPage"))
                                        if (auto a2 = a1->getChildByIDRecursive("hidden-background"))
                                            a2->setVisible(1);
                                    layer->setPagesIndicatorPosition({ 74.f, layer->getContentHeight() - (320.000f - 312.000f) });
                                    {
                                        auto dotsBG = CCScale9Sprite::create("square02_small.png");
                                        dotsBG->setPosition(layer->m_dotPosition);
                                        dotsBG->setAnchorPoint(CCPointMake(0.5f, 0.1f));
                                        dotsBG->setContentSize(CCSizeMake(52.f, 77.f));
                                        dotsBG->setOpacity(122);
                                        layer->addChild(dotsBG, 0);
                                    }
                                    switchToScene(layer);
                                }
                                else {
                                    //aaaa msg
                                    Notification::create("failed to load level!", NotificationIcon::Warning)->show();
                                    //and err
                                    if (level_import.err()) Notification::create(
                                        level_import.err().value_or("UNK ERROR")
                                        , NotificationIcon::Error
                                    )->show();
                                }
                            }
                            else FLAlertLayer::create("Failed to get picked path", result->unwrapErr(), "OK")->show();
                        }
                    );
                    m_fields->m_pickListener.setFilter(file::pick(file::PickMode::OpenFile, IMPORT_PICK_OPTIONS));
                }
            );
            load_level->setID("export_level"_spr);
            menu->addChild(load_level);

            CCMenuItemSpriteExtra* edit_level = CCMenuItemExt::createSpriteExtra(
                SimpleTextArea::create("edit .level file")->getLines()[0],
                [this](auto) {
                    auto IMPORT_PICK_OPTIONS = file::FilePickOptions{
                        std::nullopt, {{ "Extended Shared Level File", { "*.level" } }}
                    };
                    //IMPORT_PICK_OPTIONS.defaultPath;
                    m_fields->m_pickListener.bind([this](Task<Result<std::filesystem::path>>::Event* event)
                        {
                            if (auto result = event->getValue()) if (result->isOk()) {
                                auto path = result->unwrap();
                                path = string::endsWith(path.string(), ".level") ? path : std::filesystem::path(path.string() + ".level");
                                auto level_import = level::importLevelFile(path);
                                if (level_import.isOk()) {
                                    auto level = level_import.unwrapOrDefault();
                                    auto layer = LevelEditorLayer::create(level, 0);
                                    if (auto menu = layer->getChildByIDRecursive("settings-menu")) {

                                        auto specialSettings = CCMenuItemExt::createSpriteExtraWithFrameName(
                                            "GJ_optionsBtn_001.png", 0.800f, [layer, path](auto) {
                                                ConfigureLevelFileDataPopup::create(layer, path)->show();
                                            }
                                        );
                                        menu->addChild(specialSettings);

                                        menu->setContentSize(CCSizeMake(105.f, 45.f));
                                        menu->setLayout(RowLayout::create()
                                            ->setCrossAxisOverflow(0)
                                            ->setGrowCrossAxis(1)
                                            ->setAxisReverse(1)
                                        );
                                    }
                                    switchToScene(layer);
                                }
                                else {
                                    //aaaa msg
                                    Notification::create("failed to load level!", NotificationIcon::Warning)->show();
                                    //and err
                                    if (level_import.err()) Notification::create(
                                        level_import.err().value_or("UNK ERROR")
                                        , NotificationIcon::Error
                                    )->show();
                                }
                            }
                            else FLAlertLayer::create("Failed to get picked path", result->unwrapErr(), "OK")->show();
                        }
                    );
                    m_fields->m_pickListener.setFilter(file::pick(file::PickMode::OpenFile, IMPORT_PICK_OPTIONS));
                }
            );
            edit_level->setID("edit_level"_spr);
            menu->addChild(edit_level);

            menu->setPosition(CCPointMake(107.5f, 113.f));
            menu->setLayout(ColumnLayout::create());

            auto size = cocos::calculateChildCoverage(menu);
            auto menu_bg = CCLayerColor::create({ 0, 0, 0, 90 }, size.size.width, size.size.height);
            menu_bg->setID("menu_bg"_spr);
            menu_bg->setScale(1.075f);
            menu->addChild(menu_bg, -10);
        };

        m_scrollLayer->m_dynamicObjects->removeAllObjects();

        //LEVELS_LISTING
        for (auto id : mle::getListingIDs()) {
            m_scrollLayer->m_dynamicObjects->addObject(GameLevelManager::get()->getMainLevel(id, 0));
        }
        m_scrollLayer->setupDynamicScrolling(m_scrollLayer->m_dynamicObjects, this);
        m_scrollLayer->moveToPage(m_scrollLayer->m_page);

        return true;
    }

};

#include <Geode/modify/LevelPage.hpp>
class $modify(MLE_LevelPageExt, LevelPage) {

    void updateDynamicPage(GJGameLevel * p0) {
        LevelPage::updateDynamicPage(p0);
        //difficultySprite
        if (auto difficultySprite = typeinfo_cast<CCSprite*>(this->getChildByIDRecursive("difficulty-sprite"))) {
            std::string frameName = GJDifficultySprite::getDifficultyFrame((int)p0->m_difficulty, GJDifficultyName::Short).data();
            frameName = string::replace(frameName, "difficulty", "diffIcon");
            if (auto frame = CCSpriteFrameCache::get()->spriteFrameByName(frameName.data()))
                difficultySprite->setDisplayFrame(frame);
        }
        //debg
        if (!REMOVE_UI) {
            this->removeChildByTag(179823);
            this->addChild(SimpleTextArea::create(fmt::format(
                "                                                                       id: {}\n \n \n \n \n \n \n "
                , p0->m_levelID.value()
            )), 1, 179823);
        }
    }

    void onPlay(cocos2d::CCObject * sender) {
        if (this) if (auto a = getParent()) if (auto scroll = typeinfo_cast<BoomScrollLayer*>(a->getParent())) {
            MLE_LevelSelectExt::LastPlayedPage = scroll->pageNumberForPosition(this->getPosition());
            MLE_LevelSelectExt::LastPlayedPageLevelID = this->m_level->m_levelID.value();
        }
        LevelPage::onPlay(sender);

    }

    void onSecretDoor(cocos2d::CCObject * sender) {
        if (this) if (auto a = getParent()) if (auto scroll = typeinfo_cast<BoomScrollLayer*>(a->getParent())) {
            MLE_LevelSelectExt::ForceNextTo = scroll->pageNumberForPosition(this->getPosition());
        }
        LevelPage::onSecretDoor(sender);
    }

    void onTheTower(cocos2d::CCObject * sender) {
        if (this) if (auto a = getParent()) if (auto scroll = typeinfo_cast<BoomScrollLayer*>(a->getParent())) {
            MLE_LevelSelectExt::ForceNextTo = scroll->pageNumberForPosition(this->getPosition());
        }
        LevelPage::onTheTower(sender);
    }

};
#endif

#include <Geode/modify/PauseLayer.hpp>
class $modify(MLE_PauseExt, PauseLayer) {

    struct Fields {
        EventListener<Task<Result<std::filesystem::path>>> m_pickListener;
    };

    void addControlUI() {
        if (REMOVE_UI) return;
        if (auto menu = this->getChildByIDRecursive("bottom-button-menu")) {
            CCMenuItemSpriteExtra* export_level = CCMenuItemExt::createSpriteExtra(
                SimpleTextArea::create("export into .level file")->getLines()[0],
                [this](CCMenuItem*) {
                    auto level = GameManager::get()->getPlayLayer()->m_level;
                    auto IMPORT_PICK_OPTIONS = file::FilePickOptions{
                        std::nullopt, {{ "Extended Shared Level File", { "*.level" } }}
                    };
                    IMPORT_PICK_OPTIONS.defaultPath = getMod()->getConfigDir() / fmt::format("{}.level", level->m_levelID.value());
                    m_fields->m_pickListener.bind([this, level](Task<Result<std::filesystem::path>>::Event* event)
                        {
                            if (auto result = event->getValue()) if (result->isOk()) {
                                //path
                                auto path = string::endsWith( //result->unwrap()result->unwrap()result->unwrap()
                                    result->unwrapOrDefault().string(), ".level" //str ends w .lvl
                                ) ? result->unwrapOrDefault() : std::filesystem::path(result->unwrapOrDefault().string() + ".level");
                                //dir
                                auto dir = path.parent_path();
                                //exporting.
                                auto level_export = level::exportLevelFile(level, path);
                                if (level_export.isOk()) {
                                    auto dbg_json = level_export.unwrapOrDefault();
                                    dbg_json["levelString"] = dbg_json["levelString"].asString().unwrapOrDefault().erase(36, 9999999) + "...";

                                    auto body = std::stringstream();

                                    body << """" "`  File:` [" + path.string() + "](file:///" + string::replace(path.string(), " ", "%20") + ")";
                                    body << "\n";
                                    body << "\n" "`   Dir:` [" + dir.string() + "](file:///" + string::replace(dir.string(), " ", "%20") + ")";
                                    body << "\n";
                                    body << "\n" "```";
                                    body << "\n" "zip tree of \"" << std::filesystem::path(path).filename().string() << "\": ";
                                    auto unzip = file::Unzip::create(path);
                                    if (unzip.err()) body
                                        << "\n" "FAILED TO OPEN CREATED ZIP!"
                                        << "\n" << unzip.err().value_or("unk err");
                                    else for (auto entry : unzip.unwrap().getEntries()) body
                                        << "\n- " << entry.string();
                                    body << "\n" "```";
                                    body << "\n";
                                    body << "\n" "```";
                                    body << "\n" "data \"" << std::filesystem::path(path).filename().string() << "\": ";
                                    for (auto entry : dbg_json) body
                                        << "\n- " << entry.getKey().value_or("unk") + ": " << entry.dump();
                                    body << "\n" "```";

                                    MDPopup::create(
                                        "Level Exported!",
                                        body.str(),
                                        "Ok"
                                    )->show();
                                }
                                else {
                                    //aaaa msg
                                    Notification::create("failed to save level!", NotificationIcon::Warning)->show();
                                    //and err
                                    if (level_export.err()) Notification::create(
                                        level_export.err().value_or("UNK ERROR")
                                        , NotificationIcon::Error
                                    )->show();
                                    log::error("{}", level_export.err());
                                }
                            }
                            else FLAlertLayer::create("Failed to get picked path", result->unwrapErr(), "OK")->show();
                        }
                    );
                    m_fields->m_pickListener.setFilter(file::pick(file::PickMode::SaveFile, IMPORT_PICK_OPTIONS));
                }
            );
            export_level->setID("export_level"_spr);
            menu->addChild(export_level);
            menu->getLayout() ? menu->updateLayout() : menu->setLayout(RowLayout::create());
        };
    }

    virtual void customSetup() {
        PauseLayer::customSetup();
        addControlUI();
    }

};
