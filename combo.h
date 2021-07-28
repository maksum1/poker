#ifndef COMBO_H
#define COMBO_H

#include <stdint.h>
#include <string>
#include <vector>
#include <kicker.h>

class Kicker;
class Card;
class Combo;

enum class ComboRank : uint8_t{
    None                = 0,
    Higher_Card         = 1,
    One_Pair            = 2,
    Two_Pair            = 3,
    Three_of_a_Kind     = 4,
    Straight            = 5,
    Flush               = 6,
    Full_House          = 7,
    Four_of_a_Kind      = 8,
    Straight_Flush      = 9
};

bool operator<(const Combo& lhs, const Combo& rhs);
bool operator>(const Combo& lhs, const Combo& rhs);


class Combo {
    static const size_t comboSize;

    Kicker _kicker;
    ComboRank _comboRank;
    std::vector<Card> _cards;
    std::vector<uint8_t> _ranks;

    bool hasStraight(std::vector<uint8_t> const &ranks);
    bool hasFlush(std::vector<Card> const &combo);
    void getRanksOfCards(std::vector<Card> const &combo, std::vector<uint8_t> &ranks);

    ComboRank checkStraightAndFlush(std::vector<Card> const &combo, std::vector<uint8_t> const &ranks);
    ComboRank checkRanksCombos(std::vector<uint8_t> const &ranks);

    void updateRank(ComboRank newRank, const std::vector<Card> &newCards, const std::vector<uint8_t> &newRanks);

public:
     Combo();
    ~Combo() = default;

    std::vector<Card> cards() const;
    std::vector<uint8_t> ranks() const;
    ComboRank comboRank() const;

    std::vector<KickerRank> kickerRules() const;

    void update(std::vector<Card> const &combo);

    std::string toStr() const;
};

#endif // COMBO_H
