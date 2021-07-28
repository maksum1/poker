#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <vector>
#include <map>

enum class Suite : uint8_t;
enum class CardRank : uint8_t;
class Card;
struct RoundCards;


class Parser {
    static std::map<char, Suite> name2Suite;
    static std::map<char, CardRank> name2Rank;

    std::vector<Card> parseCombination(std::string const &lineWithCombo);
    RoundCards parseRound(std::string const &lineWithRound);
    Card parseCard(std::string const &card);

public:
     Parser() = default;
    ~Parser() = default;
    std::vector<RoundCards> readRoundsFromFile(std::string const & fileName);
};

#endif // PARSER_H
