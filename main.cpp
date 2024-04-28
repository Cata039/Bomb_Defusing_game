#include <iostream>
#include <vector>
#include <string>
#include <cstdlib> // For system() function

// Function to clear the screen
void clearScreen() {
    std::system("cls || clear");
}

// Function to display the welcome message centered on the terminal
void displayWelcomeMessage() {
    clearScreen();
    std::string welcomeMessage = "Welcome to the Bomb Defusing Game!";

    // Display the welcome message with a line above and below
    std::cout << "--------------------------------------------------" << std::endl;
    std::cout << welcomeMessage << std::endl;
    std::cout << "--------------------------------------------------" << std::endl;
}

// Function to display the menu centered on the terminal
void displayMenu(const std::vector<std::string>& options) {
    clearScreen();
    std::cout << "Menu:\n" << std::endl;

    // Display each option
    int index = 1;
    for (const auto& option : options) {
        std::cout << index << ") " << option << std::endl;
        ++index;
    }
}

// Function to handle level selection
void selectLevel() {
    clearScreen();
    std::vector<std::string> levels = {"Level 1", "Level 2", "Level 3"};

    std::cout << "Select a level:\n" << std::endl;
    for (int i = 0; i < levels.size(); ++i) {
        std::cout << i + 1 << ") " << levels[i] << std::endl;
    }
    std::cout << levels.size() + 1 << ") Back to menu" << std::endl;

    int choice;
    std::cout << "\nEnter your choice: ";
    std::cin >> choice;

    // Validate the choice
    if (choice >= 1 && choice <= levels.size()) {
        std::cout << "You selected: " << levels[choice - 1] << " level" << std::endl;
        std::cout << "Press any key to go back to the menu...";
        std::cin.ignore(); // Ignore newline character
        std::cin.get();    // Wait for user input to go back to the menu
    } else if (choice == levels.size() + 1) {
        // Go back to the menu
    } else {
        std::cout << "Invalid choice!" << std::endl;
    }
}

int main() {
    // Display the welcome message
    displayWelcomeMessage();

    char choice;
    do {
        // Define menu options
        std::vector<std::string> menuOptions = {
            "Controls",
            "Select Level",
            "Hall of Fame",
            "Exit"
        };

        // Display the menu
        displayMenu(menuOptions);

        // Get user choice
        std::cout << "\nEnter your choice: ";
        std::cin >> choice;

        // Handle user choice
        if (choice == '1') {
            // Display controls
            clearScreen();
            std::cout << "Controls:\n\nW - Move up\nA - Move left\nS - Move down\nD - Move right\n";
            std::cout << "\nPress any key to go back to the menu...";
            std::cin.ignore(); // Ignore newline character
            std::cin.get();    // Wait for user input to go back to the menu
        } else if (choice == '2') {
            selectLevel();
        } else if (choice == '3') {
            // Display Hall of Fame
            clearScreen();
            std::cout << "Hall of Fame:\n\nComing soon...\n";
            std::cout << "\nPress any key to go back to the menu...";
            std::cin.ignore(); // Ignore newline character
            std::cin.get();    // Wait for user input to go back to the menu
        } else if (choice == '4') {
            std::cout << "Exiting the game...\n";
        } else {
            std::cout << "Invalid choice!\n";
        }
    } while (choice != '4');

    return 0;
}
