#include "BraiderUtils.h"


static CardNode* getNextNode(CardNode* node, CardBraider::AddType type)
{
    CardNode* returnNode = nullptr;
    if (type == CardBraider::AddType::NAME)
    {
        returnNode = node -> getNextName();
    }
    else if (type == CardBraider::AddType::YEAR)
    {
        returnNode = node -> getNextYear();
    }
    else if (type == CardBraider::AddType::CONDITION)
    {
        returnNode = node -> getNextCondition();
    }
    return returnNode;
}

static void setNextNode(CardNode* node, CardNode* nodeToSet, CardBraider::AddType type)
{
    if (type == CardBraider::AddType::NAME)
    {
        node -> setNextName(nodeToSet);
    }
    else if (type == CardBraider::AddType::YEAR)
    {
        node -> setNextYear(nodeToSet);
    }
    else if (type == CardBraider::AddType::CONDITION)
    {
        node -> setNextCondition(nodeToSet);
    }
}

static CardNode* getBraidHead(CardBraider* braider, CardBraider::AddType type)
{
    CardNode* returnNode = nullptr;
    if (type == CardBraider::AddType::NAME)
    {
        returnNode = braider -> getNameHead();
    }
    else if (type == CardBraider::AddType::YEAR)
    {
        returnNode = braider -> getYearHead();
    }
    else if (type == CardBraider::AddType::CONDITION)
    {
        returnNode = braider -> getConditionHead();
    }
    return returnNode;
}

static void setBraidHead(CardBraider* braider, CardNode* nodeToSet, CardBraider::AddType type)
{
    if (type == CardBraider::AddType::NAME)
    {
        braider -> setNameHead(nodeToSet);
    }
    else if (type == CardBraider::AddType::YEAR)
    {
        braider -> setYearHead(nodeToSet);
    }
    else if (type == CardBraider::AddType::CONDITION)
    {
        braider -> setConditionHead(nodeToSet);
    }
}
