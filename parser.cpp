#include "parser.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <card.h>
#include <round.h>
#include <combo.h>

std::map<char, Suite> Parser::name2Suite = {
    {'h', Suite::Hearts   },
    {'d', Suite::Diamonds },
    {'c', Suite::Clubs    },
    {'s', Suite::Spades   }
};

std::map<char, CardRank> Parser::name2Rank = {
    {'2',  CardRank::Two   },
    {'3',  CardRank::Three },
    {'4',  CardRank::Four  },
    {'5',  CardRank::Five  },
    {'6',  CardRank::Six   },
    {'7',  CardRank::Seven },
    {'8',  CardRank::Eight },
    {'9',  CardRank::Nine  },
    {'T',  CardRank::Ten   },
    {'J',  CardRank::Jack  },
    {'Q',  CardRank::Queen },
    {'K',  CardRank::King  },
    {'A',  CardRank::Ace   }
};

Card Parser::parseCard(std::string const &strCard) {
    Card card(name2Suite[strCard[1]], name2Rank[strCard[0]]);
    return card;
}

std::vector<Card> Parser::parseCombination(std::string const &lineWithCombo) {
    std::vector<Card> combo;
    std::size_t offset = lineWithCombo.find(":");
    std::string lineWithCards = lineWithCombo.substr (offset+1, lineWithCombo.size());

    std::stringstream ss(lineWithCards);
    while( ss.good() ) {
        std::string cardStr;
        getline( ss, cardStr, '-' );
        combo.emplace_back(parseCard(cardStr));
    }
    return combo;
}

RoundCards Parser::parseRound(std::string const &strWithRound) {
    RoundCards resRound;
    std::stringstream ss(strWithRound);

    for (std::string lineWithCards; ss>>lineWithCards; ) {
        std::vector<Card> cards = parseCombination(lineWithCards);

        if (lineWithCards.find("HandA") != std::string::npos)
            resRound.handA = cards;
        else if(lineWithCards.find("HandB") != std::string::npos)
            resRound.handB = cards;
        else if (lineWithCards.find("Board") != std::string::npos)
            resRound.board = cards;
    }
    return resRound;
}

std::vector<RoundCards> Parser::readRoundsFromFile(std::string const &fileName) {
    std::vector<RoundCards> resRounds;
    std::string lineWithRound;

    std::ifstream inFile(fileName, std::ios::in);
    if (!inFile.is_open()) {
        std::cout << "Unable to open file";
        return resRounds;
    }

    while ( getline (inFile,lineWithRound) ) {
        resRounds.emplace_back(parseRound(lineWithRound));
    }
    inFile.close();
    return resRounds;
}


