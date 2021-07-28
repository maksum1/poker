#include <vector>
#include <round.h>
#include <parser.h>

int main() {
    Parser pars;
    const std::string path2Tests ("../poker/example.txt");
    std::vector<RoundCards> rounds = pars.readRoundsFromFile(path2Tests);

    Round round;
    for(auto &it : rounds) {
        round.getWinner(it);
    }
    return 0;
}
