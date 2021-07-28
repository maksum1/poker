#include "combo.h"
#include <algorithm>
#include <iostream>
#include <functional>
#include <kicker.h>
#include <map>
#include <card.h>

const size_t Combo::comboSize = 5;

std::map<ComboRank, std::string> comboRank2Name = {
    {ComboRank::Higher_Card, "Higher_Card"},
    {ComboRank::One_Pair, "One_Pair"},
    {ComboRank::Two_Pair, "Two_Pair"},
    {ComboRank::Three_of_a_Kind, "Three_of_a_Kind"},
    {ComboRank::Straight, "Straight"},
    {ComboRank::Flush, "Flush"},
    {ComboRank::Full_House, "Full_House"},
    {ComboRank::Four_of_a_Kind, "Four_of_a_Kind"},
    {ComboRank::Straight_Flush, "Straight_Flush"},
};

Combo::Combo(): _comboRank(ComboRank::None) {}

std::vector<Card> Combo::cards() const {
    return _cards;
}

ComboRank Combo::comboRank() const {
    return _comboRank;
}

void Combo::updateRank(ComboRank newRank,
                       const std::vector<Card> &newCards,
                       const std::vector<uint8_t> &newRanks) {
    if(_comboRank >= newRank)
        return;

    _comboRank = newRank;
    _cards = newCards;
    _ranks = newRanks;
//    std::cout << toStr() << std::endl;
}

void Combo::getRanksOfCards(std::vector<Card> const &combo,
                            std::vector<uint8_t> &ranks) {
    ranks.reserve(comboSize);
    std::transform(combo.begin(), combo.end(), std::back_inserter(ranks), [](Card const &card){
        return static_cast<uint8_t>(card.rank());
    });

    std::sort(ranks.begin(), ranks.end(), [](uint8_t lhs, uint8_t rhs){
                  return lhs < rhs; /** 2 -> Ace **/
              });
}

bool Combo::hasStraight(std::vector<uint8_t> const &ranks) {
    auto last = std::adjacent_find(ranks.cbegin(), ranks.cend());
    if(last != ranks.end())
        return false;

    bool hasAce = std::any_of(ranks.begin(), ranks.end(), [](uint8_t rank){
            return rank == static_cast<uint8_t>(CardRank::Ace);
        });

    size_t offset = hasAce? 2 : 1;
    for (size_t i = 0; i < ranks.size() - offset; ++i) {
        if(ranks[i]+1 != ranks[i+1])
            return false;
    }
    return true;
}

bool Combo::hasFlush(std::vector<Card> const &combo) {
    Suite primeSuite = combo.begin()->suite();
    for(Card const &card : combo) {
        if(primeSuite != card.suite())
            return false;
    }
    return true;
}

ComboRank Combo::checkStraightAndFlush(std::vector<Card> const &combo,
                                       std::vector<uint8_t> const &ranks) {

    bool containStraight = hasStraight(ranks);
    bool containFlush = hasFlush(combo);

    if(containStraight && containFlush)
        return ComboRank::Straight_Flush;
    else if(containFlush)
        return ComboRank::Flush;
    else if(containStraight)
        return ComboRank::Straight;

    return ComboRank::Higher_Card;
}


ComboRank Combo::checkRanksCombos(std::vector<uint8_t> const &ranks) {
    uint8_t indexOfFirstCard = 0;
    uint8_t indexOfMidCard   = 2;
    uint8_t indexOfLastCard  = 4;
    uint8_t firstCard = ranks[indexOfFirstCard];
    uint8_t midCard   = ranks[indexOfMidCard];
    uint8_t lastCard  = ranks[indexOfLastCard];
    uint8_t qntFirstCard = 0, qntMidCard = 0, qntLastCard = 0;

    for (size_t i = 0; i < comboSize; ++i) {
        if (ranks[i] == firstCard)  ++qntFirstCard;
        if (ranks[i] == midCard)    ++qntMidCard;
        if (ranks[i] == lastCard)   ++qntLastCard;
    }

    /** @note Four_of_a_Kind [Four cards same rank 4:1]**/
    bool containFour_of_a_Kind = qntFirstCard == 4 || qntLastCard == 4;

    /** @note Full_House [Three and two cards same rank 3:2]**/
    bool containFull_House = (qntFirstCard == 3 && qntLastCard == 2) || (qntFirstCard == 2 && qntLastCard == 3);

    /** @note Three_of_a_Kind [Three cards same rank 3]**/
    bool containThree_of_a_Kind = qntFirstCard == 3 || qntLastCard == 3;

    /** @note TwoPair [Two and two cards same rank 2:2]**/
    bool containTwoPair = (qntFirstCard == 2 && qntMidCard  == 2)  ||
                          (qntFirstCard == 2 && qntLastCard == 2)  ||
                          (qntMidCard   == 2 && qntLastCard == 2);

    /** @note OnePair [Two cards same rank 2]**/
    bool containOnePair = qntFirstCard == 2 || qntMidCard == 2 || qntLastCard == 2;

    if(containFour_of_a_Kind)
        return ComboRank::Four_of_a_Kind;
    else if(containFull_House)
        return ComboRank::Full_House;
    else if(containThree_of_a_Kind)
        return ComboRank::Three_of_a_Kind;
    else if(containTwoPair)
        return ComboRank::Two_Pair;
    else if(containOnePair)
        return ComboRank::One_Pair;

    return  ComboRank::Higher_Card;
}


void Combo::update(std::vector<Card> const &combo) {
//    for(auto it: combo)
//        std::cout << it.toStr() << " ";
//    std::cout << std::endl;

    std::vector<uint8_t> ranks;
    getRanksOfCards(combo, ranks);

    updateRank(checkStraightAndFlush(combo, ranks), combo, ranks);
    if(_comboRank == ComboRank::Straight_Flush) return;

    updateRank(checkRanksCombos(ranks), combo, ranks);
}

std::string Combo::toStr() const {
    return comboRank2Name[_comboRank];
}

std::vector<uint8_t> Combo::ranks() const {
    return _ranks;
}

std::vector<KickerRank> Combo::kickerRules() const{
    return _kicker.get(*this);
}


bool operator<(const Combo& lhs, const Combo& rhs) {
    ComboRank lhsComboRank = lhs.comboRank();
    ComboRank rhsComboRank = rhs.comboRank();

    if(lhsComboRank != rhsComboRank)
        return lhsComboRank < rhsComboRank;

    std::vector<KickerRank> lhsKickerRules = lhs.kickerRules();
    std::vector<KickerRank> rhsKickerRules = rhs.kickerRules();

    return lhsKickerRules < rhsKickerRules;
}


bool operator>(const Combo& lhs, const Combo& rhs) {
    ComboRank lhsComboRank = lhs.comboRank();
    ComboRank rhsComboRank = rhs.comboRank();

    if(lhsComboRank != rhsComboRank)
        return lhsComboRank > rhsComboRank;

    std::vector<KickerRank> lhsKickerRules = lhs.kickerRules();
    std::vector<KickerRank> rhsKickerRules = rhs.kickerRules();

    return lhsKickerRules > rhsKickerRules;
}


