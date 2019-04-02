#ifndef CARDCOLLECTIONCONTROLLER_H
#define CARDCOLLECTIONCONTROLLER_H

#include <string>
#include <vector>
using namespace std;

#include "BaseballCard.h"
#include "CardNode.h"
#include "CardBraider.h"
#include "FileReader.h"
using namespace model;

#include "OutputBuilder.h"
using namespace view;

namespace controller
{

class CardCollectionController
{
    private:
        CardBraider* braidedCardList;



    public:
        //Constructs a new CardCollectionController
        //@precondition
        //      none
        //@postcondition
        //      a new controller is made
        CardCollectionController();

        //Destroys a CardCollectionController to free up memory.
        virtual ~CardCollectionController();

        //Gets the braided card list.
        //@precondition
        //      none
        //@return
        //      the braided card list.
        CardBraider* getCardBraider();

        //Adds a card to the braided list.
        //@precondition
        //      card cannot be nullptr
        //@para card
        //      the card to add
        void addCard(BaseballCard* card);

        //Deletes a card in the braided list.
        //@precondition
        //      name cannot be empty
        //@postcondition
        //      tall cards matching the name are deleted
        //@para name
        //      the name to delete by
        void deleteCard(string name);

        //Builds and returns the output for the collection window.
        //@precondition
        //      none
        //@return
        //      a string formatted properly for output.
        //@para isAscending
        //      true if ascending, false is descending
        string buildOutput(bool isAscending);

        //Adds all cards in the list to the braid.
        //@precondition
        //      none
        //@postcondition
        //      the cards are added
        //@para cards
        //      the collection of cards to add
        void addCardsFromCollection(vector<BaseballCard*> cards);

        //Deletes the current braided list and replaces it with a new one.
        //@precondition
        //      none
        //@postcondition
        //      the old list is deleted and a new one is created
        void resetBraidedList();
};

}

#endif // CARDCOLLECTIONCONTROLLER_H
