#pragma once
#include <iostream>
#include <string>
using namespace std;
class DataGeter
{
private:
	string fileContent;
	string filePath;
public:
	DataGeter();
	DataGeter(string filePath);
	~DataGeter();
	string getFileContent();
	void displayData();
};

