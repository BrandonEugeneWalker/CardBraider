#ifndef FILEWRITER_H
#define FILEWRITER_H

#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <stdexcept>
using namespace std;

#include "CardNode.h"
using namespace model;

#include "Utils.h"

namespace io
{

class FileWriter
{
private:
    string createLineFromNode(CardNode* node);

public:
    //Creates a new instance of a FileWriter.
    //@precondition
    //      none
    //@postcondition
    //      a new FileWriter is created.
    FileWriter();

    //Destroys a FileWriter.
    virtual ~FileWriter();

    void writeNodesToFile(CardNode* head, string fileName);

};

}

#endif // FILEWRITER_H
