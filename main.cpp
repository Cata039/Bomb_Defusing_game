#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string.h>
#include <sstream>
#include <string>
#include <stdexcept>
#include <iomanip>

using namespace std;

#define MAX_LINE_LENGTH 500
#define MAX_NAME_LENGTH 500

// MenuItem class represents a menu item in the restaurant
class MenuItem {
private:
    string name;
    double price;

public:
    MenuItem(const string& n, double p)
        : name(n), price(p) {}

    // Accessors
    string getName() const { return name; }
    double getPrice() const { return price; }
};

// OrderItem class represents an item in an order
class OrderItem {
private:
    const MenuItem* menuItem;
    int quantity;

public:
    OrderItem(const MenuItem* item, int qty)
        : menuItem(item), quantity(qty) {}

    // Accessors
    const MenuItem* getMenuItem() const { return menuItem; }
    int getQuantity() const { return quantity; }
};

// Order class represents an order placed by a customer
class Order {
private:
    int tableNumber;
    double totalPrice;
    vector<OrderItem> orderItems;

public:
    Order(int tableNum)
        : tableNumber(tableNum), totalPrice(0) {}

    // Accessors
    int getTableNumber() const { return tableNumber; }
    double getTotalPrice() const { return totalPrice; }

    // Methods
    void addOrderItem(const OrderItem& item);
    void saveToFile(const string& filename) const;
};

void Order::addOrderItem(const OrderItem& item) {
    orderItems.push_back(item);
    totalPrice += item.getMenuItem()->getPrice() * item.getQuantity();
}

void Order::saveToFile(const string& filename) const {
    ofstream file(filename, ios::app);
    if (file.is_open()) {
        for (const OrderItem& item : orderItems) {
            file << tableNumber << ","
                << item.getMenuItem()->getName() << ","
                << item.getQuantity() << ","
                << item.getMenuItem()->getPrice() * item.getQuantity() << endl;
        }
        file.close();
    }
    else {
        cerr << "Unable to open file: " << filename << endl;
    }
}

// Table class represents a table in the restaurant
class Table {
private:
    int tableNumber;
    string status;

public:
    Table(int num) : tableNumber(num), status("Vacant") {}

    // Accessors
    int getTableNumber() const { return tableNumber; }
    string getStatus() const { return status; }

    // Methods
    void setStatus(const string& newStatus) { status = newStatus; }
};

// Staff class represents a staff member in the restaurant
class Staff {
private:
    string username;
    string password;

public:
    Staff(const string& uname, const string& pwd) : username(uname), password(pwd) {}

    // Accessors
    string getUsername() const { return username; }
    string getPassword() const { return password; }
};

// Function to display menu items from a file
void displayMenuItems(const string& filename) {
    ifstream file(filename);
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string name, price;
            getline(ss, name, ',');
            getline(ss, price, ',');
            cout << "Name: " << name << ", Price: " << price << endl;
        }
        file.close();
    }
    else {
        cerr << "Unable to open file: " << filename << endl;
    }
}

// Function to get the price of a product by name from a file
double getProductPrice(const string& filename, const string& product_name) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Unable to open product file " << filename << endl;
        return -1;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string name, priceStr;
        getline(ss, name, ',');
        getline(ss, priceStr, ',');

        if (name == product_name) {
            return stod(priceStr); // Convert price string to double
        }
    }

    return -1; // Return -1 if product not found
}

// Function to check if a product is available
bool isProductAvailable(const string& filename, const string& product_name) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Unable to open file " << filename << endl;
        return false;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string name;
        getline(ss, name, ',');
        if (name == product_name) {
            return true;
        }
    }

    return false;
}

// Function to place an order
void placeOrder(int tableNumber, const string& menuFile) {
    string product_name;
    int quantity;

    cout << "Enter the name of the product: ";
    cin.ignore();
    getline(cin, product_name);

    cout << "Enter the quantity: ";
    cin >> quantity;
    if (quantity < 0) {
        cout << "Error: Please enter a positive quantity." << endl;
        return;
    }

    if (isProductAvailable(menuFile, product_name)) {
        double price = getProductPrice(menuFile, product_name);
        if (price < 0) {
            cout << "Error: Could not find the product price." << endl;
            return;
        }

        // Create a MenuItem object
        MenuItem menuItem(product_name, price);

        // Create an OrderItem object
        OrderItem orderItem(&menuItem, quantity);

        // Create an Order object
        Order order(tableNumber);
        order.addOrderItem(orderItem);

        // Save the order to file
        order.saveToFile("C:/Users/jemna/CLionProjects/Restaurant_management_system/orders.txt");

        cout << "Order placed successfully!" << endl;
    }
    else {
        cout << "Order could not be placed. Product not available." << endl;
    }
}

