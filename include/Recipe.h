#ifndef RECIPE_H
#define RECIPE_H

#include "Ingredient.h"
#include <vector>
#include <string>

class Recipe {
public:
    Recipe(const std::string &name);
    void addIngredient(const Ingredient &ingredient);
    void display() const;

private:
    std::string name;
    std::vector<Ingredient> ingredients;
};

#endif // RECIPE_H
