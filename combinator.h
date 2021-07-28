#ifndef COMBINATOR_H
#define COMBINATOR_H

#include <vector>
#include <stdint.h>

class Card;
class Player;
class Combo;

struct Combinator {
private:
    uint32_t factorial(uint32_t n);
    std::vector<std::vector<Card>> getCombosBySize(std::vector<Card> const &vec, size_t comboSize);
    void calcCombo(std::vector<std::vector<Card>> &res,
                   std::vector<Card> const &vec,
                   int comboSize,int index,
                   std::vector<Card> &tmp, size_t i);

    std::vector<std::vector<Card>> getPlayerCombos(std::vector<Card> const &hand,
                                                   std::vector<Card> const &board);

public:
     Combinator() = default;
    ~Combinator() = default;

    Combo calcComboRank(std::vector<Card> const &combo);
    void calcPlayerMaxCombo(Player &player, std::vector<Card> const &board);
};


#endif // COMBINATOR_H
