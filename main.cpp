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

// displayStock() - Function to display store stock
// Arguments: a map of clothing stores.
// Goes through each map element, outputs the name of the store (map key) and the clothing stores' tops, bottoms, and shoes (map value)
void displayStock(const map<string, array<list<Clothing>, 3>>& clothingStores) {
	cout << "Called displayStock()\n";

	// For every store,
	for (const auto& store : clothingStores) {
		cout << "Now displaying stock for " << store.first << ":\n";

		// For every clothing category (tops, bottoms, shoes)
		for (const auto& category : store.second) {
			// Output category name
			cout << category.front().category << ": ";
			// Output all the clothing items in that category.
			for (const auto& clothingPiece : category) {
				cout << clothingPiece.name << ", ";
			}
			cout << "\n";
		}
	}
	cout << "End of displayStock()\n";
}

// restockClothing() - Function to add new clothing to a particular store
// Arguments: a map of clothing stores, the name of the particular clothing store, the three vectors for tops, bottoms, and shoes.
// One random category (tops, bottoms, shoes) is selected restocked with a random number of clothes
void restockClothing(map<string, array<list<Clothing>, NUM_CATEGORIES>>& clothingStores, const string& storeName,
					const array<vector<Clothing>, NUM_CATEGORIES>& clothingPool) {
	
	// Choose a random category to be added to.
	int categoryIndex = rand() % 3;


	// Choose a random number of clothes to add to that category.
	const int MIN = 1;
	const int MAX = 3;
	int randomNum;	// Random number between 1-3

	cout << randomNum << " " << categoryNames[categoryIndex] << " have been restocked\n";


	// Add clothes to that category.
	randomNum = MIN + (rand() % (MAX - MIN + 1));
	for (int i = 0; i < randomNum; ++i) {
		auto& store = clothingStores[storeName];							// access particular store
		store[categoryIndex].push_back(clothingPool[categoryIndex].at(0));	// access particular store's category and add a new element
		// In the real code, a random index for a random clothing piece in clothingPool would be chosen,
		// but for simplicity in this mockup example, the index is just 0.
	}
}


// sellClothing() - Function to sell clothing from a particular store
// Arguments - a map of clothing stores, the name of the particular clothing store.
// One random category (tops, bottoms, shoes) is selected and guaranteed to sell a random number of clothes
// The other categories have a chance to sell
void sellClothing(map<string, array<list<Clothing>, NUM_CATEGORIES>>& clothingStores, const string& storeName) {
	// Choose a random category to sell from.
	int categoryIndex = rand() % 3;

	// Choose a random number of clothes to add to that category.
	const int MIN = 1;
	const int MAX = 3;
	int randomNum;	// Random number between 1-3

	cout << randomNum << " " << categoryNames[categoryIndex] << " have been sold\n";

	// Add clothes to that category.
	randomNum = MIN + (rand() % (MAX - MIN + 1));
	for (int i = 0; i < randomNum; ++i) {
		auto& store = clothingStores[storeName];							// access particular store
		store[categoryIndex].push_back(clothingPool[categoryIndex].at(0));	// access particular store's category and add a new element
		// In the real code, a random index for a random clothing piece in clothingPool would be chosen,
		// but for simplicity in this mockup example, the index is just 0.
	}
}


// transferClothing() - Function to transfer clothing between two stores
// Arguments - a map of clothing stores, the name of the particular clothing store
// A random other store is chosen to be transferred to
// A random piece of clothing from a random category is taken from the parameter store and added to the other store

// Define main function
int main() {
	srand(time(0));

	// Open external file 
	cout << "Opening file...\n";
	array<vector<Clothing>, 3> clothingPool;

		// If the file does not open, print an error and exit
		// Read at least 100 pieces of clothing from a file, extracting its data, and storing into three vectors (depending on if it's a top, bottom, or shoes)
		cout << "Reading file into vectors topsPool, bottomsPool, shoesPool.\n";
		// Here are some mockup examples of clothing pieces that may be read from the file:
		clothingPool[TOPS].push_back(Clothing("Striped Blouse", "Tops"));
		clothingPool[BOTTOMS].push_back(Clothing("Black Slacks", "Bottoms"));
		clothingPool[SHOES].push_back(Clothing("Knee-high Boots", "Shoes"));
		// Close the file
		cout << "Closing file.\n\n";

	// Create a map of clothing stores
	// The map's key is the clothing store name (string)
	// The map's value is an array of 3 lists for tops, bottoms, and shoes
	map<string, array<list<Clothing>, NUM_CATEGORIES>> clothingStores;
	clothingStores["Bubbly Boutique"];

	// For each clothing store, go through each of its categories: tops, bottoms, shoes
	cout << "Initializing clothingStores with values from topsPool, bottomsPool, and shoesPool.\n";
	for (auto& store : clothingStores) {
		// Output store name
		cout << "Initializing " << store.first << ":\n";

		const int MAX = 1;
		const int MIN = 3;
		int randomNum;	// Random number between 1-3

		// Add a random number of tops from the vector of tops
		randomNum = MIN + (rand() % (MAX - MIN + 1));
		for (int i = 0; i < randomNum; ++i) {
			cout << "Adding tops.\n";
			store.second[TOPS].push_back(clothingPool[TOPS].at(0));	// In the real code, a random index for a random top in topsPool would be chosen,
																	// but for simplicity in this mockup example, the index is just 0.
		}

		// Add a random number of bottoms from the vector of bottoms
		randomNum = MIN + (rand() % (MAX - MIN + 1));
		for (int i = 0; i < randomNum; ++i) {
			cout << "Adding bottoms.\n";
			store.second[BOTTOMS].push_back(clothingPool[BOTTOMS].at(0));
		}

		// Add a random number of shoes from the vector of shoes
		randomNum = MIN + (rand() % (MAX - MIN + 1));
		for (int i = 0; i < randomNum; ++i) {
			cout << "Adding bottoms.\n";
			store.second[SHOES].push_back(clothingPool[SHOES].at(0));
		}
		cout << "\n";
	}

	// Before the time periods begin, call displayStock() to display the initial state of each store, showing their beginning stock
	displayStock(clothingStores);
	cout << "\n";

	// Begin a time-based simulation for clothing store changes:
	cout << "Now beginning time intervals.\n";
	// For 25 time intervals:
	for (int i = 0; i < NUM_DAYS; ++i) {
		cout << "\n--- DAY " << i << " ---\n";
		// Iterate through each clothing store.
		for (const auto& store : clothingStores) {
			bool somethingHappened = false;

			cout << "At " << store.first << ":\n";

			int probability;

			// For that particular clothing store, these events have a chance of happening:
			// Event 1 (60% chance) - Clothing gets restocked. (call restockClothing)
			probability = rand() % 100 + 1;
			// restockClothing(clothingStores, store.first);
			if (probability <= 60) {
				restockClothing(clothingStores, store.first, clothingPool);
				somethingHappened = true;
			}

			// Event 2 (70% cnance) - Clothing gets sold. (call sellClothing)
			probability = rand() % 100 + 1;
			if (probability <= 70) {
				
			}

			// sellClothing(clothingStores, store.first);

			// Event 3 (20% chance) - Clothing gets transferred between stores. (call transferClothing)
			probability = rand() % 60 + 1;

			if (!somethingHappened) {
				cout << "Nothing happened.\n";
			}
			// Whenever one of these events happen, print the change, e.g. "3 tops were added to [Clothing Store Name]".

			cout << "\n";
		}
		// Wait or pause briefly to simulate the passage of time between intervals
		displayStock(clothingStores);
	// End of main function
	}

	return 0;
}