#ifndef KICKER_H
#define KICKER_H

#include <stdint.h>
#include <vector>
#include <functional>
#include <map>

typedef uint8_t KickerRank;

enum class ComboRank : uint8_t;
class Combo;

bool operator>(const std::vector<KickerRank>& lhs, const std::vector<KickerRank>& rhs);
bool operator<(const std::vector<KickerRank>& lhs, const std::vector<KickerRank>& rhs);

class Kicker {
    typedef std::function<std::vector<KickerRank>(Combo)> pKickerFunc;

    static std::map<ComboRank, pKickerFunc> comboRank2Kicker;
    static std::map<ComboRank, uint8_t> comboRank2Size;

    static std::vector<KickerRank> calcRanksByPriority(Combo const &combo);
    static void setPrior_FullHouse_KindOfFour(std::vector<KickerRank> &res,
                                              std::vector<uint8_t> const &ranks);

    static std::vector<KickerRank> kicker_Higher_Card(Combo const &combo);
    static std::vector<KickerRank> kicker_Straight(Combo const &combo);
    static std::vector<KickerRank> kicker_Flush(Combo const &combo);

public:
    std::vector<KickerRank> get(Combo const &combo) const;
     Kicker() = default;
    ~Kicker() = default;
};

#endif // KICKER_H
