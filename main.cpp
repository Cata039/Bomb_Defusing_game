#include "DineTech.h"

#define MAX_LINE_LENGTH 500
#define MAX_NAME_LENGTH 500

bool isLoggedIn = false; // Track whether a staff member is logged in
const string basePath = "C:\\faculta\\PP\\game\\";

int main() {
    // Clear the daily report at the start
    std::ofstream report(basePath + "day_report.txt", std::ios::trunc);
    report.close();

    int choice;
    double dailyTotal = 0.0; // Track total sales for the day

    while (true) {
        clearScreen();
        cout << "DineTech Main Page <3" << endl;
        cout << "1. Customer" << endl;
        cout << "2. Staff" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            if (!isLoggedIn) {
                cout << "You must be logged in to access the customer section." << endl;
                continue;
            }

            int tableNumber;
            cout << "Enter the table's number: ";
            cin >> tableNumber;
            cout << endl;

            Table table(tableNumber);
            while (true) {
                clearScreen();
                cout << "1. See the Menu" << endl;
                cout << "2. See your orders" << endl;
                cout << "3. Ask for the Bill" << endl;
                cout << "4. Exit" << endl;
                cout << "Enter your choice: ";
                cin >> choice;

                switch (choice) {

                    case 1:
                        do {
                            clearScreen();
                            cout << "Menu Categories:" << endl;
                            cout << "1. Appetizers" << endl;
                            cout << "2. Main Course" << endl;
                            cout << "3. Desserts" << endl;
                            cout << "4. Drinks" << endl;
                            cout << "5. That's all." << endl;

                            cout << "Enter your choice: ";
                            cin >> choice;

                            switch (choice) {

                                case 1:
                                    clearScreen();
                                    displayMenuItems(basePath + "appetizers.txt");
                                    cout << "Do you want to order something from Appetizers? (Y/N): ";
                                    char order_choice1;
                                    cin >> order_choice1;
                                    if (order_choice1 == 'Y' || order_choice1 == 'y') {
                                        placeOrder(tableNumber, basePath + "appetizers.txt");
                                    }
                                    break;
                                case 2:
                                    clearScreen();
                                    displayMenuItems(basePath + "main_course.txt");
                                    cout << "Do you want to order something from Main Course? (Y/N): ";
                                    char order_choice2;
                                    cin >> order_choice2;
                                    if (order_choice2 == 'Y' || order_choice2 == 'y') {
                                        placeOrder(tableNumber, basePath + "main_course.txt");
                                    }
                                    break;
                                case 3:
                                    clearScreen();
                                    displayMenuItems(basePath + "dessert.txt");
                                    cout << "Do you want to order something from Desserts? (Y/N): ";
                                    char order_choice3;
                                    cin >> order_choice3;
                                    if (order_choice3 == 'Y' || order_choice3 == 'y') {
                                        placeOrder(tableNumber, basePath + "dessert.txt");
                                    }
                                    break;
                                case 4:
                                    clearScreen();
                                    displayMenuItems(basePath + "drinks.txt");
                                    cout << "Do you want to order something from Drinks? (Y/N): ";
                                    char order_choice4;
                                    cin >> order_choice4;
                                    if (order_choice4 == 'Y' || order_choice4 == 'y') {
                                        placeOrder(tableNumber, basePath + "drinks.txt");
                                    }
                                    break;
                                case 5:
                                    clearScreen();
                                    cout << "Returning to main menu..." << endl;
                                    break;
                                default:
                                    cout << "Invalid choice!" << endl;
                                    break;
                            }
                        } while (choice != 5);
                        break;

                    case 2:
                        clearScreen();
                        seeYourOrder(tableNumber, basePath + "orders.txt");
                        break;

                    case 3:
                        calculateBill(tableNumber, basePath + "orders.txt", dailyTotal); // Pass the dailyTotal variable
                        break;

                    case 4:
                        cout << "Returning to main menu..." << endl;
                        break;

                    default:
                        cout << "Invalid choice. Please try again." << endl;
                        break;
                }

                if (choice == 4) break; // Exit the customer menu loop
            }
        } else if (choice == 2) {
            cout << "Open the Shift" << endl;
            login(basePath + "staff.txt");
        } else if (choice == 3) {
            cout << "Exiting the program. Goodbye!" << endl;
            break;
        } else {
            cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}