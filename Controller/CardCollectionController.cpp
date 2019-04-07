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

string CardCollectionController::buildOutput(int order)
{
    OutputBuilder newBuilder;
    CardNode* headNode;
    string results;
    if (order == 0)
    {
        headNode = this -> braidedCardList -> getNameHead();
        results = newBuilder.buildOutput(true, OutputBuilder::SortType::NAME, headNode);
    }
    else if(order == 1)
    {
        headNode = this -> braidedCardList -> getNameHead();
        results = newBuilder.buildOutput(false, OutputBuilder::SortType::NAME, headNode);
    }
    else if(order == 2)
    {
        headNode = this -> braidedCardList -> getYearHead();
        results = newBuilder.buildOutput(true, OutputBuilder::SortType::YEAR, headNode);
    }
    else if(order == 3)
    {
        headNode = this -> braidedCardList -> getYearHead();
        results = newBuilder.buildOutput(false, OutputBuilder::SortType::YEAR, headNode);
    }
    else if(order == 4)
    {
        headNode = this -> braidedCardList -> getConditionHead();
        results = newBuilder.buildOutput(true, OutputBuilder::SortType::CONDITION, headNode);
    }
    else if(order == 5)
    {
        headNode = this -> braidedCardList -> getConditionHead();
        results = newBuilder.buildOutput(false, OutputBuilder::SortType::CONDITION, headNode);
    }
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
