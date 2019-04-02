#ifndef FILEREADER_H
#define FILEREADER_H

#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <vector>
#include <stdexcept>
using namespace std;

#include "BaseballCard.h"
#include "Utils.h"
using namespace model;


namespace io
{

class FileReader
{
    private:
        BaseballCard::Condition parseCondition(string condition);
        void parseLine(string line);
        vector<BaseballCard*> loadedCards;

    public:
        //Creates a new instance of a FileReader.
        //@precondition
        //      none
        //@postcondition
        //      a new file reader is created
        FileReader();

        //Destroys a FileReader to free memory.
        virtual ~FileReader();

        //Loads a file of baseball cards into a collection of baseball objects.
        //@precondition
        //      file name cannot be empty
        //@return
        //      a list of baseball cards
        //@para fileName
        //      the file name
        vector<BaseballCard*> loadFile(string fileName);
};

}

#endif // FILEREADER_H
