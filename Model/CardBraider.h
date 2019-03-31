#ifndef CARDBRAIDER_H
#define CARDBRAIDER_H

#include <string>
using namespace std;

#include "CardNode.h"
#include "Utils.h"

namespace model
{

class CardBraider
{
    private:
        CardNode* head;

        void deconstructNode(CardNode* currentNode);

        void addByNameBraid(CardNode* currentNode, CardNode* nodeToAdd);

    public:
        // Creates a new instance of a CardBraider.
        // @precondition
        //      none
        // @postcondition
        //      the CardBraider is created.
        CardBraider();

        //Destroys a CardBraider to free up memory.
        virtual ~CardBraider();

        //Adds a node to each of the braids.
        //@precondition
        //      node cannot be nullptr
        //@postcondition
        //      the node is added
        //@para node
        //      the node to add
        void addNode(CardNode* node);

        //Removes all nodes matching the given last name.
        //@precondition
        //      name cannot be empty
        //@postcondition
        //      the node(s) are deleted
        //@para name
        //      the name to delete by
        void deleteNode(string name, CardNode* currentNode, CardNode* previousNode);

        //Gets and returns the pointer to the head.
        //@precondition
        //      none
        //@return
        //      the pointer if it exists, nullptr otherwise
        CardNode* getHead();

};

}

#endif // CARDBRAIDER_H
