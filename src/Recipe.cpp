#include "../include/Recipe.h"
#include <iostream>

Recipe::Recipe(const std::string &name, const int id) : name(name), id(id) {}

void Recipe::addIngredient(const Ingredient &ingredient)
{
    ingredients.push_back(ingredient);
}

void Recipe::display() const
{
    std::cout << "Recipe for: " << name << std::endl;
    for (const auto &ingredient : ingredients)
    {
        std::cout << "- " << ingredient.toString() << std::endl;
    }
}

int Recipe::getId() const
{
    return id;
}

std::string Recipe::getName() const
{
    return name;
}