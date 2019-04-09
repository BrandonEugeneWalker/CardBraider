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

    //Writes the braided list to a file starting at the head node.
    //@precondition
    //      the filename cannot be empty
    //@postcondition
    //      the list is written to the file in a format that can be loaded back in
    //@para head
    //      the starting node
    //@para fileName
    //      the fileName/path to save to.
    void writeNodesToFile(CardNode* head, string fileName);

};

}

#endif // FILEWRITER_H
