// Pseudocode comments and mockup:

// Include headers for files, data structures, etc

// Define constants for the number of simulation days and the number of stores

// displayStock() - Function to display store stock
// Arguments: a map of clothing stores
// Goes through each map element, outputs the name of the store (map key) and the clothing stores' tops, bottoms, and shoes (map value)

// restockClothing() - Function to add new clothing to a particular store
// Arguments: a map of clothing stores, the name of the particular clothing store, the three vectors for tops, bottoms, and shoes
// It has a chance of restocking a random number of tops, bottoms, and shoes
// One category is guaranteed to be restocked each time

// sellClothing() - Function to sell clothing from a particular store
// Arguments - a map of clothing stores, the name of the particular clothing store
// 

// Define main function
// Open external file 
	// If the file does not open, print an error and exit
	// Read at least 100 pieces of clothing from a file, extracting its data, and storing into three vectors (depending on if it's a top, bottom, or shoes)
	// Close the file

// Create a map of clothing stores
// For each clothing store, go through each of its categories: tops, bottoms, shoes
	// Add a random number of tops from the vector of tops
	// Add a random number of bottoms from the vector of bottoms
	// Add a random number of shoes from the vector of shoes

// Before the time periods begin, call displayStock() to display the initial state of each store, showing their beginning stock

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