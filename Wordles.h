#include <iostream>
#include <ostream>
#include <map>
#include "Wordbot.h"

enum class letter_state
{
    CORRECT,
    WRONG,
    CONTAINED // For misplaced letters
};

std::ostream &operator<<(std::ostream &, const letter_state &);
std::string make_str(char c, int pos);

class Wordle
{
private:
    std::string answer;
    std::map<char, bool> ans_set;
    Wordle(){};

public:
    int trials;
    Wordle(std::string ans, int tries);
    int word_len() { return answer.length(); }
    std::vector<letter_state> check_guess(std::string guess);
};

class Player
{
private:
    std::map<char, bool> bad_letters{};
    std::map<std::string, bool> bad_positions{};
    std::vector<letter_state> last_res{};
    int trials;
    Wordle wordle;
    int trys{0};

    bool check_invalids(std::string &s);
    Player() = delete; // No default constructor

public:
    std::string last_guess;
    Wordbot bot;
    Player(Wordbot &mybot, Wordle &wordler) : bot{mybot}, trials{wordler.trials}, wordle{wordler} {}
    void play();
    void update_bad_letters();
    std::string return_first_valid(std::vector<std::string> &word_guesses);
    std::string remake_guess();
    void print_out();
};
