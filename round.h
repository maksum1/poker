#ifndef ROUND_H
#define ROUND_H

#include <card.h>
#include <vector>
#include <combinator.h>

struct RoundCards {
    std::vector<Card> handA;
    std::vector<Card> handB;
    std::vector<Card> board;
};

class Round {
    Combinator _combinator;

    void printVectorCards(std::vector<Card> const &cards);
    void printPlayer(Player const &player);
public:
     Round() = default;
    ~Round() = default;

    void getWinner(RoundCards  const &roundCads,
                   std::string const &name1 = "Player1",
                   std::string const &name2 = "Player2");
};

#endif // ROUND_H
