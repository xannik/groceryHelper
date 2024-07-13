#include "Book.h"
#include <algorithm>
#include <iostream>

Book::Book(const std::string &name, const std::string &dbPath) : name(name), dbHelper(dbPath) {}

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
void Book::saveToDatabase() const
{
    dbHelper.executeQuery("DELETE FROM Recipe;");
    dbHelper.executeQuery("DELETE FROM Ingredient;");

    for (const auto &recipe : recipe_book)
    {
        std::string query = "INSERT INTO Recipe (id, name) VALUES (" +
                            std::to_string(recipe->getId()) + ", '" + recipe->getName() + "');";
        dbHelper.executeQuery(query);

        for (const auto &ingredient : recipe->getIngredients())
        {
            query = "INSERT INTO Ingredient (recipe_id, name, quantity, unit) VALUES (" +
                    std::to_string(recipe->getId()) + ", '" + ingredient.getName() + "', " +
                    std::to_string(ingredient.getQuantity()) + ", '" + ingredient.getUnit() + "');";
            dbHelper.executeQuery(query);
        }
    }
}

void Book::loadFromDatabase()
{
    recipe_book.clear();

    std::vector<std::pair<int, std::string>> recipes;
    dbHelper.fetchRecipes(recipes);

    for (const auto &recipe : recipes)
    {
        auto newRecipe = std::make_unique<Recipe>(recipe.second, recipe.first);

        std::vector<std::tuple<std::string, double, std::string>> ingredients;
        dbHelper.fetchIngredients(recipe.first, ingredients);

        for (const auto &ingredient : ingredients)
        {
            newRecipe->addIngredient(Ingredient(std::get<0>(ingredient), std::get<1>(ingredient), std::get<2>(ingredient)));
        }

        recipe_book.push_back(std::move(newRecipe));
    }
}
