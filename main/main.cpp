#include "Book.h"
#include "Recipe.h"
#include "Ingredient.h"
#include <iostream>
#include <memory>
#include <boost/program_options.hpp>

namespace po = boost::program_options;

void addRecipe(Book &book)
{
    std::string name;
    int id;
    std::cout << "Enter recipe name: ";
    std::cin >> name;
    std::cout << "Enter recipe id: ";
    std::cin >> id;

    auto recipe = std::make_unique<Recipe>(name, id);

    while (true)
    {
        std::string ingredientName;
        double quantity;
        std::string unit;

        std::cout << "Enter ingredient name (or 'done' to finish): ";
        std::cin >> ingredientName;
        if (ingredientName == "done")
            break;

        std::cout << "Enter quantity: ";
        std::cin >> quantity;

        std::cout << "Enter unit: ";
        std::cin >> unit;

        recipe->addIngredient(Ingredient(ingredientName, quantity, unit));
    }

    book.addRecipe(std::move(recipe));
}

int main(int argc, char *argv[])
{
    std::string dbPath = "recipes.db";
    Book book("My Recipe Book", dbPath);

    po::options_description desc("Allowed options");
    desc.add_options()("help,h", "produce help message")("add,a", "add a new recipe")("delete,d", po::value<int>(), "delete a recipe by ID")("display,p", "display all recipes")("save,s", "save recipes to database")("load,l", "load recipes from database");

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    if (vm.count("help"))
    {
        std::cout << desc << std::endl;
        return 1;
    }

    if (vm.count("add"))
    {
        addRecipe(book);
    }

    if (vm.count("delete"))
    {
        int id = vm["delete"].as<int>();
        book.deleteRecipe(id);
    }

    if (vm.count("display"))
    {
        // book.display();
        std::cout << "WIP" << std::endl;
    }

    if (vm.count("save"))
    {
        book.saveToDatabase();
    }

    if (vm.count("load"))
    {
        book.loadFromDatabase();
    }

    return 0;
}
