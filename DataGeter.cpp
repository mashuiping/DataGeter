#include "DataGeter.h"
#include <fstream>

DataGeter::DataGeter()
{
}

DataGeter::DataGeter(string filePath)
{
	this->filePath = filePath;
}


DataGeter::~DataGeter()
{
}

string DataGeter::getFileContent()
{
	fstream getData;
	char tempLine[1024];
	getData.open(filePath, fstream::in | fstream::out | fstream::app);
	while (!getData.eof()) {
		getData.getline(tempLine, 1024);
		fileContent.append(tempLine).append("\n");
	}
	return fileContent;
}

void DataGeter::displayData()
{
	cout << fileContent;
}
