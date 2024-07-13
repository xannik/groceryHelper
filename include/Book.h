#ifndef BOOK_H
#define BOOK_H

#include "Recipe.h"
#include "SQLiteHelper.h"
#include <vector>
#include <memory>

class Book
{
public:
    Book(const std::string &name, const std::string &dbPath);

    void addRecipe(std::unique_ptr<Recipe> recipe_p);
    void deleteRecipe(const int id);
    void deleteRecipe(std::string &name);
    const Recipe *getRecipe(std::string &name);
    const Recipe *getRecipe(const int id);

    void saveToDatabase() const;
    void loadFromDatabase();

private:
    std::string name;
    std::vector<std::unique_ptr<Recipe>> recipe_book;
    SQLiteHelper dbHelper;
};

#endif // BOOK_h