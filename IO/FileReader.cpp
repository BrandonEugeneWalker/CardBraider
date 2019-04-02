#include "FileReader.h"

namespace io
{

FileReader::FileReader()
{
    //ctor
}

FileReader::~FileReader()
{
    //dtor
}

vector<BaseballCard> FileReader::loadFile(string fileName)
{
    if (fileName == "")
    {
        throw invalid_argument("file name cannot be empty");
    }
    fstream inputFile;
    inputFile.open(fileName);

    while (! inputFile.eof())
    {
        string currentLine;
        getline(inputFile, currentLine);
        parseLine(currentLine);
    }
    inputFile.close();
    return this -> loadedCards;
}

int FileReader::parseCondition(string condition)
{
    int returnInt = 5;
    if (condition == "Poor")
    {
        returnInt = 0;
    }
    else if (condition == "Good")
    {
        returnInt = 1;
    }
    else if (condition == "Excellent")
    {
        returnInt = 2;
    }
    else if (condition == "Mint")
    {
        returnInt = 3;
    }
    else if (condition == "Pristine")
    {
        returnInt = 4;
    }
    return returnInt;
}


void FileReader::parseLine(string line)
{
    char* errorMessage = new char;
    vector<string> cardVariables;
    istringstream lineStream(line, ios_base::in);
    string result;
    while(getline(lineStream, result, ','))
    {
        cardVariables.push_back(result);
    }
    string lastName = cardVariables[0];
    string firstName = cardVariables[1];
    int year = UTILS_H::toInt(cardVariables[2], errorMessage);
    int intCondition = parseCondition(cardVariables[3]);
    BaseballCard::Condition condition = static_cast<BaseballCard::Condition>(intCondition);
    int value = UTILS_H::toInt(cardVariables[4], errorMessage);

    BaseballCard cardToAdd(firstName, lastName, year, condition, value);
    this -> loadedCards.push_back(cardToAdd);
}

}
