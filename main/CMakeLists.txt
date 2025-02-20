add_executable(shoppinglist main.cpp)

# Link the recipe_lib library to the recipe_main executable
target_link_libraries(shoppinglist PRIVATE recipe_lib ${Boost_LIBRARIES} )