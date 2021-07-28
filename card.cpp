#include "card.h"

std::map<Suite, std::string> Card::suite2Name = {
    {Suite::Hearts,     "h"},
    {Suite::Diamonds,   "d"},
    {Suite::Clubs,      "c"},
    {Suite::Spades,     "s"}
};


std::map<CardRank, std::string> Card::rank2Name = {
    {CardRank::Two,     "2"},
    {CardRank::Three,   "3"},
    {CardRank::Four,    "4"},
    {CardRank::Five,    "5"},
    {CardRank::Six,     "6"},
    {CardRank::Seven,   "7"},
    {CardRank::Eight,   "8"},
    {CardRank::Nine,    "9"},
    {CardRank::Ten,     "10"},
    {CardRank::Jack,    "J"},
    {CardRank::Queen,   "Q"},
    {CardRank::King,    "K"},
    {CardRank::Ace,     "A"}
};


Card::Card(Suite newSuite, CardRank newRank):
    _suite(newSuite), _rank(newRank) {}

Suite Card::suite() const {
    return _suite;
}

CardRank Card::rank() const {
    return _rank;
}

std::string Card::toStr() const {
    return rank2Name[_rank] + suite2Name[_suite];
}
