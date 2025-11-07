// COMSC-210 | Labs 29-31 | Mika Aquino
// IDE used: Visual Studio 2022

#include <iostream>
#include <map>
#include <array>
#include <list>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>
#include <fstream>

using namespace std;

// Define constants and enums.
enum ClothingCategories { TOPS, BOTTOMS, SHOES };						// Indexes for clothing categories
const int NUM_CATEGORIES = 3;											// Number of categories
string categoryNames[NUM_CATEGORIES] = { "Tops", "Bottoms", "Shoes"};	// Names of categories
const int NUM_DAYS = 25;												// Number of simulation days

// Define a struct representing a single clothing piece.
struct Clothing {
	string name;
	string category;	// "Tops", "Bottoms", or "Shoes"
	Clothing(string n, string c) : name(n), category(c) {}
};

// Function to generate a random number between MIN and MAX inclusive.
int generateRandomNum(const int MIN, const int MAX);

// Function to add a certain number of clothes to a given category in a store.
void addClothes(
	const int CAT_INDEX,													// Arg 1 - the index for which category to add to
	const int NUM_CLOTHES,													// Arg 2 - the number of clothes to add
	array<list<Clothing>, NUM_CATEGORIES>& store,							// Arg 3 - an array representing the particular store to add to
	const array<vector<Clothing>, NUM_CATEGORIES>& clothingPool				// Arg 5 - the pool of possible clothing to choose from when adding
);

// Function to read pieces of clothing from a file and store it into the vector clothingPool.
void populateClothingPool(array<vector<Clothing>, NUM_CATEGORIES>& clothingPool, const string FILE_NAME);

// Function to display the stock of all clothing stores.
void displayStock(const map<string, array<list<Clothing>, NUM_CATEGORIES>>& clothingStores);

// Function to add new clothing to a particular store.
void restockClothing(
	map<string, array<list<Clothing>, NUM_CATEGORIES>>& clothingStores,		// Arg 1 - a map of clothing stores
	const string& storeName,												// Arg 2 - the name of the clothing store to restock
	const array<vector<Clothing>, NUM_CATEGORIES>& clothingPool				// Arg 3 - a pool of possible clothing that can be restocked
);

// Function to sell clothing from a particular store.
bool sellClothing(
	map<string, array<list<Clothing>, NUM_CATEGORIES>>& clothingStores,		// Arg 1 - a map of clothing stores
	const string& storeName													// Arg 2 - the name of the clothing store to sell from
);

// Function to transfer clothing from one store to another.
bool transferClothing(
	map<string, array<list<Clothing>, NUM_CATEGORIES>>& clothingStores,		// Arg 1 - a map of clothing stores
	const string& storeName													// Arg 2 - the name of the clothing store to transfer from
);

