// PSEUDOCODE COMMENTS AND MOCKUP:

// Include headers for files, data structures, etc
#include <iostream>
#include <map>
#include <array>
#include <list>
#include <vector>
#include <string>
#include <ctime>	// for seed
#include <cstdlib>	// for RNG
#include <fstream>

using namespace std;

// Define constants for the number of simulation days, the number of stores, the name of each store, the name of each clothing category (top, bottom, or shoes)
enum ClothingCategories { TOPS, BOTTOMS, SHOES };
const int NUM_CATEGORIES = 3;
string categoryNames[NUM_CATEGORIES] = { "Tops", "Bottoms", "Shoes"};
const int NUM_DAYS = 25;

// Define a struct for a single clothing piece, containing the clothing piece's name and category (top, bottom, or shoes)
struct Clothing {
	string name;
	string category;	// "Tops", "Bottoms", or "Shoes"
	Clothing(string n, string c) : name(n), category(c) {}
};

int generateRandomNum(const int MIN, const int MAX) {
	return MIN + (rand() % (MAX - MIN + 1));
}

void addClothes(const int CAT_INDEX, const int NUM_CLOTHES, array<list<Clothing>, NUM_CATEGORIES>& store, const array<vector<Clothing>, NUM_CATEGORIES>& clothingPool) {
	for (int i = 0; i < NUM_CLOTHES; ++i) {
		int index = generateRandomNum(0, (clothingPool[CAT_INDEX].size() - 1));
		cout << "Adding " << categoryNames[CAT_INDEX] << ".\n";
		store[CAT_INDEX].push_back(clothingPool[CAT_INDEX].at(index));
	}
}

// displayStock() - Function to display store stock
// Arguments: a map of clothing stores.
// Goes through each map element, outputs the name of the store (map key) and the clothing stores' tops, bottoms, and shoes (map value)
void displayStock(const map<string, array<list<Clothing>, NUM_CATEGORIES>>& clothingStores) {
	// For every store,
	for (const auto& store : clothingStores) {
		cout << "[ STOCK REPORT for " << store.first << " ]\n";

		// For every clothing category (tops, bottoms, shoes)
		for (int i = 0; i < NUM_CATEGORIES; ++i) {
			const auto& category = store.second[i];	// get list for current category
			cout << ">> " << categoryNames[i] << ":\n";
			if (store.second[i].empty()) {
				cout << "OUT OF STOCK\n";
			}
			else {
				for (const auto& clothingPiece : category) {
					cout << "\t- " << clothingPiece.name << "\n";
				}
			}
		}
		cout << "\n";
	}
}

// restockClothing() - Function to add new clothing to a particular store
// Arguments: a map of clothing stores, the name of the particular clothing store, the three vectors for tops, bottoms, and shoes.
// One random category (tops, bottoms, shoes) is selected restocked with a random number of clothes
void restockClothing(map<string, array<list<Clothing>, NUM_CATEGORIES>>& clothingStores, const string& storeName,
					const array<vector<Clothing>, NUM_CATEGORIES>& clothingPool) {
	
	// Choose a random category to be added to.
	int catIndex = rand() % 3;

	// Choose a random number of clothes to add to that category.
	const int MIN = 1;
	const int MAX = 3;
	int numClothes = MIN + (rand() % (MAX - MIN + 1));	// Random number between 1-3

	cout << numClothes << " " << categoryNames[catIndex] << " have been restocked\n";


	// Add clothes to that category.
	auto& store = clothingStores[storeName];
	addClothes(catIndex, numClothes, store, clothingPool);
}


// sellClothing() - Function to sell clothing from a particular store
// Arguments - a map of clothing stores, the name of the particular clothing store.
// One random category (tops, bottoms, shoes) is selected and guaranteed to sell a random number of clothes
// The other categories have a chance to sell
bool sellClothing(map<string, array<list<Clothing>, NUM_CATEGORIES>>& clothingStores, const string& storeName) {

	// Choose a random category to sell from.
	int categoryIndex = rand() % 3;

	// Return if that category is empty (can't sell if there's nothing)
	auto& store = clothingStores[storeName];
	if (store[categoryIndex].empty()) {
		return false;	// false - nothing sold
	}

	// Choose a random number of clothes to sell from category.	
	const int MIN = 1;
	const int MAX = 3;
	int randomNum = MIN + (rand() % (MAX - MIN + 1));	// Random number between 1-3

	// Ensure we don't sell more clothes than we have
	while (randomNum > store[categoryIndex].size()) {
		randomNum = MIN + (rand() % (MAX - MIN + 1));
	}

	cout << randomNum << " " << categoryNames[categoryIndex] << " have been sold\n";

	// Sell clothes from that category.
	for (int i = 0; i < randomNum; ++i) {
		store[categoryIndex].pop_front();	// access particular store's category and remove an element		
		// In the real code, a random piece of clothing would be sold,
		// but for simplicity in this mockup example, the front of the category is just sold.

	}
	return true;	// true - something sold
}


