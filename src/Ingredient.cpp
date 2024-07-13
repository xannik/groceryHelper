#include "../include/Ingredient.h"
#include <string>

Ingredient::Ingredient(const std::string &name, double quantity, const std::string &unit)
    : name(name), quantity(quantity), unit(unit) {}

std::string Ingredient::toString() const
{
    return std::to_string(quantity) + " " + unit + " of " + name;
}
double Ingredient::getQuantity() const
{
    return quantity;
}

std::string Ingredient::getUnit() const
{
    return unit;
}

std::string Ingredient::getName() const
{
    return name;
}