#include "player.h"


Player::Player(const std::string &newName)
    : _name(newName){}

Player::Player(const std::string &newName, std::vector<Card> const &cards)
    : _name(newName), _handCards(cards){}

const std::string &Player::name() const {
    return _name;
}

const Combo &Player::maxCombo() const {
    return _maxCombo;
}

const std::vector<Card> &Player::handCards() const {
    return _handCards;
}

void Player::setHandCards(std::vector<Card> &cards) {
    _handCards = cards;
}

void Player::updateMaxCombo(std::vector<Card> const &combo) {
    _maxCombo.update(combo);
}
