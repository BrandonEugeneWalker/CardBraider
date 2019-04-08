#include "FileWriter.h"

#define DIAGNOSTIC_OUTPUT

namespace io
{

FileWriter::FileWriter()
{
#ifdef DIAGNOSTIC_OUTPUT
    cout << "FileWriter Constructor:" << endl;
#endif
}

FileWriter::~FileWriter()
{
#ifdef DIAGNOSTIC_OUTPUT
    cout << "FileWriter Destructor:" << endl;
#endif
}

string FileWriter::createLineFromNode(CardNode* node)
{
    if(node == nullptr)
    {
        throw invalid_argument("Cannot create a line from a nullptr!");
    }

    stringstream lineStream;
    string lastName = node -> getLastName();
    string firstName = node -> getFirstName();
    int year = node -> getYear();
    string condition = UTILS_H::enumToString(node -> getCondition());
    int value = node -> getValue();
    string comma = ",";

    lineStream << lastName;
    lineStream << comma;
    lineStream << firstName;
    lineStream << comma;
    lineStream << year;
    lineStream << comma;
    lineStream << condition;
    lineStream << comma;
    lineStream << value;

    return lineStream.str();
}

void FileWriter::writeNodesToFile(CardNode* head, string fileName)
{
    ofstream fileOutput;
    fileOutput.open(fileName);

    CardNode* currentNode = head;

    while (currentNode != nullptr)
    {
        fileOutput << this -> createLineFromNode(currentNode) << endl;
        currentNode = currentNode -> getNextName();
    }

    fileOutput.close();
}

}
