#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <curl/curl.h>
#include <json/json.h>
using namespace std;

int main()
{
	//	system("curl -X POST -H 'Content-Type: application/json' -d '{\"userId\": 1, \"date\": \"2019-08-28\", \"hours\": 6}'  http://example.com/api");
	//
	string filename= "test.json";
	string command = "curl -X GET https://swapi.dev/api/species/3 -H 'Content-Type: application/json'>>";
	command+= filename;
	const char* command1 = command.c_str();
	//curl execute
	system(command1);
	//system("curl -X GET https://swapi.dev/api/species/3 -H 'Content-Type: application/json'>> test.json");
	//Reading 
	Json::Value root;
	Json::Reader reader;
	ifstream t;
	t.open("test.json");
	if (!reader.parse(t, root)) {

		cout << "Parsing Failed!!" << endl;
		return 0;

	}

	for (auto it = root.begin(); it != root.end(); it++)
	{
		std::cout << it.key() << ": " << (*it) << std::endl;
	}
	cout << root["average_height"].asString()<<endl;
	return 0;
}
