#pragma once

inline void initDynamics()
{
	app.Get("/lightswitch/api/service/bulk/status", [](const Request& req, Response& res)
	{
		const auto j =
		R"(
		[{
			"serviceInstanceId": "fortcommunism",
			"status": "UP",
			"message": "Neocommunism++",
			"maintenanceUri": null,
			"allowedActions": ["PLAY", "DOWNLOAD"],
			"banned": false
		}]
		)";
		res.set_content(j, "application/json");
	});

	app.Get(R"(/fortcommunism/api/v2/versioncheck/(.*))", [](const Request& req, Response& res)
	{
		const auto j = R"({"type": "NO_UPDATE"})"_json;
		res.set_content(j.dump(), "application/json");
	});

	app.Get("/content/api/pages/fortcommunism-game/", [](const Request& req, Response& res)
	{
		json j = fortcommunismGame();
		res.set_content(j.dump(), "application/json");
	});

	app.Get("/fortcommunism/api/calendar/v1/timeline", [](const Request& req, Response& res)
	{
		json j = calendar();
		res.set_content(j.dump(), "application/json");
	});

	app.Get("/account/api/public/account", [](const Request& req, Response& res)
	{
		auto account_id = req.get_param_value("accountId");
		json j;
		j[0] = {
			{"id", account_id},
			{"displayName", account_id},
			{"externalAuths", json({})}
		};
		res.set_content(j.dump(), "application/json");
	});

	app.Get(R"(/account/api/public/account/(.*))", [](const Request& req, Response& res)
	{
		auto account_id = static_cast<std::string>(req.matches[1]);
		json j = {
			{"id", account_id},
			{"displayName", account_id},
			{"externalAuths", json({})}
		};
		res.set_content(j.dump(), "application/json");
	});

	app.Get(R"(/fortcommunism/api/game/v2/privacy/account/(.*))", [](const Request& req, Response& res)
	{
		auto account_id = static_cast<std::string>(req.matches[1]);
		json j = {
			{"accountId", account_id},
			{"optOutOfPublicLeaderboards", false}
		};
		res.set_content(j.dump(), "application/json");
	});

	app.Post("/api/v1/user/setting", [](const Request& req, Response& res)
	{
		const auto j =
		R"(
          [{
              "accountId": "neocommunismuseridplaceholder",
              "key": "avatar",
              "value": "cid_005_athena_commando_m_default"
          }, {
              "accountId": "neocommunismuseridplaceholder",
              "key": "avatarBackground",
              "value": "[\"#8EFDE5\",\"#1CBA9E\",\"#034D3F\"]"
          }, {
              "accountId": "neocommunismuseridplaceholder",
              "key": "appInstalled",
              "value": "init"
          }]
		)"_json;
		res.set_content(j.dump(), "application/json");
	});

	app.Get("/api/v1/Fortcommunism/get", [](const Request& req, Response& res)
	{
		const auto j =
		R"({"interactions": []})"_json;

		res.set_content(j.dump(), "application/json");
	});

	app.Get(R"(/friends/api/v1/(.*)/settings)", [](const Request& req, Response& res)
	{
		const auto j =
		R"(
        {
        "friends": [],
        "incoming": [],
        "outgoing": [],
        "suggested": [],
        "blocklist": [],
        "settings": {"acceptInvites": "public"},
        "limitsReached": {"incoming": false, "outgoing": false, "accepted": false}
        }
		)"_json;

		res.set_content(j.dump(), "application/json");
	});

	app.Get(R"(/friends/api/v1/(.*)/summary)", [](const Request& req, Response& res)
	{
		json j = {
			{"acceptInvites", "public"}
		};
		res.set_content(j.dump(), "application/json");
	});

	app.Post(R"(/fortcommunism/api/game/v2/tryPlayOnPlatform/account/(.*))", [](const Request& req, Response& res)
	{
		res.set_content("true", "text/plain");
	});

	app.Get(R"(/affiliate/api/public/affiliates/slug/(.*))", [](const Request& req, Response& res)
	{
		const auto j =
		R"({"bans":[],"warnings":[]})"_json;
		res.set_content(j.dump(), "application/json");
	});

	app.Get(R"(/party/api/v1/Fortcommunism/user/(.*))", [](const Request& req, Response& res)
	{
		const auto j = R"({ "current": [], "pending": [], "invites": [], "pings": [] })"_json;
		res.set_content(j.dump(), "application/json");
	});

	app.Get("/fortcommunism/api/storefront/v2/catalog", [](const Request& req, Response& res)
	{
		res.status = 204;
	});

	app.Get("/fortcommunism/api/cloudstorage/system/config", [](const Request& req, Response& res)
	{
		res.status = 204;
	});


	app.Post(R"(/api/v1/assets/Fortcommunism/(.*))", [](const Request& req, Response& res)
	{
		const auto j =
		R"(
		        {
        "FortPlaylistAthena": {
        "meta": {
            "promotion": 0
          },
         "assets": {}
          }
        }
		)"_json;
		res.set_content(j.dump(), "application/json");
	});
}
