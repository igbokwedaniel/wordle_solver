
#include"Wordles.h"

std::ostream &operator<<(std::ostream &os, const letter_state &dt)
{
    switch (dt)
    {
    case letter_state::CONTAINED:
        os << "Contained";
        break;
    case letter_state::WRONG:
        os << "wrong";
        break;
    case letter_state::CORRECT:
        os << "correct";
        break;
    }
    return os;
}

Wordle::Wordle(std::string ans, int tries)
{
    answer = ans;
    trials = tries;
    std::for_each(answer.begin(), answer.end(), [&](char &s)
                  { ans_set[s] = true; });
}

std::vector<letter_state> Wordle::check_guess(std::string guess)
{
    if (guess.length() != answer.length())
    {
        std::cout << "Length Mismatch";
        return std::vector<letter_state>{};
    }

    std::vector<letter_state> res{};
    int i = 0;
    std::for_each(guess.begin(), guess.end(), [&](char &s)
                  {
            if(guess[i] == answer[i])
                res.push_back(letter_state::CORRECT);
            else if (ans_set[s])
                res.push_back(letter_state::CONTAINED);
            else
                res.push_back(letter_state::WRONG);
            i++; });
    return res;
}


bool Player::check_invalids(std::string &s)
{

    for (int i = 0; i < s.length(); i++)
    {
        if (bad_letters[s[i]] || bad_positions[make_str(s[i], i)])
            return false;
    }
    std::cout << s << std::endl;
    return true;
}

void Player::update_bad_letters()
{
    for (int i = 0; i < last_guess.size(); i++)
    {
        if (last_res[i] == letter_state::WRONG)
            bad_letters[last_guess[i]] = true;
        if (last_res[i] == letter_state::CONTAINED)
            bad_positions[make_str(last_guess[i], i)] = true;
    }
}

std::string Player::return_first_valid(std::vector<std::string> &word_guesses)
{
    for (int j = 0; j < word_guesses.size(); j++)
    {
        if (check_invalids(word_guesses[j]))
            return word_guesses[j];
    }
    return last_guess; // Loop for no solutions
}

void Player::print_out()
{
    int i{0};
    std::cout << " <========== Trial " << trys << std::endl;
    std::for_each(last_res.begin(), last_res.end(), [&](letter_state &l)
                  {std::cout <<last_guess[i] << " -> " << l << std::endl;
        i++; });
}

std::string Player::remake_guess()
{
    std::map<char, bool> used{}; // words used
    std::string corrigeux{"_____"};
    std::string contained = last_res.size() == 0 ? std::string{"aie"} : ""; // use aie at the start of play
    for (int i = 0; i < last_res.size(); i++)
    {
        switch (last_res[i])
        {
        case letter_state::CORRECT:
            corrigeux[i] = last_guess[i];
            if (!used[last_guess[i]])
                contained += last_guess[i];
            break;
        case letter_state::CONTAINED:
            if (!used[last_guess[i]])
                contained += last_guess[i];
            break;
        default:
            break;
        }
        used[last_guess[i]] = true;
    }

    std::cout << contained << " | " << corrigeux << std::endl;
    std::vector<std::string> word_guesses = bot.get_ran_word(contained, corrigeux);
    return return_first_valid(word_guesses);
}

void Player::play()
{
    if (trys >= trials)
        return;
    if (trys <= trials)
    {
        ++trys;
        last_guess = remake_guess();
        last_res = wordle.check_guess(last_guess);
        update_bad_letters();
        print_out();
    }
}

std::string make_str(char c, int pos){
    return std::string{c} +  std::to_string(pos);
}