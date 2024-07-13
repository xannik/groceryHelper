#include "SQLiteHelper.h"
#include <iostream>
#include <tuple>

SQLiteHelper::SQLiteHelper(const std::string &dbPath)
{
    if (sqlite3_open(dbPath.c_str(), &db) != SQLITE_OK)
    {
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
        db = nullptr;
    }
    else
    {
        std::string createRecipeTable = "CREATE TABLE IF NOT EXISTS Recipe ("
                                        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                                        "name TEXT NOT NULL);";

        std::string createIngredientTable = "CREATE TABLE IF NOT EXISTS Ingredient ("
                                            "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                                            "recipe_id INTEGER,"
                                            "name TEXT NOT NULL,"
                                            "quantity REAL NOT NULL,"
                                            "unit TEXT NOT NULL,"
                                            "FOREIGN KEY(recipe_id) REFERENCES Recipe(id));";

        executeQuery(createRecipeTable);
        executeQuery(createIngredientTable);
    }
}

SQLiteHelper::~SQLiteHelper()
{
    if (db)
    {
        sqlite3_close(db);
    }
}

bool SQLiteHelper::executeQuery(const std::string &query) const
{
    char *errMsg = nullptr;
    if (sqlite3_exec(db, query.c_str(), nullptr, nullptr, &errMsg) != SQLITE_OK)
    {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
        return false;
    }
    return true;
}

bool SQLiteHelper::fetchRecipes(std::vector<std::pair<int, std::string>> &recipes) const
{
    sqlite3_stmt *stmt;
    std::string query = "SELECT id, name FROM Recipe;";
    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr) != SQLITE_OK)
    {
        std::cerr << "Failed to fetch recipes: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }

    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        int id = sqlite3_column_int(stmt, 0);
        std::string name = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1));
        recipes.emplace_back(id, name);
    }
    sqlite3_finalize(stmt);
    return true;
}

bool SQLiteHelper::fetchIngredients(int recipeId, std::vector<std::tuple<std::string, double, std::string>> &ingredients) const
{
    sqlite3_stmt *stmt;
    std::string query = "SELECT name, quantity, unit FROM Ingredient WHERE recipe_id = ?;";
    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr) != SQLITE_OK)
    {
        std::cerr << "Failed to fetch ingredients: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }
    sqlite3_bind_int(stmt, 1, recipeId);

    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        std::string name = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 0));
        double quantity = sqlite3_column_double(stmt, 1);
        std::string unit = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 2));
        ingredients.emplace_back(name, quantity, unit);
    }
    sqlite3_finalize(stmt);
    return true;
}
