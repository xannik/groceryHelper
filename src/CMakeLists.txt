# Create a library from the Ingredient and Recipe sources
add_library(recipe_lib Ingredient.cpp Recipe.cpp Book.cpp SQLiteHelper.cpp)

target_link_libraries(recipe_lib PUBLIC ${SQLite3_LIBRARIES})
target_include_directories(recipe_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})