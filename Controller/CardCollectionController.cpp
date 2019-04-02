#include "CardCollectionController.h"

#define DIAGNOSTIC_OUTPUT

#ifdef DIAGNOSTIC_OUTPUT
#include <iostream>
#endif

namespace controller
{

CardCollectionController::CardCollectionController()
{
    this -> braidedCardList = new CardBraider();
}

CardCollectionController::~CardCollectionController()
{
    delete this -> braidedCardList;
}

CardBraider* CardCollectionController::getCardBraider()
{
    return this -> braidedCardList;
}

void CardCollectionController::addCard(BaseballCard* card)
{
    if (card == nullptr)
    {
        throw invalid_argument("the card cannot be nullptr");
    }
    CardNode* newNode = new CardNode(card);
    this -> braidedCardList -> addNode(newNode);
}

void CardCollectionController::deleteCard(string name)
{

    this -> braidedCardList -> deleteNode(name, nullptr, nullptr);
}

string CardCollectionController::buildOutput(bool isAscending)
{
    OutputBuilder newBuilder;
    CardNode* headNode = this -> braidedCardList -> getHead();
    string results = newBuilder.buildOutput(isAscending, headNode);
    return results;
}

void CardCollectionController::addCardsFromCollection(vector<BaseballCard*> cards)
{

    #ifdef DIAGNOSTIC_OUTPUT
        cout << "Inside Controller Add All:" << endl;
    #endif

    for (BaseballCard* currentCard : cards)
    {
        if (currentCard != nullptr)
        {
            this -> addCard(currentCard);
        }
    }
}

void CardCollectionController::resetBraidedList()
{
    delete this -> braidedCardList;
    this -> braidedCardList = new CardBraider();
}


}
