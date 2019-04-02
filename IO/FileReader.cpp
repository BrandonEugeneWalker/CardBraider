#include "FileReader.h"

#define DIAGNOSTIC_OUTPUT

#ifdef DIAGNOSTIC_OUTPUT
#include <iostream>
#endif

namespace io
{

FileReader::FileReader()
{
    #ifdef DIAGNOSTIC_OUTPUT
        cout << "FileReader Constructor:" << endl;
    #endif
}

FileReader::~FileReader()
{
    #ifdef DIAGNOSTIC_OUTPUT
        cout << "FileReader Destructor:" << endl;
    #endif
}

vector<BaseballCard*> FileReader::loadFile(string fileName)
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

BaseballCard::Condition FileReader::parseCondition(string condition)
{
    string upperCondition = UTILS_H::toUpperCase(condition);

    #ifdef DIAGNOSTIC_OUTPUT
        cout << "Current Condition To Parse: " << upperCondition << endl;
    #endif

    BaseballCard::Condition parsedCondition = BaseballCard::Condition::UNKNOWN;
    if (upperCondition == "POOR")
    {
        parsedCondition = BaseballCard::Condition::POOR;
    }
    else if (upperCondition == "GOOD")
    {
        parsedCondition = BaseballCard::Condition::GOOD;
    }
    else if (upperCondition == "EXCELLENT")
    {
        parsedCondition = BaseballCard::Condition::EXCELLENT;
    }
    else if (upperCondition == "MINT")
    {
        parsedCondition = BaseballCard::Condition::MINT;
    }
    else if (upperCondition == "PRISTINE")
    {
        parsedCondition = BaseballCard::Condition::PRISTINE;
    }
    #ifdef DIAGNOSTIC_OUTPUT
        cout << "Current Parsed Condition: " << parsedCondition << endl;
    #endif
    return parsedCondition;
}


void FileReader::parseLine(string line)
{
    if (line == "")
    {
        return;
    }


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
    //int intCondition = parseCondition(cardVariables[3]);
    BaseballCard::Condition condition = parseCondition(cardVariables[3]);
    #ifdef DIAGNOSTIC_OUTPUT
        cout << "Condition Being Added To Card: " << condition << endl;
    #endif
    int value = UTILS_H::toInt(cardVariables[4], errorMessage);

    BaseballCard* cardToAdd = new BaseballCard(firstName, lastName, year, condition, value);
    this -> loadedCards.push_back(cardToAdd);
}

}
