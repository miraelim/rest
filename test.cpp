#include <cstdint>
#include <iostream>
#include <memory>
#include <string>

#include <curl/curl.h>
#include <json/json.h>
using namespace std;
namespace
{
	std::size_t callback(
			const char* in,
			std::size_t size,
			std::size_t num,
			std::string* out)
	{
		const std::size_t totalBytes(size * num);
		out->append(in, totalBytes);
		return totalBytes;
	}
}

int main()
{
	const std::string url("https://swapi.dev/api/species/3/");

	CURL* curl = curl_easy_init();
	curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
	curl_easy_setopt(curl, CURLOPT_IPRESOLVE, CURL_IPRESOLVE_V4);

	curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10);
	curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

	long httpCode(0);
	std::unique_ptr<std::string> httpData(new std::string());


	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callback);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, httpData.get());

	curl_easy_perform(curl);
	curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &httpCode);
	curl_easy_cleanup(curl);


	if (httpCode == 200)
	{
		std::cout << "\nGot successful response from " << url << std::endl;


		Json::Value jsonData;
		Json::Reader jsonReader;

		if (jsonReader.parse(*httpData.get(), jsonData))
		{
			std::cout << "Successfully parsed JSON data" << std::endl;
			std::cout << "\nJSON data received:" << std::endl;
			std::cout << jsonData.toStyledString() << std::endl;

			Json::Reader reader;
			Json::Value root;

			std::string s(jsonData.toStyledString());
			reader.parse(s, root, false);

			auto entriesArray = root["films"];

			auto firstelem = entriesArray[0];
			const std::string array(firstelem.asString());
			const std::string dateString(jsonData["average_height"].asString());
			const std::string unixTimeMs(
					jsonData["average_lifespan"].asString());
			const std::string timeString(jsonData["created"].asString());

			std::cout << "Natively parsed:" << std::endl;
			std::cout << "\tArray: " ;
				cout << array<<endl;
			std::cout << "\tDate string: " << dateString << std::endl;
			std::cout << "\tUnix timeMs: " << unixTimeMs << std::endl;
			std::cout << "\tTime string: " << timeString << std::endl;
			std::cout << std::endl;
		}
		else
		{
			std::cout << "Could not parse HTTP data as JSON" << std::endl;
			std::cout << "HTTP data was:\n" << *httpData.get() << std::endl;
			return 1;
		}
	}
	else
	{
		std::cout << "Couldn't GET from " << url << " - exiting" << std::endl;
		return 1;
	}

	return 0;
}
