#include "kicker.h"
#include <combo.h>
#include <map>
#include <card.h>

#include <iostream>

bool operator<(const std::vector<KickerRank>& lhs,
               const std::vector<KickerRank>& rhs) {
    for(size_t i = 0; i < lhs.size(); ++i) {
        std::cout << (int)lhs[i] << " " << (int)rhs[i] << std::endl;
        if(lhs[i] != rhs[i]) {
            return lhs[i] < rhs[i];
            break;
        }
    }
    return false;
}

bool operator>(const std::vector<KickerRank>& lhs,
               const std::vector<KickerRank>& rhs) {
    for(size_t i = 0; i < lhs.size(); ++i) {
        if(lhs[i] != rhs[i]) {
            return lhs[i] > rhs[i];
            break;
        }
    }
    return false;
}

std::vector<KickerRank> Kicker::kicker_Higher_Card(Combo const &combo) {
    auto const &ranks = combo.ranks();
    std::vector<KickerRank> res (ranks.crbegin(), ranks.crend());
    return res;
}

void Kicker::setPrior_FullHouse_KindOfFour(std::vector<KickerRank> &res, std::vector<uint8_t> const &ranks) {
    uint8_t qntLeftSide = std::count(ranks.begin(), ranks.end(), ranks[0]);
    if(qntLeftSide == 3 || qntLeftSide == 4)
        std::swap(res[0], res[1]);
}

std::vector<KickerRank> Kicker::calcRanksByPriority(Combo const &combo) {
    const ComboRank comboRank = combo.comboRank();
    std::vector<KickerRank> res;
    std::vector<uint8_t>    buf;

    buf.reserve(5);
    res.reserve(comboRank2Size[comboRank]);
    auto const &ranks = combo.ranks();

    for(auto it = ranks.crbegin(); it < ranks.crend(); ++it) {
        if(std::find(buf.begin(), buf.end(), *it) != buf.end()) {
            if(std::find(res.begin(), res.end(), *it) == buf.end())
                res.emplace_back(*it);
            continue;
        }
        buf.emplace_back(*it);
    }

    for(auto it: res) {
        auto rmIt = std::remove(buf.begin(), buf.end(), it);
        buf.erase(rmIt);
    }

    res.insert(res.end(), buf.begin(), buf.end());

    if(ComboRank::Full_House == comboRank || ComboRank::Four_of_a_Kind == comboRank)
        setPrior_FullHouse_KindOfFour(res, ranks);

    return res;
}

std::vector<KickerRank> Kicker::kicker_Straight(Combo const &combo) {
    std::vector<uint8_t> const& ranks = combo.ranks();
    bool hasAce = std::any_of(ranks.begin(), ranks.end(), [](uint8_t rank){
        return rank == static_cast<uint8_t>(CardRank::Ace);
    });

    KickerRank lowestCard = hasAce ? 1 : *ranks.cbegin();
    return {lowestCard};
}

std::vector<KickerRank> Kicker::kicker_Flush(const Combo &combo) {
    KickerRank highestCard = combo.ranks().back();
    return {highestCard};
}

std::map<ComboRank, uint8_t> Kicker::comboRank2Size = {
    {ComboRank::Higher_Card,     5 },
    {ComboRank::One_Pair,        4 },
    {ComboRank::Two_Pair,        3 },
    {ComboRank::Three_of_a_Kind, 3 },
    {ComboRank::Straight,        1 },
    {ComboRank::Flush,           1 },
    {ComboRank::Full_House,      2 },
    {ComboRank::Four_of_a_Kind,  2 },
    {ComboRank::Straight_Flush,  1 },
};

std::map<ComboRank, Kicker::pKickerFunc> Kicker::comboRank2Kicker = {
    {ComboRank::Higher_Card,     Kicker::kicker_Higher_Card  },
    {ComboRank::One_Pair,        Kicker::calcRanksByPriority },
    {ComboRank::Two_Pair,        Kicker::calcRanksByPriority },
    {ComboRank::Three_of_a_Kind, Kicker::calcRanksByPriority },
    {ComboRank::Straight,        Kicker::kicker_Straight     },
    {ComboRank::Flush,           Kicker::kicker_Flush        },
    {ComboRank::Full_House,      Kicker::calcRanksByPriority },
    {ComboRank::Four_of_a_Kind,  Kicker::calcRanksByPriority },
    {ComboRank::Straight_Flush,  Kicker::kicker_Straight     },
};


std::vector<KickerRank> Kicker::get(Combo const &combo) const {
    pKickerFunc comboKicker = comboRank2Kicker[combo.comboRank()];
    std::vector<KickerRank> const &res = comboKicker(combo);
    return res;
}
