#ifndef RECIPE_H
#define RECIPE_H

#include "Ingredient.h"
#include <vector>
#include <string>

class Recipe
{
public:
    Recipe(const std::string &name, int id);

    Recipe(const Recipe &other) = delete;
    Recipe &operator=(const Recipe &other) = delete;
    ~Recipe() = default;

    void addIngredient(const Ingredient &ingredient);
    void display() const;
    std::vector<Ingredient> getIngredients();
    int getId() const;
    std::string getName() const;

private:
    std::string name;
    std::vector<Ingredient> ingredients;
    const int id;
};

#endif // RECIPE_H
