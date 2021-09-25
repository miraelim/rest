#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <curl/curl.h>
#include <json/json.h>
using namespace std;

int main()
{
	//	system("curl -o -X POST -H 'Content-Type: application/json' -d '{\"userId\": 1, \"date\": \"2019-08-28\", \"hours\": 6}'  http://example.com/api");
	//
	string filename= "test.json";
	string command = "curl -o  -X GET -w %{http_code} https://swapi.dev/api/species/3 -H 'Content-Type: application/json'>>";
	command+= filename;
	string s = " > stdout.txt 2>stderr";
	command+=s;

	const char* command1 = command.c_str();
	//curl execute
	system(command1);
	string str;
	ifstream file("stdout.txt");

	while (getline(file, str))
		cout << str << '\n';
	str = str.substr(str.length()-3,3);
	cout << str<<endl;

	//system("curl -X GET https://swapi.dev/api/species/3 -H 'Content-Type: application/json'>> test.json");
	//Reading 
	if(str!="200"){
		cout<< "connection Error"<<endl;
		return 0;
	}
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
