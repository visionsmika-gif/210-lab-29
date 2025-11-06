#ifndef CLOTHING_STORE_H
#define CLOTHING_STORE_H

#include <iostream>
#include <map>
#include <array>
#include <list>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>
#include <fstream>

// CONSTANTS AND ENUMS
enum ClothingCategories { TOPS, BOTTOMS, SHOES };
const int NUM_CATEGORIES = 3;
std::string categoryNames[NUM_CATEGORIES];
const int NUM_DAYS = 25;

// STRUCTS
struct Clothing {
	std::string name;
	std::string category;	// "Tops", "Bottoms", or "Shoes"
	Clothing(std::string n, std::string c);
};

// FUNCTIONS
int generateRandomNum(const int MIN, const int MAX);

void addClothes(const int CAT_INDEX, const int NUM_CLOTHES, std::array<std::list<Clothing>, NUM_CATEGORIES>& store,
				const std::array<std::vector<Clothing>, NUM_CATEGORIES>& clothingPool);

void populateClothingPool(std::array<std::vector<Clothing>, NUM_CATEGORIES>& clothingPool, const std::string FILE_NAME);

void displayStock(const std::map<std::string, std::array<std::list<Clothing>, NUM_CATEGORIES>>& clothingStores);

void restockClothing(std::map<std::string, std::array<std::list<Clothing>, NUM_CATEGORIES>>& clothingStores, const std::string& storeName,
	const std::array<std::vector<Clothing>, NUM_CATEGORIES>& clothingPool);

bool sellClothing(std::map<std::string, std::array<std::list<Clothing>, NUM_CATEGORIES>>& clothingStores, const std::string& storeName);
bool transferClothing(std::map<std::string, std::array<std::list<Clothing>, NUM_CATEGORIES>>& clothingStores, const std::string& storeName);

#endif