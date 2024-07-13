#ifndef BOOK_H
#define BOOK_H

#include "Recipe.h"
#include <vector>
#include <memory>

class Book
{
public:
    Book(const std::string &name);

    void addRecipe(std::unique_ptr<Recipe> recipe_p);
    void deleteRecipe(const int id);
    void deleteRecipe(std::string &name);
    const Recipe *getRecipe(std::string &name);
    const Recipe *getRecipe(const int id);

    void storeBook();
    void readStoredBook();

private:
    std::string name;
    std::vector<std::unique_ptr<Recipe>> recipe_book;
};

#endif // BOOK_h