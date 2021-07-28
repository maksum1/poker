#ifndef CARD_H
#define CARD_H

#include <stdint.h>
#include <string>
#include <map>

enum class Suite : uint8_t{
    Hearts      = 20,
    Diamonds    = 40,
    Clubs       = 60,
    Spades      = 80
};

enum class CardRank : uint8_t{
    Two     = 2,
    Three   = 3,
    Four    = 4,
    Five    = 5,
    Six     = 6,
    Seven   = 7,
    Eight   = 8,
    Nine    = 9,
    Ten     = 10,
    Jack    = 11,
    Queen   = 12,
    King    = 13,
    Ace     = 14
};


class Card {
    static std::map<Suite, std::string> suite2Name;
    static std::map<CardRank, std::string> rank2Name;

    Suite _suite;
    CardRank _rank;
public:
    ~Card() = default;
     Card() = default;
    Card(Suite suite, CardRank rank);

    Suite suite() const;
    CardRank rank() const;
    std::string toStr()const;
};

#endif // CARD_H