// transferClothing() - Function to transfer clothing between two stores
// Arguments - a map of clothing stores, the name of the particular clothing store
// A random other store is chosen to be transferred to
// A random piece of clothing from a random category is taken from the parameter store and added to the other store
void transferClothing(map<string, array<list<Clothing>, NUM_CATEGORIES>>& clothingStores, const string& storeName) {
	int itOffset = rand() % clothingStores.size();	// select a random clothing store

	// In the real code, more advanced logic will be added to transferClothing().
	// However, since the mockup only has 1 clothing store, transferClothing() has not yet had all its logic implemented
	// (because a clothign store can't transfer to itself)
	
	// TODO: Ensure that a clothing store does not select itself as the store to transfer to.
	auto it = clothingStores.begin();
	advance(it, itOffset);

	if (it != clothingStores.end()) {
		cout << storeName << " transfers clothing to " << it->first << "\n";
	}
}

int main() {
	srand(time(0));
	array<vector<Clothing>, 3> clothingPool;

	const string FILE_NAME = "clothing.txt";
	ifstream clothingFile;
	clothingFile.open(FILE_NAME);

	if (!clothingFile) {
		cout << "ERROR: Unable to open the file " << FILE_NAME << ".\n";
		return 1;
	}
	
	string clothingName;
	string clothingCategory;
	while (getline(clothingFile, clothingName)) {
		getline(clothingFile, clothingCategory);

		if (clothingCategory == "Tops") {
			clothingPool[TOPS].push_back(Clothing(clothingName, clothingCategory));
		}
		else if (clothingCategory == "Bottoms") {
			clothingPool[BOTTOMS].push_back(Clothing(clothingName, clothingCategory));
		}
		else if (clothingCategory == "Shoes") {
			clothingPool[SHOES].push_back(Clothing(clothingName, clothingCategory));
		}
	}

	// Create a map of clothing stores.
	// Each store has an array of 3 lists for tops, bottoms, and shoes.
	map<string, array<list<Clothing>, NUM_CATEGORIES>> clothingStores;
	clothingStores["Aesthetic Apparel"];
	clothingStores["Bubbly Boutique"];
	clothingStores["Casual Couture"];

	// Initialize each store.
	for (auto& store : clothingStores) {
		// Output current store name.
		cout << "Initializing " << store.first << ":\n";

		// Each store will start with 1 to 3 clothing pieces per category.
		const int MIN_CLOTHES = 1;
		const int MAX_CLOTHES = 3;

		// Add 1 to 3 tops.
		int numClothes = generateRandomNum(MIN_CLOTHES, MAX_CLOTHES);
		addClothes(TOPS, numClothes, store.second, clothingPool);

		// Add 1 to 3 bottoms.
		numClothes = generateRandomNum(MIN_CLOTHES, MAX_CLOTHES);
		addClothes(BOTTOMS, numClothes, store.second, clothingPool);

		// Add 1 to 3 shoes.
		numClothes = generateRandomNum(MIN_CLOTHES, MAX_CLOTHES);
		addClothes(SHOES, numClothes, store.second, clothingPool);

		cout << "\n";
	}

	// Before the time periods begin, call displayStock() to display the initial state of each store, showing their beginning stock
	displayStock(clothingStores);
	cout << "\n";

	// Begin a time-based simulation for clothing store changes:
	cout << "Now beginning time intervals.\n";
	// For 25 time intervals:
	for (int i = 0; i <= NUM_DAYS; ++i) {
		cout << "\n--- DAY " << i << " ---\n";
		// Iterate through each clothing store.
		for (const auto& store : clothingStores) {
			bool somethingHappened = false;

			cout << "At " << store.first << ":\n";

			int probability;

			// For that particular clothing store, these events have a chance of happening:
			// Event 1 (70% chance) - Clothing gets restocked. (call restockClothing)
			probability = generateRandomNum(1, 100);
			// restockClothing(clothingStores, store.first);
			if (probability <= 70) {
				restockClothing(clothingStores, store.first, clothingPool);
				somethingHappened = true;
			}

			// Event 2 (60% cnance) - Clothing gets sold. (call sellClothing)
			probability = generateRandomNum(1, 100);
			if (probability <= 60) {
				if (sellClothing(clothingStores, store.first)) {
					somethingHappened = true;
				}
			}

			// sellClothing(clothingStores, store.first);

			// Event 3 (20% chance) - Clothing gets transferred between stores. (call transferClothing)
			probability = generateRandomNum(1, 100);
			if (probability <= 20) {
				transferClothing(clothingStores, store.first);
			}

			if (!somethingHappened) {
				cout << "Nothing happened.\n";
			}
			// Whenever one of these events happen, print the change, e.g. "3 tops were added to [Clothing Store Name]".

			cout << "\n";
		}
		// Display stock by the end of the day
		displayStock(clothingStores);

		// Wait or pause briefly to simulate the passage of time between intervals

	// End of main function
	}

	return 0;
}