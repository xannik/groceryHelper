#include "../include/Recipe.h"
#include <iostream>

Recipe::Recipe(const std::string &name) : name(name) {}

void Recipe::addIngredient(const Ingredient &ingredient) {
    ingredients.push_back(ingredient);
}

void Recipe::display() const {
    std::cout << "Recipe for: " << name << std::endl;
    for (const auto &ingredient : ingredients) {
        std::cout << "- " << ingredient.toString() << std::endl;
    }
}
