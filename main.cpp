#include <iostream>
#include <map>
#include "Wordbot.h"
#include "Wordles.h"


int main()
{
    std::cout << " ------------- STARTING DEBUG -------------" << std::endl;
    Wordbot bot{};
    // switch (bot.check("churlish"))
    // {
    // case Wordbot::search_result::VALID:
    //     std::cout << "VALID" << std::endl;
    //     break;
    // case Wordbot::search_result::NOT_FOUND:
    //     std::cout << "INVALID WORD- NOT FOUND" << std::endl;
    //     break;
    // default:
    //     break;
    // }

    // std::vector<std::string> test_rand = bot.get_ran_word("rue", "r____");
    // if (!test_rand.empty())
    //     std::for_each(test_rand.begin(), test_rand.end(), [](std::string &s)
    //                   { std::cout << s << std::endl; });

    Wordle w{Wordle("aloft", 5)};
    // auto s = std::string{"rains"};
    // auto ans = w.check_guess(s);
    // int i = 0;
    // std::for_each(ans.begin(), ans.end(), [&](letter_state &l)
    //               {
    //     std::cout << s[i] << " -> " << ((l == letter_state::CORRECT)? "correct" : ( l == letter_state::WRONG ? "wrong" : "contained")) << std::endl;
    //     i++; });

    // std::map<char, bool> bad_letters{};
    // bad_letters['n'] = true;
    // bad_letters['m'] = true;
    // bad_letters['p'] = true;
    // bad_letters['t'] = true;

    // std::cout << retry(bad_letters, ans, s, bot) << std::endl;

    Player daniel = Player(bot,w);
    daniel.play();
    daniel.play();
    daniel.play();
    daniel.play();
    daniel.play();

}