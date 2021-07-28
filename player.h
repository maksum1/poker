#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <combo.h>
#include <card.h>

class Player {
private:
    std::string _name;
    std::vector<Card> _handCards;
    Combo _maxCombo;


public:
     Player(const std::string &name);
     Player(const std::string &name, std::vector<Card> const &cards);
     ~Player() = default;

     void updateMaxCombo(std::vector<Card> const &combo);

     void setHandCards(std::vector<Card> &cards);
     const std::vector<Card> &handCards()const;
     const std::string &name() const;
     const Combo &maxCombo() const;
};

#endif // PLAYER_H