bool checkUserExistence(const string& username, const string& password) {
    ifstream file("C:/Users/jemna/CLionProjects/Restaurant_management_system/staff.txt");
    if (!file.is_open()) {
        cerr << "Error: Unable to open staff file" << endl;
        return false;
    }

    string stored_username, stored_password;
    while (file >> stored_username >> stored_password) {
        if (stored_username == username && stored_password == password) {
            return true;
        }
    }

    return false;
}
bool checkUsernameExists(const string& username) {
    ifstream file("C:/Users/jemna/CLionProjects/Restaurant_management_system/staff.txt");
    if (!file.is_open()) {
        cerr << "Error: Unable to open staff file" << endl;
        return false;
    }

    string stored_username, stored_password;
    while (file >> stored_username >> stored_password) {
        if (stored_username == username) {
            return true;
        }
    }

    return false;
}
// o a doua functie de verificare a userului care cauta doar dupa nume
// mereu deasupra lui create!
void create() {
    string username, password;
    cout << "Enter a new username: ";
    cin >> username;

    if (checkUsernameExists(username)) {
       cout << "Error: Username already exists." << endl;
        return;
    }

    cout << "Enter a new password: ";
    cin >> password;

    ofstream file("staff.txt", ios::app);  // Open in append mode
    if (!file.is_open()) {
        cerr << "Error: Unable to open staff file" << endl;
        return;
    }

    file << username << " " << password << endl;
    file.close();

    cout << "Account created successfully!" << endl;
}//important sa fie deasupra lui log in

void menu() {
    string name, price, alergen;
    int nr;

    cout << "What would you like to add:\n 1. main course\n 2. dessert\n 3. apetizers\n 4. drinks: \n";
    cin >> nr;

    if (nr > 4 || nr < 1) {
        cout << "Error: Invalid response, try 1, 2, or 3." << endl;
        return;
    }

    ofstream file;
    if (nr == 1) {
        file.open("C:/Users/jemna/CLionProjects/Restaurant_management_system/main_course.txt", ios::app);
    }
    else if (nr == 2) {
        file.open("C:/Users/jemna/CLionProjects/Restaurant_management_system/dessert.txt", ios::app);
    }
    else if (nr == 3) {
        file.open("C:/Users/jemna/CLionProjects/Restaurant_management_system/appetisers.txt", ios::app);
    }
    else if (nr == 4) {
        file.open("C:/Users/jemna/CLionProjects/Restaurant_management_system/drinks.txt", ios::app);
    }

    if (!file.is_open()) {
        cerr << "Error: Unable to open file" << endl;
        return;
    }

    cout << "Enter the name of the food: ";
    cin.ignore();
    getline(cin, name);
    cout << "Enter price: ";
    getline(cin, price);
    cout << "Enter allergens: ";
    getline(cin, alergen);//implementeaza sa adaugi mai multi alergeni


    file << endl << name << "," << price << "," << alergen;
    file.close();

    cout << "Food added successfully!" << endl;
}

//disply items of an order per table
double displayOrderItems(const int table, const string& filename) {
    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "Unable to open file: " << filename << endl;
        return 0.0; // Return 0 if file cannot be opened
    }

    double total = 0.0; // Initialize total
    string line;
    bool tableFound = false;

    while (getline(file, line)) {
        stringstream ss(line);
        string tableNumStr, itemName, itemQuantity, itemTotalPrice;

        if (getline(ss, tableNumStr, ',') &&
            getline(ss, itemName, ',') &&
            getline(ss, itemQuantity, ',') &&
            getline(ss, itemTotalPrice, ',')) {
            try {
                double price = stod(itemTotalPrice);
                int tableNum = stoi(tableNumStr);

                if (tableNum == table) {
                    tableFound = true;
                    cout << " Item: " << itemName << ", Quantity: " << itemQuantity << ", Price: " << itemTotalPrice << endl;
                    total += price; // Add price to total
                }
            }
            catch (const invalid_argument& e) {
                cerr << "Error: Invalid table number format in file. Line skipped: " << line << endl;
            }
            catch (const out_of_range& e) {
                cerr << "Error: Table number out of range in file. Line skipped: " << line << endl;
            }
            }
    }

    if (tableFound)
        cout << " Total: " << total << endl; // Print total if orders found

    return total; // Return total
}

