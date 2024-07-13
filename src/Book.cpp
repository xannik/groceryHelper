#include "Book.h"
#include <algorithm>
#include <iostream>
Book::Book(const std::string &name) : name(name) {}

void Book::addRecipe(std::unique_ptr<Recipe> recipe_p)
{
    recipe_book.push_back(std::move(recipe_p));
}

void Book::deleteRecipe(int id)
{

    recipe_book.erase(
        std::remove_if(recipe_book.begin(), recipe_book.end(), [id](const std::unique_ptr<Recipe> &recipe)
                       { return recipe->getId() == id; }),
        recipe_book.end());
}
void Book::deleteRecipe(std::string &name)
{

    recipe_book.erase(
        std::remove_if(recipe_book.begin(), recipe_book.end(), [&name](const std::unique_ptr<Recipe> &recipe)
                       { return recipe->getName() == name; }),
        recipe_book.end());
}

const Recipe *Book::getRecipe(std::string &name)
{
    auto it = std::find_if(recipe_book.begin(), recipe_book.end(), [&name](const std::unique_ptr<Recipe> &recipe_p)
                           { return recipe_p->getName() == name; });
    if (it != recipe_book.end())
    {
        return it->get();
    }
    else
    {
        std::cout << "Recipe with name: " << name << "not found" << std::endl;
        return nullptr;
    }
}
const Recipe *Book::getRecipe(int id)
{
    auto it = std::find_if(recipe_book.begin(), recipe_book.end(), [id](const std::unique_ptr<Recipe> &recipe_p)
                           { return recipe_p->getId() == id; });
    if (it != recipe_book.end())
    {
        return it->get();
    }
    else
    {
        std::cout << "Recipe with ID: " << id << "not found" << std::endl;
        return nullptr;
    }
}