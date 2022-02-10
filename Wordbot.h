#ifndef WORDBOT_H
#define WORDBOT_H


#include <type_traits>
#include <sqlite3.h>
#include <memory>
#include <string>
#include<vector>
#include<algorithm>


class Wordbot final
{
private:
    static int search_callback(void *search_state, int argc, char **argv, char **az_col_name);
public:
    enum class search_result
    {
        NOT_FOUND,
        VALID,
        ERROR
    };

    enum class db_state
    {
        INVALID,
        VALID
    };

    // C style struct with lack of constructors and destructors require this wrapping
    class sqlite3_wrapper
    {
    public:
        sqlite3 *db;
        sqlite3_wrapper() {}
        ~sqlite3_wrapper()
        {
            if (db != nullptr)
                sqlite3_close(db);
        }
    };

private:
    std::unique_ptr<sqlite3_wrapper> db3{new sqlite3_wrapper}; // One database connnection to minimize memory leak
    std::string db_file{"C:/Users/USER/Documents/cpp/dict.db"};
    char *err_msg;

public:
    db_state state{db_state::INVALID};
    Wordbot();
    Wordbot(std::string autre_db);
    const char *errmsg();
    search_result check(std::string word);
    std::vector<std::string> get_ran_word(std::string,std::string corrigeux);
    Wordbot(const Wordbot &);
};


// Function to print permutations of string. Taken from geek for geeks
// This function takes three parameters:
// 1. String
// 2. Starting index of the string
// 3. Ending index of the string.
void permute(std::string a, int l, int r, std::vector<std::string>& cont);

int rand_callback(void *search_state, int argc, char **argv, char **az_col_name);

#endif