int main() {
	srand(time(0));
	array<vector<Clothing>, NUM_CATEGORIES> clothingPool;

	// Read file to populate clothingPool.
	const string FILE_NAME = "clothing.txt";
	try {
		populateClothingPool(clothingPool, FILE_NAME);
	}
	catch (const runtime_error& e) {
		cout << "ERROR: " << e.what() << "\n";
		return 1;
	}
	
	// Create a map of clothing stores.
	// Each store has an array of 3 lists for Tops, Bottoms, and Shoes.
	map<string, array<list<Clothing>, NUM_CATEGORIES>> clothingStores;
	clothingStores["Aesthetic Apparel"];
	clothingStores["Bubbly Boutique"];
	clothingStores["Casual Couture"];

	// Initialize each store.
	for (auto& store : clothingStores) {
		// Each store will start with 1 to 3 clothing pieces per category.
		const int MIN = 1;
		const int MAX = 3;

		// Add tops.
		int numClothes = generateRandomNum(MIN, MAX);
		addClothes(TOPS, numClothes, store.second, clothingPool);

		// Add bottoms.
		numClothes = generateRandomNum(MIN, MAX);
		addClothes(BOTTOMS, numClothes, store.second, clothingPool);

		// Add shoes.
		numClothes = generateRandomNum(MIN, MAX);
		addClothes(SHOES, numClothes, store.second, clothingPool);
	}

	// Before the time periods begin, display the initial state of each store, showing their beginning stock.
	cout << "INITIAL STOCK:\n\n";
	displayStock(clothingStores);
	cout << "\n";

	// Begin a time-based simulation for clothing store changes.
	cout << "Now beginning time intervals.\n";

	// For 25 time intervals:
	for (int i = 1; i <= NUM_DAYS; ++i) {
		// Output the current day number.
		cout << "\n--- DAY " << i << " ---\n";

		// Iterate through each clothing store.
		for (const auto& store : clothingStores) {
			bool somethingHappened = false;
			int probability;

			// Output the current store name.
			cout << "At " << store.first << ":\n";

			// At a particular clothing store, these events have a chance of happening:
		
			// Event 1 (60% chance) - Clothing gets restocked.
			probability = generateRandomNum(1, 100);
			if (probability <= 60) {
				restockClothing(clothingStores, store.first, clothingPool);
				somethingHappened = true;
			}

			// Event 2 (80% cnance) - Clothing gets sold.
			probability = generateRandomNum(1, 100);
			if (probability <= 80) {
				if (sellClothing(clothingStores, store.first)) {
					somethingHappened = true;
				}
			}

			// Event 3 (20% chance) - Clothing gets transferred between stores.
			probability = generateRandomNum(1, 100);
			if (probability <= 20) {
				if (transferClothing(clothingStores, store.first)) {
					somethingHappened = true;
				}
			}

			// If nothing happened at this particular clothing store, output that nothing happened.
			if (!somethingHappened) {
				cout << "Nothing happened.\n";
			}

			cout << "\n";
		}
		
		// Display the stock at the end of the day.
		displayStock(clothingStores);
	}

	return 0;
}

// Function to generate a random number between MIN and MAX inclusive.
int generateRandomNum(const int MIN, const int MAX) {
	return MIN + (rand() % (MAX - MIN + 1));
}

// Function to add a certain number of clothes to a given category in a store.
void addClothes(const int CAT_INDEX, const int NUM_CLOTHES, array<list<Clothing>, NUM_CATEGORIES>& store, const array<vector<Clothing>, NUM_CATEGORIES>& clothingPool) {
	for (int i = 0; i < NUM_CLOTHES; ++i) {
		int index = generateRandomNum(0, (clothingPool[CAT_INDEX].size() - 1));
		store[CAT_INDEX].push_back(clothingPool[CAT_INDEX].at(index));
	}
}

// Function to read pieces of clothing from a file and store it into the vector clothingPool.
void populateClothingPool(array<vector<Clothing>, NUM_CATEGORIES>& clothingPool, const string FILE_NAME) {
	ifstream clothingFile;
	clothingFile.open(FILE_NAME);

	if (!clothingFile) {
		throw runtime_error("Unable to open the file " + FILE_NAME + ".\n");
	}

	// Read file into clothingPool
	string clothingName;
	string clothingCategory;
	while (getline(clothingFile, clothingName)) {
		getline(clothingFile, clothingCategory);

		if (clothingCategory == categoryNames[TOPS]) {
			clothingPool[TOPS].push_back(Clothing(clothingName, clothingCategory));
		}
		else if (clothingCategory == categoryNames[BOTTOMS]) {
			clothingPool[BOTTOMS].push_back(Clothing(clothingName, clothingCategory));
		}
		else if (clothingCategory == categoryNames[SHOES]) {
			clothingPool[SHOES].push_back(Clothing(clothingName, clothingCategory));
		}
	}

	clothingFile.close();
}

// Function to display the stock of all clothing stores.
void displayStock(const map<string, array<list<Clothing>, NUM_CATEGORIES>>& clothingStores) {
	// For every store,
	for (const auto& store : clothingStores) {
		cout << "[ STOCK REPORT for " << store.first << " ]\n";

		// For every clothing category (tops, bottoms, shoes)
		for (int i = 0; i < NUM_CATEGORIES; ++i) {
			const auto& category = store.second[i];	// get list for current category
			cout << ">> " << categoryNames[i] << ": ";
			if (store.second[i].empty()) {
				cout << "OUT OF STOCK\n";
			}
			else {
				cout << "\n";
				for (const auto& clothingPiece : category) {
					cout << "\t- " << clothingPiece.name << "\n";
				}
			}
		}
		cout << "\n";
	}
}

