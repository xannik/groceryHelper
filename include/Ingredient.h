#ifndef INGREDIENT_H
#define INGREDIENT_H

#include <string>

class Ingredient
{
public:
    Ingredient(const std::string &name, double quantity, const std::string &unit);
    std::string toString() const;
    double getQuantity() const;
    std::string getUnit() const;
    std::string getName() const;

private:
    std::string name;
    double quantity;
    std::string unit;
};

#endif // INGREDIENT_H
