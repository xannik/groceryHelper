#ifndef SQLITEHELPER_H
#define SQLITEHELPER_H

#include <sqlite3.h>
#include <string>
#include <vector>

class SQLiteHelper
{
public:
    SQLiteHelper(const std::string &dbPath);
    ~SQLiteHelper();

    bool executeQuery(const std::string &query) const;
    bool fetchRecipes(std::vector<std::pair<int, std::string>> &recipes) const;
    bool fetchIngredients(int recipeId, std::vector<std::tuple<std::string, double, std::string>> &ingredients) const;

private:
    sqlite3 *db;
};

#endif // SQLITEHELPER_H
