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

// Define constants and enums
enum ClothingCategories { TOPS, BOTTOMS, SHOES };
const int NUM_CATEGORIES = 3;
string categoryNames[NUM_CATEGORIES] = { "Tops", "Bottoms", "Shoes"};
const int NUM_DAYS = 25;

// Define a struct representing a single clothing piece
struct Clothing {
	string name;
	string category;	// "Tops", "Bottoms", or "Shoes"
	Clothing(string n, string c) : name(n), category(c) {}
};

// Function to generate a random number between MIN and MAX inclusive
int generateRandomNum(const int MIN, const int MAX);

// Function to add a certain number of clothes to a given category in a store
void addClothes(const int CAT_INDEX, const int NUM_CLOTHES, array<list<Clothing>, NUM_CATEGORIES>& store, const array<vector<Clothing>, NUM_CATEGORIES>& clothingPool);

// Function to read pieces of clothing from a file and store it into a vector
void populateClothingPool(array<vector<Clothing>, NUM_CATEGORIES>& clothingPool, const string FILE_NAME);

// Function to display the stock of all clothing stores
void displayStock(const map<string, array<list<Clothing>, NUM_CATEGORIES>>& clothingStores);

// Function to add new clothing to a particular store
void restockClothing(
	map<string, array<list<Clothing>, NUM_CATEGORIES>>& clothingStores,		// Arg 1 - a map of clothing stores
	const string& storeName,												// Arg 2 - the name of the clothing store to sell from
	const array<vector<Clothing>, NUM_CATEGORIES>& clothingPool				// Arg 3 - a pool of possible clothing that can be restocked
);

// sellClothing() - Function to sell clothing from a particular store
// Arguments - a map of clothing stores, the name of the particular clothing store.
// One random category (tops, bottoms, shoes) is selected and guaranteed to sell a random number of clothes
// The other categories have a chance to sell
bool sellClothing(map<string, array<list<Clothing>, NUM_CATEGORIES>>& clothingStores, const string& storeName);
// transferClothing() - Function to transfer clothing between two stores
// Arguments - a map of clothing stores, the name of the particular clothing store
// A random other store is chosen to be transferred to
// A random piece of clothing from a random category is taken from the parameter store and added to the other store
bool transferClothing(map<string, array<list<Clothing>, NUM_CATEGORIES>>& clothingStores, const string& storeName);

int main() {
	srand(time(0));
	array<vector<Clothing>, 3> clothingPool;

	// Read file into clothingPool.
	const string FILE_NAME = "clothing.txt";
	try {
		populateClothingPool(clothingPool, FILE_NAME);
	}
	catch (const runtime_error& e) {
		cout << "ERROR: " << e.what() << "\n";
		return 1;
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

		// Add tops.
		int numClothes = generateRandomNum(MIN_CLOTHES, MAX_CLOTHES);
		addClothes(TOPS, numClothes, store.second, clothingPool);

		// Add bottoms.
		numClothes = generateRandomNum(MIN_CLOTHES, MAX_CLOTHES);
		addClothes(BOTTOMS, numClothes, store.second, clothingPool);

		// Add shoes.
		numClothes = generateRandomNum(MIN_CLOTHES, MAX_CLOTHES);
		addClothes(SHOES, numClothes, store.second, clothingPool);

		cout << "\n";
	}

	// Before the time periods begin, display the initial state of each store, showing their beginning stock.
	displayStock(clothingStores);
	cout << "\n";

	// Begin a time-based simulation for clothing store changes:
	cout << "Now beginning time intervals.\n";
	// For 25 time intervals:
	for (int i = 1; i <= NUM_DAYS; ++i) {
		cout << "\n--- DAY " << i << " ---\n";
		// Iterate through each clothing store.
		for (const auto& store : clothingStores) {
			bool somethingHappened = false;

			cout << "At " << store.first << ":\n";

			int probability;

			// For a particular clothing store, these events have a chance of happening:
		
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


int generateRandomNum(const int MIN, const int MAX) {
	return MIN + (rand() % (MAX - MIN + 1));
}

void addClothes(const int CAT_INDEX, const int NUM_CLOTHES, array<list<Clothing>, NUM_CATEGORIES>& store, const array<vector<Clothing>, NUM_CATEGORIES>& clothingPool) {
	for (int i = 0; i < NUM_CLOTHES; ++i) {
		int index = generateRandomNum(0, (clothingPool[CAT_INDEX].size() - 1));
		// cout << "Adding " << categoryNames[CAT_INDEX] << ".\n";			DELETE THIS LINE. is used for debug purposes
		store[CAT_INDEX].push_back(clothingPool[CAT_INDEX].at(index));
	}
}

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

	clothingFile.close();
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

	cout << numClothes << " " << categoryNames[catIndex] << " get restocked\n";


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
	int catIndex = generateRandomNum(0, 2);

	// Return if that category is empty (can't sell anything if there's nothing).
	auto& store = clothingStores[storeName];
	if (store[catIndex].empty()) {
		return false;	// False - nothing sold
	}

	// Choose a random number of clothes to sell from category.	
	const int MIN = 1;
	const int MAX = 3;
	int randomNum = generateRandomNum(1, 3);

	// Ensure we don't sell more clothes than we have
	while (randomNum > store[catIndex].size()) {
		randomNum = generateRandomNum(1, 3);
	}

	cout << randomNum << " " << categoryNames[catIndex] << " get sold\n";

	// Sell clothes from that category.
	for (int i = 0; i < randomNum; ++i) {
		// Select a random clothing to sell
		auto it = store[catIndex].begin();
		int position = generateRandomNum(0, (store[catIndex].size() - 1));
		advance(it, position);

		// Sell that particular clothing
		store[catIndex].erase(it);
	}
	return true;	// true - something sold
}

// transferClothing() - Function to transfer clothing between two stores
// Arguments - a map of clothing stores, the name of the particular clothing store
// A random other store is chosen to be transferred to
// A random piece of clothing from a random category is taken from the parameter store and added to the other store
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
	} while (otherStoreIt->first == storeName);

	// Output action.
	if (otherStoreIt != clothingStores.end()) {
		cout << storeName << " transfers " << numClothes << " " << categoryNames[catIndex] << " to " << otherStoreIt->first << ".\n";
	}

	// Remove clothes from one store and add them to the other.
	for (int i = 0; i < numClothes; ++i) {
		// Select a random clothing to transfer
		auto it = thisStore[catIndex].begin();
		int position = generateRandomNum(0, (thisStore[catIndex].size() - 1));
		advance(it, position);

		// Save that clothing
		Clothing transferredPiece = *it;

		// Remove that particular clothing from our store
		thisStore[catIndex].erase(it);

		otherStoreIt->second[catIndex].push_back(transferredPiece);
	}

	return true;
}