// Function to add new clothing to a particular store.
void restockClothing(map<string, array<list<Clothing>, NUM_CATEGORIES>>& clothingStores, const string& storeName,
	const array<vector<Clothing>, NUM_CATEGORIES>& clothingPool) {

	// Choose a random category to be added to.
	int catIndex = rand() % 3;

	// Choose a random number of clothes to add to that category.
	const int MIN = 1;
	const int MAX = 3;
	int numClothes = generateRandomNum(MIN, MAX);

	// Output action.
	cout << numClothes << " " << categoryNames[catIndex] << " get restocked\n";

	// Add clothes to that category.
	auto& store = clothingStores[storeName];
	addClothes(catIndex, numClothes, store, clothingPool);
}

// Function to sell clothing from a particular store.
bool sellClothing(map<string, array<list<Clothing>, NUM_CATEGORIES>>& clothingStores, const string& storeName) {

	// Choose a random category to sell from.
	int catIndex = generateRandomNum(0, 2);

	// Return if that category is empty (can't sell anything if there's nothing).
	auto& store = clothingStores[storeName];
	if (store[catIndex].empty()) {
		return false;	// False - nothing sold
	}

	// Choose a random number of clothes to sell from that category.
	const int MIN = 1;
	const int MAX = 3;
	int randomNum = generateRandomNum(1, 3);

	// Ensure we don't sell more clothes than we have.
	while (randomNum > store[catIndex].size()) {
		randomNum = generateRandomNum(1, 3);
	}

	// Output action.
	cout << randomNum << " " << categoryNames[catIndex] << " get sold\n";

	// Sell clothes from that category.
	for (int i = 0; i < randomNum; ++i) {
		// Select a random clothing piece to sell.
		auto it = store[catIndex].begin();
		int position = generateRandomNum(0, (store[catIndex].size() - 1));
		advance(it, position);

		// Sell that clothing piece.
		store[catIndex].erase(it);
	}
	return true;	// True - something sold
}

// Function to transfer clothing from one store to another.
bool transferClothing(map<string, array<list<Clothing>, NUM_CATEGORIES>>& clothingStores, const string& storeName) {

	// Choose a random category to transfer.
	int catIndex = generateRandomNum(0, 2);

	// If the category is empty, return without transferring.
	auto& thisStore = clothingStores[storeName];
	if (thisStore[catIndex].empty()) {
		return false;
	}

	// Choose a random number of clothes to transfer from that category.	
	const int MIN = 1;
	const int MAX = 3;
	int numClothes = generateRandomNum(MIN, MAX);

	// Ensure we don't transfer more clothing than we have.
	while (numClothes > thisStore[catIndex].size()) {
		numClothes = generateRandomNum(MIN, MAX);
	}

	// Choose a random clothing store to transfer to.
	auto otherStoreIt = clothingStores.begin();
	do {
		int position = generateRandomNum(0, clothingStores.size() - 1);
		otherStoreIt = clothingStores.begin();
		advance(otherStoreIt, position);
	} while (otherStoreIt->first == storeName);		// Ensure that the store doesn't transfer to itself.

	// Output action.
	if (otherStoreIt != clothingStores.end()) {
		cout << storeName << " transfers " << numClothes << " " << categoryNames[catIndex] << " to " << otherStoreIt->first << ".\n";
	}

	// Remove clothes from this store and add them to the other.
	for (int i = 0; i < numClothes; ++i) {
		// Select a random clothing piece to transfer.
		auto it = thisStore[catIndex].begin();
		int position = generateRandomNum(0, (thisStore[catIndex].size() - 1));
		advance(it, position);

		// Save that clothing piece.
		Clothing transferredPiece = *it;

		// Remove that clothing piece from this store.
		thisStore[catIndex].erase(it);

		// Add that clothing piece to the other store.
		otherStoreIt->second[catIndex].push_back(transferredPiece);
	}

	return true;
}