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
enum ClothingCategories { TOP, BOTTOMS, SHOES };


// Define a struct for a single clothing piece, containing the clothing piece's name and category (top, bottom, or shoes)
struct Clothing {
	string name;
	string category;	// "Top", "Bottoms", or "Shoes"
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
			cout << category.front().category << "\n";
			// Output all the clothing items in that category.
			for (const auto& clothingPiece : category) {
				cout << clothingPiece.name << "\n";
			}
		}
	}
}

// restockClothing() - Function to add new clothing to a particular store
// Arguments: a map of clothing stores, the name of the particular clothing store, the three vectors for tops, bottoms, and shoes.
// One random category (tops, bottoms, shoes) is selected and guaranteed to be restocked with a random number of clothes
// The other categories have a chance to be restocked

// sellClothing() - Function to sell clothing from a particular store
// Arguments - a map of clothing stores, the name of the particular clothing store.
// One random category (tops, bottoms, shoes) is selected and guaranteed to sell a random number of clothes
// The other categories have a chance to sell

// transferClothing() - Function to transfer clothing between two stores
// Arguments - a map of clothing stores, the name of the particular clothing store
// A random other store is chosen to be transferred to
// A random piece of clothing from a random category is taken from the parameter store and added to the other store

// Define main function
int main() {
	srand(time(0));

	// Open external file 
	cout << "Opening file...\n";
	vector<Clothing> topsPool, bottomsPool, shoesPool;
		// If the file does not open, print an error and exit
		// Read at least 100 pieces of clothing from a file, extracting its data, and storing into three vectors (depending on if it's a top, bottom, or shoes)
		cout << "Reading file into vectors topsPool, bottomsPool, shoesPool.\n";
		// Here are some mockup examples of clothing pieces that may be read from the file:
		topsPool.push_back(Clothing("Striped Blouse", "Top"));
		bottomsPool.push_back(Clothing("Black Slacks", "Bottoms"));
		shoesPool.push_back(Clothing("Knee-high Boots", "Shoes"));
		// Close the file
		cout << "Closing file.\n\n";

	// Create a map of clothing stores
	// The map's key is the clothing store name (string)
	// The map's value is an array of 3 lists for tops, bottoms, and shoes
	map<string, array<list<Clothing>, 3>> clothingStores;
	clothingStores["Bubbly Boutique"];

	// For each clothing store, go through each of its categories: tops, bottoms, shoes
	cout << "Initializing clothingStores with values from topsPool, bottomsPool, and shoesPool.\n";
	for (auto& store : clothingStores) {
		// Output store name
		cout << "Initializing " << store.first << ":\n";

		const int MAX = 5;
		const int MIN = 3;
		int randomNum;	// Random number between 3-5

		// Add a random number of tops from the vector of tops
		randomNum = MIN + (rand() % (MAX - MIN + 1));
		for (int i = 0; i < randomNum; ++i) {
			cout << "Adding top.\n";
			store.second[TOP].push_back(topsPool.at(0));	// In the real code, a random index for a random top in topsPool would be chosen,
															// but for simplicity in this mockup example, the index is just 0.
		}

		// Add a random number of bottoms from the vector of bottoms
		randomNum = MIN + (rand() % (MAX - MIN + 1));
		for (int i = 0; i < randomNum; ++i) {
			cout << "Adding bottom.\n";
			store.second[BOTTOMS].push_back(bottomsPool.at(0));
		}

		// Add a random number of shoes from the vector of shoes
		randomNum = MIN + (rand() % (MAX - MIN + 1));
		for (int i = 0; i < randomNum; ++i) {
			cout << "Adding bottom.\n";
			store.second[SHOES].push_back(shoesPool.at(0));
		}
		cout << "\n";
	}

	// Before the time periods begin, call displayStock() to display the initial state of each store, showing their beginning stock
	displayStock(clothingStores);

	// Begin a time-based simulation for clothing store changes:
	// For 25 time intervals:
		// Iterate through each clothing store.
			// For that particular clothing store, these events have a chance of happening:
			// Event 1 - Clothing gets restocked. (call restockClothing)
			// Event 2 - Clothing gets sold. (call sellClothing)
			// Event 3 - Clothing gets transferred between stores. (call transferClothing)
			// Whenever one of these events happen, print the change, e.g. "3 tops were added to [Clothing Store Name]".
		// Wait or pause briefly to simulate the passage of time between intervals
	// End of main function

	return 0;
}