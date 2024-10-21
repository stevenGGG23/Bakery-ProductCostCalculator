// Description: calculate the cost of various bakery products 
// using ingredient amounts and their unit prices. It will output a 
// formatted table displaying the cost of each product and determine the most expensive one. 
// Input: recipes.dat, products.dat, filename. 
// Output: Formatted cost table and  Most expensive product 
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

const int kMaxProducts = 24;
const int kMaxIngredients = 30;

// Function to calculate the price for a single product based on ingredients and unit prices
double calculateProductPrice(double ingredientAmounts[], double unitPrices[]) {
    double totalPrice = 0;
    for (int j = 0; j <= 6; ++j) {
        totalPrice += ingredientAmounts[j] * unitPrices[j]; // Calculate total price based on ingredient amounts and unit prices
    }
    return totalPrice;
}

void printTable(const std::string products[], double ingredients[][kMaxIngredients], double unitPrices[], double prices[], int productCount) {
  std::cout << "**************************************************************************\n";
  std::cout << "Product          Ing1  Ing2  Ing3  Ing4  Ing5  Ing6   Price\n";
  std::cout << "--------------------------------------------------------------------------\n";


    for (int i = 0; i <= productCount; ++i) {
        // Print the product number and name
        std::cout << std::left << std::setw(1) << (i + 1) << " "  // Product number
                  << std::setw(16) << products[i]; // Product name with adjusted width

        // Print ingredients
        for (int j = 0; j <= 5; ++j) {  // Print only the first 7 ingredients
            std::cout << std::setw(6) << static_cast<int>(ingredients[i][j]); // Show as integer
        }

        // Print total price for each product
        prices[i] = calculateProductPrice(ingredients[i], unitPrices); // Store the calculated price
        std::cout << std::left << std::setw(1) << "$ " << std::fixed << std::setprecision(2) << prices[i] << std::endl;
    }
    std::cout << "--------------------------------------------------------------------------" << std::endl;
}

bool openFile(std::ifstream &infile) {
    std::string filename;
    std::cout << "Enter the file name: ";
    std::cin >> filename;

    infile.open(filename);
    if (!infile) {
        std::cout << "File open error.\n";
        return false;
    }
    std::cout << "File Opened Successfully.\n";
    return true;
}

// Updated function to read recipes using the new reading style
void readRecipes(std::ifstream &infile, double ingredients[][kMaxIngredients], double unitPrices[], int &productCount) {
    int numIngredients, numProducts;
    infile >> numIngredients >> numProducts;

    productCount = numProducts;
    for (int i = 0; i <= numProducts; ++i) {
        for (int j = 0; j < numIngredients; ++j) { // Read ingredient amounts (rows)
            infile >> ingredients[j][i]; // Note the order: ingredients are stored in rows for each product
        }
        infile >> unitPrices[i]; // Assuming unit prices are stored here as well.
    }
}

int main() {
    double ingredients[kMaxProducts][kMaxIngredients] = {};
    double prices[kMaxProducts] = {};
    double unitPrices[kMaxIngredients] = {};
    std::string products[kMaxProducts];

    std::ifstream infile;
    if (!openFile(infile)) {
        return 1;
    }

    int productCount = 0; // Initialize productCount
    readRecipes(infile, ingredients, unitPrices, productCount);
    infile.close();

    // Open the products file and read product names
    std::ifstream productFile("products.dat");
    for (int i = 0; i <= productCount; ++i) {
        std::getline(productFile, products[i]);
    }
    productFile.close();

    printTable(products, ingredients, unitPrices, prices, productCount); // Pass prices to the printTable function

    // Find the most expensive product
    double maxPrice = prices[0];
    int maxIndex = 0;
    for (int i = 1; i <= productCount; ++i) { // Use i <= productCount to ensure all products are considered
        if (prices[i] > maxPrice) {
            maxPrice = prices[i];
            maxIndex = i;
        }
    }
    std::cout << "Product " << (maxIndex + 1) << ": " << products[maxIndex] << " is the most expensive product.\n";

    return 0;
}
