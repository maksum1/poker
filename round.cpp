#include "round.h"
#include <player.h>
#include <iostream>

void Round::printVectorCards(std::vector<Card> const &cards) {
    for(auto it : cards)
        std::cout << it.toStr() << " ";
    std::cout << std::endl;
}

void Round::printPlayer(Player const &player) {

    std::cout << "[Name]: " <<player.name() << " "
              << "[Max combo]: " << player.maxCombo().toStr() << " ";

    std::cout << "[MC  Cards]: ";
    for(auto it : player.maxCombo().cards())
        std::cout << it.toStr() << " ";
    std::cout << std::endl;

    std::cout << "[Hand]: ";
    for(auto it : player.handCards())
        std::cout << it.toStr() << " ";
    std::cout << std::endl;
}


void Round::getWinner(RoundCards  const &roundCads,
                      std::string const &name1,
                      std::string const &name2) {
    Player pl1(name1, roundCads.handA);
    Player pl2(name2, roundCads.handB);
    _combinator.calcPlayerMaxCombo(pl1, roundCads.board);
    _combinator.calcPlayerMaxCombo(pl2, roundCads.board);

    std::cout << "[Board]: ";
    printVectorCards(roundCads.board);
    printPlayer(pl1);
    printPlayer(pl2);

    std::string winMsg = "[Winner]: ";
    Combo pl1Combo = pl1.maxCombo();
    Combo pl2Combo = pl2.maxCombo();

    if(pl1.maxCombo() > pl2.maxCombo())
        winMsg = pl1.name();
    else if(pl1.maxCombo() < pl2.maxCombo())
        winMsg = pl2.name();
    else
        winMsg = "TIE";

    std::cout << winMsg << std::endl;
    std::cout << "-------------------" << std::endl;
}