void displayAllOrders(const string& filename) {
    ifstream file(filename);
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string table, name, quantity, price;
            getline(ss, table, ',');
            getline(ss, name, ',');
            getline(ss, quantity, ',');
            getline(ss, price, ',');
            cout << "Table: " << table<<", Item: "<<name<<", Quantity:"<<quantity << ", Price: " << price << endl;
        }
        file.close();
    }
    else {
        cerr << "Unable to open file: " << filename << endl;
    }
}

//function to remove items from the order file for a specific table
void removeItems(const int table, const string& filename) {
    ifstream inFile(filename);
    ofstream outFile("temp.txt"); // Temporary file to write updated orders

    if (!inFile.is_open() || !outFile.is_open()) {
        cerr << "Unable to open files: " << filename << " or temp.txt" << endl;
        return;
    }

    string line;
    bool tableFound = false;

    // Copy orders to temp file, excluding orders for the specified table
    while (getline(inFile, line)) {
        stringstream ss(line);
        string tableNumStr;

        if (getline(ss, tableNumStr, ',')) {
            try {
                int tableNum = stoi(tableNumStr);

                if (tableNum != table) {
                    outFile << line << endl; // Write line to temp file
                } else {
                    tableFound = true;
                }
            } catch (const invalid_argument& e) {
                cerr << "Error: Invalid table number format in file. Line skipped: " << line << endl;
            } catch (const out_of_range& e) {
                cerr << "Error: Table number out of range in file. Line skipped: " << line << endl;
            }
        }
    }

    inFile.close();
    outFile.close();

    // Replace original file with temp file
    remove(filename.c_str());
    rename("temp.txt", filename.c_str());

    if (!tableFound) {
        cout << "No orders found for table number: " << table << endl;
    }
}

// Function to calculate bill with tip and handle payment
void calculateBill(const int table, const string& filename) {
    // Display items and total
    double total = displayOrderItems(table, filename);

    // Ask for tip percentage
    cout << "Choose tip percentage:" << endl;
    cout << "1. 5%" << endl;
    cout << "2. 10%" << endl;
    cout << "3. 15%" << endl;
    cout<<"Enter your choice: ";
    int tipChoice;
    cin >> tipChoice;

    double tipPercentage;
    switch (tipChoice) {
    case 1:
        tipPercentage = 0.05;
        break;
    case 2:
        tipPercentage = 0.10;
        break;
    case 3:
        tipPercentage = 0.15;
        break;
    default:
        cout << "Invalid tip choice. Defaulting to 0% tip." << endl;
        tipPercentage = 0.0;
        break;
    }

    // Calculate new total including tip
    double newTotal = total * (1 + tipPercentage);
    cout << "New Total (including " << tipPercentage << "% tip): " << fixed << setprecision(2) << newTotal << endl;

    // Ask if customer wants to pay
    cout << "Do you want to pay? (Y/N): ";
    char payChoice;
    cin >> payChoice;
    if (payChoice == 'Y' || payChoice == 'y') {
        // Remove items from the order file
        removeItems(table, filename);
        cout << "Payment successful." << endl;
    } else {
        cout << "Payment canceled." << endl;
    }
}

void login(const string& staffFile) {
    string username;
    string password;

    cout << "Enter your username: ";
    cin >> username;
    cout << "Enter your password: ";
    cin >> password;

    if (checkUserExistence(username, password)) {
        Staff staff(username, password);
        cout << "Welcome, " << staff.getUsername() << "!" << endl;

        int choice;
        do {
            cout << "1.Add new member to staff" << endl;
            cout << "2.Add new item to Menu" << endl;
            cout << "3.See Orders by Table" << endl;
            cout << "4.See All Orders" << endl;
            cout << "5.Exit" << endl;
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
            case 1:
                create();

                break;
            case 2:

                menu();
                break;
            case 3:
            {
                const string filen = "C:/Users/jemna/CLionProjects/Restaurant_management_system/orders.txt";
                int tableNumber;
                cout << "Enter table number: ";
                cin >> tableNumber;
                displayOrderItems(tableNumber, filen);
                break;
            }
            case 4:
                displayAllOrders("C:/Users/jemna/CLionProjects/Restaurant_management_system/orders.txt");
                break;
            case 5:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
            }
        } while (choice != 5);
    }
    else {
        cout << "User not found." << endl;
    }
}


