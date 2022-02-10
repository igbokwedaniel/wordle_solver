#include "Wordbot.h"
#include<iostream>
int Wordbot::search_callback(void *search_state, int argc, char **argv, char **az_col_name)
{
    search_result *res = static_cast<search_result *>(search_state);
    if (argc >= 1)
        *res = search_result::VALID;
    return 0;
}

Wordbot::Wordbot()
{
    if (!sqlite3_open(db_file.c_str(), &db3->db))
        state = db_state::VALID;
}

Wordbot::Wordbot(const Wordbot &bot)
{
    this->db3->db = bot.db3->db;
    state = db_state::VALID;
}

Wordbot::Wordbot(std::string autre_db) : db_file{autre_db}
{
    if (sqlite3_open(db_file.c_str(), &db3->db))
        state = db_state::VALID;
}

const char *Wordbot::errmsg()
{
    return err_msg;
}

Wordbot::search_result Wordbot::check(std::string word)
{
    search_result res{search_result::NOT_FOUND};

    if (state == db_state::INVALID)
        return search_result::ERROR;

    std::string query{"SELECT distinct word FROM 'english dictionary' where upper(word) = upper('" + word + "')"};
    if (sqlite3_exec(db3->db, query.c_str(), search_callback, &res, &err_msg) != SQLITE_OK)
        return search_result::ERROR;

    return res;
}

// Function to print permutations of string. Taken from geek for geeks
// This function takes three parameters:
// 1. String
// 2. Starting index of the string
// 3. Ending index of the string.
void permute(std::string a, int l, int r, std::vector<std::string> &cont)
{
    // Base case
    if (l == r)
        cont.push_back(a);
    else
    {
        // Permutations made
        for (int i = l; i <= r; i++)
        {

            // Swapping done
            std::swap(a[l], a[i]);

            // Recursion called
            permute(a, l + 1, r, cont);

            // backtrack
            std::swap(a[l], a[i]);
        }
    }
}

void ins_perc(std::string &s)
{
    int sz = s.size() - 1;
    for (auto i = 0; i < sz; i++)
        s.insert((2 * i + 1), "%");
    s.insert(0, "%");
    s.insert(s.size(), "%");
}

std::vector<std::string> Wordbot::get_ran_word(std::string letters, std::string corrigeux)
{
    std::vector<std::string> res{};

    std::vector<std::string> perms{};
    permute(letters, 0, letters.size() - 1, perms);

    std::string query = "select lower(word) from (select DISTINCT word from 'english dictionary' where length(word) = 5 and(";
    std::for_each(perms.begin(), perms.end() - 1, [&](std::string &s)
                  {ins_perc(s);
   query +=     " lower(word) like '" +  s + "' or \n "; });
    ins_perc(perms[perms.size() - 1]);
    query += "lower(word) like '" + perms[perms.size() - 1] + "' )) where word like '" + corrigeux + "' ORDER BY RANDOM()";


    if (sqlite3_exec(db3->db, query.c_str(), rand_callback, &res, &err_msg) != SQLITE_OK)
    {
        res = {};
        std::cout << err_msg << std::endl;
    }

    return res;
}

int rand_callback(void *s_res, int argc, char **argv, char **az_col_name)
{
    std::vector<std::string> *res = static_cast<std::vector<std::string> *>(s_res);
    for (int i = 0; i < argc; i++)
    {
        res->push_back(std::string{argv[i]});
    }
    return 0;
}
