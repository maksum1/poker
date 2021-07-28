#include "combinator.h"
#include <iostream>
#include <player.h>

uint32_t Combinator::factorial(uint32_t n) {
    if (!n)
        return 1;
    return n * factorial(n - 1);
}

std::vector<std::vector<Card>> Combinator::getCombosBySize(std::vector<Card> const &vec, size_t comboSize) {
    size_t vecSize = vec.size();
    size_t qntCombos = factorial(vecSize)/
                      (factorial(comboSize) * factorial(vecSize - comboSize));
    std::vector<Card> tmp (comboSize);

    std::vector<std::vector<Card>> res;
    res.reserve(qntCombos);

    calcCombo(res, vec, comboSize, 0, tmp, 0);
    return res;
}

/**
*  @example
*  index set in tmp, i get from vec
*  1 2 3 4 index = 0, i = 0
*  1       index = 1, i = 1
*  1 2     index = 2, i = 2
*  1 3     index = 1, i + 1
*  1 4     index = 1, i + 1
**/
void Combinator::calcCombo(std::vector<std::vector<Card>> &res,
                           std::vector<Card> const &vec,
                           int comboSize,int index,
                           std::vector<Card> &tmp, size_t i) {

    if (index == comboSize) {
        res.push_back(tmp);
        return;
    }

    if (i >= vec.size())
        return;

    // current is included put next
    tmp[index] = vec[i];
    calcCombo(res, vec, comboSize, index + 1, tmp, i + 1);

    // current is excluded replace with next
    calcCombo(res, vec, comboSize, index, tmp, i+1);
}

std::vector<std::vector<Card>> Combinator::getPlayerCombos(const std::vector<Card> &hand,
                                                           const std::vector<Card> &board) {
    std::vector<std::vector<Card>> handCombos  = getCombosBySize(hand,  2);
    std::vector<std::vector<Card>> boardCombos = getCombosBySize(board, 3);
    std::vector<std::vector<Card>> allCombos;
    allCombos.reserve(handCombos.size() * boardCombos.size() );

    for(size_t i = 0; i < handCombos.size(); ++i) {
        for(size_t j = 0; j < boardCombos.size(); ++j) {
            std::vector<Card> buf (handCombos[i]);
            buf.insert(buf.end(), boardCombos[j].begin(), boardCombos[j].end());
            allCombos.emplace_back(buf);
        }
    }
    return allCombos;
}



void Combinator::calcPlayerMaxCombo(Player &player, std::vector<Card> const &board) {
    std::vector<std::vector<Card>> playerCombos = getPlayerCombos(player.handCards(), board);

    for(auto comboIt = playerCombos.crbegin(); comboIt != playerCombos.crend();  ++comboIt) {
        player.updateMaxCombo(*comboIt);
    }
}