int main() {
    int choice;
    cout << "Welcome to the Restaurant Management System!" << endl;
    cout << "1. Customer" << endl;
    cout << "2. Staff" << endl;
    cout << "Enter your choice: ";
    cin >> choice;

    if (choice == 1) {
        int tableNumber;
        cout << "Enter the table's number: ";
        cin >> tableNumber;
        cout << endl;

        do {
            cout << "1. See the Menu" << endl;
            cout << "2. See your order" << endl;
            cout << "3. Ask for the Bill" << endl;
            cout << "4. Exit" << endl;
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
                case 1: {
                    int innerChoice;
                    do {
                        cout << "Menu Categories:" << endl;
                        cout << "1. Appetizers" << endl;
                        cout << "2. Main Course" << endl;
                        cout << "3. Desserts" << endl;
                        cout << "4. Drinks" << endl;
                        cout << "5. That's all." << endl;
                        cout << "Enter your choice: ";
                        cin >> innerChoice;

                        switch (innerChoice) {
                            case 1:
                                displayMenuItems("C:/Users/jemna/CLionProjects/Restaurant_management_system/appetisers.txt");
                                cout << "Do you want to order something from Appetizers? (Y/N): ";
                                char order_choice1;
                                cin >> order_choice1;
                                if (order_choice1 == 'Y' || order_choice1 == 'y') {
                                    placeOrder(tableNumber, "C:/Users/jemna/CLionProjects/Restaurant_management_system/appetisers.txt");
                                }
                                break;
                            case 2:
                                displayMenuItems("C:/Users/jemna/CLionProjects/Restaurant_management_system/main_course.txt");
                                cout << "Do you want to order something from Main Course? (Y/N): ";
                                char order_choice2;
                                cin >> order_choice2;
                                if (order_choice2 == 'Y' || order_choice2 == 'y') {
                                    placeOrder(tableNumber, "C:/Users/jemna/CLionProjects/Restaurant_management_system/main_course.txt");
                                }
                                break;
                            case 3:
                                displayMenuItems("C:/Users/jemna/CLionProjects/Restaurant_management_system/dessert.txt");
                                cout << "Do you want to order something from Desserts? (Y/N): ";
                                char order_choice3;
                                cin >> order_choice3;
                                if (order_choice3 == 'Y' || order_choice3 == 'y') {
                                    placeOrder(tableNumber, "C:/Users/jemna/CLionProjects/Restaurant_management_system/dessert.txt");
                                }
                                break;
                            case 4:
                                displayMenuItems("C:/Users/jemna/CLionProjects/Restaurant_management_system/drinks.txt");
                                cout << "Do you want to order something from Drinks? (Y/N): ";
                                char order_choice4;
                                cin >> order_choice4;
                                if (order_choice4 == 'Y' || order_choice4 == 'y') {
                                    placeOrder(tableNumber, "C:/Users/jemna/CLionProjects/Restaurant_management_system/drinks.txt");
                                }
                                break;
                            case 5:
                                cout << "Exiting..." << endl;
                                break;
                            default:
                                cout << "Invalid choice!" << endl;
                                break;
                        }
                    } while (innerChoice != 5);
                    break;
                }
                case 2: {
                    // See the order
                    displayOrderItems(tableNumber, "C:/Users/jemna/CLionProjects/Restaurant_management_system/orders.txt");
                    cout << "1. Go back" << endl;
                    cout << "2. Exit" << endl;
                    cout << "Enter your choice: ";
                    cin >> choice;
                    if (choice == 1) {
                        // Go back to the main menu
                    } else if (choice == 2) {
                        cout << "Exiting..." << endl;
                        exit(0);
                    } else {
                        cout << "Invalid choice!" << endl;
                    }
                    break;
                }
                case 3:
                    // Call function to display items and calculate total bill
                    calculateBill(tableNumber, "C:/Users/jemna/CLionProjects/Restaurant_management_system/orders.txt");
                    removeItems(tableNumber, "C:/Users/jemna/CLionProjects/Restaurant_management_system/orders.txt");
                    break;
                case 4:
                    cout << "Exiting..." << endl;
                    exit(0);
                    break;
                default:
                    cout << "Invalid choice!" << endl;
                    break;
            }
        } while (choice != 4);

    } else if (choice == 2) {
        login("C:/Users/jemna/CLionProjects/Restaurant_management_system/staff.txt");
    }

    return 0;
}
