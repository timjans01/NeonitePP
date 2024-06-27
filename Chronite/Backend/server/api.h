/**
 * Copyright (c) 2020-2021 Kareem Olim (Kemo)
 * All Rights Reserved. Licensed under the Neo License
 * https://neocommunism.dev/LICENSE.html
 */

#pragma once
#include "DefaultGame.h"
#include "DefaultEngine.h"
#include "DefaultRuntimeOptions.h"
#include "../../Frontend/settings.h"

#define GALACTUS_AES_KEY XOR("C60475E046D0F0FBCFE6DE6F9E040E0E:Wc6IzWuqnm7EHqcSx14i6KwXwl4+PmQq180ESMdR+08=")
#define TRAVIS_AES_KEY XOR("8734362B2A2A8B0FBC9EDE6160627E1D:8ZsoLeTeezxjoIxnNfUrNf61XfqMEKfnyTb3u4o/X6g=")
#define DEVICE_AES_KEY XOR("F51C8301B1C9BE9D4C4F48ED2C0FE067:+MsgNTH4cF1Mr4mjNVZVgsf3GBgjSjYn2yRZn2fE70A=")

inline void initApi()
{
	app.Get("/fortcommunism/api/cloudstorage/system", [](const Request& req, Response& res)
	{
		json j = json::array({
			{
				{"uniqueFilename", DefaultGame::name},
				{"filename", DefaultGame::name},
				{"hash", DefaultGame::sha1},
				{"hash256", DefaultGame::sha256},
				{"length", DefaultGame::ini.size()},
				{"contentType", "application/octet-stream"},
				{"uploaded", "2021-01-03T21:17:16.703Z"},
				{"storageType", "S3"},
				{"doNotCache", false}
			},
			{
				{"uniqueFilename", DefaultEngine::name},
				{"filename", DefaultEngine::name},
				{"hash", DefaultEngine::sha1},
				{"hash256", DefaultEngine::sha256},
				{"length", DefaultEngine::ini.size()},
				{"contentType", "application/octet-stream"},
				{"uploaded", "2021-01-03T21:17:16.703Z"},
				{"storageType", "S3"},
				{"doNotCache", false}
			},
			{
				{"uniqueFilename", DefaultRuntimeOptions::name},
				{"filename", DefaultRuntimeOptions::name},
				{"hash", DefaultRuntimeOptions::sha1},
				{"hash256", DefaultRuntimeOptions::sha256},
				{"length", DefaultRuntimeOptions::ini.size()},
				{"contentType", "application/octet-stream"},
				{"uploaded", "2021-01-03T21:17:16.703Z"},
				{"storageType", "S3"},
				{"doNotCache", false}
			}
		});
		res.set_content(j.dump(), "application/json");
	});

	app.Get("/fortcommunism/api/cloudstorage/system/DefaultGame.ini", [](const Request& req, Response& res)
	{
		boost::replace_all(DefaultGame::ini, "'", "\"");
		res.set_content(DefaultGame::ini, "application/octet-stream");
	});

	app.Get("/fortcommunism/api/cloudstorage/system/DefaultEngine.ini", [](const Request& req, Response& res)
	{
		res.set_content(DefaultEngine::ini, "application/octet-stream");
	});

	app.Get("/fortcommunism/api/cloudstorage/system/DefaultRuntimeOptions.ini", [](const Request& req, Response& res)
	{
		res.set_content(DefaultRuntimeOptions::ini, "application/octet-stream");
	});

	//Keychain
	app.Get("/fortcommunism/api/storefront/v2/keychain", [](const Request& req, Response& res)
	{
		Client cli("https://api.communismstats.com");

		auto j = R"(["A93064DA8BDA456CADD2CD316BE64EE5:nziBPQTfuEl4IRK6pOaovQpqQC6nsMQZFTx+DEg62q4=:CID_NEOcommunism_TEMP"])"_json;

		if (auto response = cli.Get("/v1/epic/keychain"))
		{
			if (response->status == 200)
			{
				j.clear();
				j = json::parse(response->body);
			}
		}

		//Events aes keys.
		j.push_back(GALACTUS_AES_KEY);
		j.push_back(TRAVIS_AES_KEY);
		j.push_back(DEVICE_AES_KEY);
		res.set_content(j.dump(), "application/json");
	});

	//OAuth
	app.Get("/account/api/oauth/verify", [](const Request& req, Response& res)
	{
		auto token = static_cast<std::string>(req.get_header_value("Authorization"));
		token.erase(token.begin(), token.begin() + 7);
		json j = {
			{"access_token", token},
			{"expires_in", 28800},
			{"expires_at", "9999-12-31T23:59:59.999Z"},
			{"token_type", "bearer"},
			{"refresh_token", "neocommunismpprefreshtokenplaceholder"},
			{"refresh_expires", 115200},
			{"refresh_expires_at", "9999-12-31T23:59:59.999Z"},
			{"account_id", "neocommunismpp"},
			{"client_id", "neocommunismppclientidplaceholderkekw"},
			{"internal_client", "true"},
			{"client_service", "fortcommunism"},
			{"displayName", "neocommunismppplayer"},
			{"app", "fortcommunism"},
			{"in_app_id", "neocommunismpp"},
			{"device_id", "neocommunismppdeviceidplaceholderkekw"}
		};
		res.set_content(j.dump(), "application/json");
	});

	app.Post("/account/api/oauth/token", [](const Request& req, Response& res)
	{
		json j;
		if (util::getQuery(req.body, "grant_type") == "client_credentials")
		{
			j = {
				{"access_token", util::genRandom(32)},
				{"expires_in", 28800},
				{"expires_at", "9999-12-31T23:59:59.999Z"},
				{"token_type", "bearer"},
				{"client_id", "neocommunismppclientidplaceholderkekw"},
				{"internal_client", "true"},
				{"client_service", "fortcommunism"},
			};
		}
		else
		{
			std::string displayName;
			const std::string body = util::urlDecode(req.body);

			if (util::getQuery(body, "email") != "failed")
			{
				displayName = util::sSplit(util::getQuery(body, "email"), "@");
			}
			else if (util::getQuery(body, "username") != "failed")
			{
				displayName = util::sSplit(util::getQuery(body, "username"), "@");
			}
			else displayName = "NeocommunismPPUser";

			j = {
				{"access_token", util::genRandom(32)},
				{"expires_in", 28800},
				{"expires_at", "9999-12-31T23:59:59.999Z"},
				{"token_type", "bearer"},
				{"account_id", displayName},
				{"client_id", "neocommunismppclientidplaceholderkekw"},
				{"internal_client", true},
				{"client_service", "fortcommunism"},
				{"displayName", displayName},
				{"app", "fortcommunism"},
				{"in_app_id", displayName},
				{"device_id", "neocommunismdeviceidplaceholderkekw"}
			};
		}

		res.set_content(j.dump(), "application/json");
	});
}
