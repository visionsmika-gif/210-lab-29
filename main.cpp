// Pseudocode comments and mockup:

// Include headers for files, data structures, etc

// Define constants for the number of simulation days and the number of stores

// displayStock() - Function to display store stock
// takes a map of clothing stores, goes through each map element
// outputs the name of the store (map key) and the clothing stores' tops, bottoms, and shoes (map value)

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
			// Event 1.1 - Tops get added
			// Event 1.2 - Bottoms get added
			// Event 1.3 - Shoes get added
			// Event 2 - 