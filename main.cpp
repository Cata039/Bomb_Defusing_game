#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

#define MAX_LINE_LENGTH 500
#define MAX_NAME_LENGTH 500

bool isLoggedIn = false; // Track whether a staff member is logged in

const string basePath = "C:/Users/jemna/CLionProjects/Restaurant_management_system/";

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
    string getProductName() const { return menuItem->getName(); }
    double getProductPrice() const { return menuItem->getPrice(); }
};

// Order class represents an order placed by a customer
class Order {
private:
    int tableNumber;
    double totalPrice;
    vector<OrderItem> orderItems;
    bool paid;

public:
    Order(int tableNum)
        : tableNumber(tableNum), totalPrice(0), paid(false) {}

    // Accessors
    int getTableNumber() const { return tableNumber; }
    double getTotalPrice() const { return totalPrice; }
    bool isPaid() const { return paid; }
    void setPaid(bool isPaid) { paid = isPaid; }

    // Methods
    string toString() const {
        stringstream ss;
        ss << "Table Number: " << tableNumber << "\n";
        for (const auto& item : orderItems) {
            ss << "Product: " << item.getProductName() << ", Quantity: " << item.getQuantity()
               << ", Price: $" << item.getProductPrice() << "\n";
        }
        ss << "Paid: " << (paid ? "Yes" : "No") << "\n";
        return ss.str();
    }

    void addOrderItem(const OrderItem& item) {
        orderItems.push_back(item);
        totalPrice += item.getMenuItem()->getPrice() * item.getQuantity();
    }

    const vector<OrderItem>& getOrderItems() const {
        return orderItems;
    }

    void saveToFile(const string& filename) const {
        ofstream file(filename, ios::app);
        if (file.is_open()) {
            for (const OrderItem& item : orderItems) {
                file << tableNumber << ","
                     << item.getMenuItem()->getName() << ","
                     << item.getQuantity() << ","
                     << item.getMenuItem()->getPrice() * item.getQuantity() << ","
                     << paid << endl;
            }
            file.close();
        } else {
            cerr << "Unable to open file: " << filename << endl;
        }
    }
};

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

//EU
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
    } else {
        cerr << "Unable to open file: " << filename << endl;
    }
}

//EU
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

//EU
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

//EU
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
        order.saveToFile(basePath + "orders.txt");

        cout << "Order placed successfully!" << endl;
    } else {
        cout << "Order could not be placed. Product not available." << endl;
    }
}

//EU
bool checkUserExistence(const string& username, const string& password) {
    ifstream file(basePath + "staff.txt");
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

//HELGA
bool checkUsernameExists(const string& username) {
    ifstream file(basePath + "staff.txt");
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

//HELGA
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

    ofstream file(basePath + "staff.txt", ios::app);  // Open in append mode
    if (!file.is_open()) {
        cerr << "Error: Unable to open staff file" << endl;
        return;
    }

    file << username << " " << password << endl;
    file.close();

    cout << "Account created successfully!" << endl;
}

//HELGA
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
        file.open(basePath +"main_course.txt", ios::app);
    }
    else if (nr == 2) {
        file.open(basePath +"dessert.txt", ios::app);
    }
    else if (nr == 3) {
        file.open(basePath +"appetizers.txt", ios::app);
    }
    else if (nr == 4) {
        file.open(basePath +"drinks.txt", ios::app);
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

//CATA
void deleteItemMenu() {
    string itemName;
    int nr;

    cout << "Which category does the item belong to:\n 1. Main course\n 2. Dessert\n 3. Appetizers\n 4. Drinks\n";
    cin >> nr;

    if (nr > 4 || nr < 1) {
        cout << "Error: Invalid response, try 1, 2, 3, or 4." << endl;
        return;
    }

    string filename;
    if (nr == 1) {
        filename = basePath + "main_course.txt";
    } else if (nr == 2) {
        filename = basePath + "dessert.txt";
    } else if (nr == 3) {
        filename = basePath + "appetizers.txt";
    } else if (nr == 4) {
        filename = basePath + "drinks.txt";
    }

    cout << "Enter the name of the item to delete: ";
    cin.ignore(); // Ignore the newline character left in the input buffer
    getline(cin, itemName);

    // Open the file for reading and writing
    fstream file(filename, ios::in | ios::out);

    if (!file.is_open()) {
        cerr << "Error: Unable to open file" << endl;
        return;
    }

    bool itemFound = false;
    string line;
    ofstream temp("temp.txt"); // Temporary file to store non-deleted items

    // Read each line from the file
    while (getline(file, line)) {
        // Split the line into name, price, and allergen
        stringstream ss(line);
        string name;
        getline(ss, name, ',');
        // Trim leading and trailing whitespaces from name
        name.erase(0, name.find_first_not_of(" \t\n\r\f\v"));
        name.erase(name.find_last_not_of(" \t\n\r\f\v") + 1);

        // If the item matches, don't write it to the temporary file
        if (name == itemName) {
            itemFound = true;
        } else {
            temp << line << endl;
        }
    }

    file.close();
    temp.close();

    // Remove the original file
    remove(filename.c_str());
    // Rename the temporary file to the original filename
    rename("temp.txt", filename.c_str());

    if (itemFound) {
        cout << "Item '" << itemName << "' deleted successfully from the menu." << endl;
    } else {
        cout << "Item '" << itemName << "' not found in the menu." << endl;
    }
}

//HELGA
void displayOrders(const int table, const string& filename) {
    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "Unable to open file: " << filename << endl;
        return;
    }
    double s = 0;
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
                    cout << "Item: " << itemName << ", Quantity: " << itemQuantity << ", Price: " << itemTotalPrice << endl;
                    s += price;
                }
            } catch (const invalid_argument& e) {
                cerr << "Error: Invalid table number format in file. Line skipped: " << line << endl;
            } catch (const out_of_range& e) {
                cerr << "Error: Table number out of range in file. Line skipped: " << line << endl;
            }
            }
    }
    if (s > 0)
        cout << "Total: " << s << endl;

    if (!tableFound) {
        cout << "No orders found for table number: " << table << endl;
    }
}


//HELGA
void displayAllOrders(const string& filename) {
    ifstream file(filename);
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string table, name, quantity, price, paid;
            getline(ss, table, ',');
            getline(ss, name, ',');
            getline(ss, quantity, ',');
            getline(ss, price, ',');
            getline(ss, paid, ',');
            cout << "Table: " << table << ", Item: " << name << ", Quantity: " << quantity << ", Price: " << price << ", Paid: " << paid << endl;
        }
        file.close();
    }
    else {
        cerr << "Unable to open file: " << filename << endl;
    }
}

//CATA
bool confirmUsernameAndPassword(const string& username, const string& password) {
    ifstream infile("tmp_shift.txt");
    string storedUsername, storedPassword;
    if (infile.is_open()) {
        infile >> storedUsername >> storedPassword;
        infile.close();
        return (username == storedUsername && password == storedPassword);
    }
    return false;
}

//CATA
void seeDailyReport() {
    const string dailyReportFile = basePath + "day_report.txt";
    ifstream report(dailyReportFile);
    if (report.is_open()) {
        string line;
        while (getline(report, line)) {
            cout << line << endl;
        }
        report.close();
    } else {
        cout << "Unable to open the daily report file." << endl;
    }
}

//EU
void login(const string& staffFile) {
    string username;
    string password;

    if (!isLoggedIn) {
        cout << "You must be logged in to access the customer section." << endl;
        cout << "Enter your username: ";
        cin >> username;
        cout << "Enter your password: ";
        cin >> password;

        if (checkUserExistence(username, password)) {
            isLoggedIn = true;
            cout << "Login successful!" << endl;
            ofstream tmpFile("tmp_shift.txt");
            if (tmpFile.is_open()) {
                tmpFile << username << " " << password << endl;
                tmpFile.close();
            }
        } else {
            cout << "User not found." << endl;
            return;
        }
    }

    Staff staff(username, password);
    cout << "Welcome, " << staff.getUsername() << "!" << endl;

    int choice;
    bool exitProgram = false;
    double dailyTotal = 0.0; // Track total sales for the day

    do {
        cout << "1. Add new member to staff" << endl;
        cout << "2. Add new item to Menu" << endl;
        cout << "3. Delete item from the Menu" << endl;
        cout << "4. See Orders by Table" << endl;
        cout << "5. See All Orders" << endl;
        cout << "6. Close the Shift" << endl;
        cout << "7. Exit" << endl;
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
                deleteItemMenu();
                break;
            case 4: {
                const string filen = basePath + "orders.txt";
                int tableNumber;
                cout << "Enter table number: ";
                cin >> tableNumber;
                displayOrders(tableNumber, filen);
                break;
            }
            case 5:
                displayAllOrders(basePath + "orders.txt");
                break;
            case 6: {
                string inputUsername, inputPassword;
                cout << "Enter username: ";
                cin >> inputUsername;
                cout << "Enter password: ";
                cin >> inputPassword;

                if (confirmUsernameAndPassword(inputUsername, inputPassword)) {
                    int nr;
                    cout << "1. See the daily report" << endl;
                    cout << "2. Exit" << endl;
                    cin >> nr;

                    switch (nr) {
                        case 1:
                            seeDailyReport();
                            // Append the final total to the day report and clear it
                            {
                                ofstream report(basePath + "day_report.txt", ios::app);
                                report << "Final total for the day: " << std::fixed << std::setprecision(2) << dailyTotal << "\n";
                                report.close();
                            }
                            // Clear the daily report file
                            {
                                ofstream report(basePath + "day_report.txt", ios::trunc);
                            }
                            isLoggedIn = false;
                            exitProgram = true; // Set flag to exit program
                            break;
                        case 2:
                            cout << "Exiting..." << endl;
                            exitProgram = true; // Set flag to exit program
                            break;
                    }
                } else {
                    cout << "Incorrect username or password. Please try again." << endl;
                }
                break;
            }
            case 7:
                cout << "Exiting..." << endl;
                exitProgram = true; // Set flag to exit program
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }
    } while (!exitProgram);
}

//EU
double seeYourOrder(int tableNumber, const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Unable to open file " << filename << endl;
        return 0.0;
    }

    string line;
    double totalPrice = 0.0;
    bool orderFound = false;

    while (getline(file, line)) {
        stringstream ss(line);
        string tableNumStr, itemName, quantityStr, priceStr;

        getline(ss, tableNumStr, ',');
        getline(ss, itemName, ',');
        getline(ss, quantityStr, ',');
        getline(ss, priceStr, ',');

        try {
            int currentTableNumber = stoi(tableNumStr);
            int quantity = stoi(quantityStr);
            double price = stod(priceStr);

            if (currentTableNumber == tableNumber) {
                orderFound = true;
                cout << "Here is what you have ordered until now:" << endl;
                cout << "Item: " << itemName << ", Quantity: " << quantity << ", Price: $" << price << endl;
                totalPrice += price;
            }
        } catch (const invalid_argument& e) {
            cerr << "Error: Invalid number format in file. Line skipped: " << line << endl;
        } catch (const out_of_range& e) {
            cerr << "Error: Number out of range in file. Line skipped: " << line << endl;
        }
    }

    if (orderFound) {
        cout << "Total Price: $" << totalPrice << endl;
    } else {
        cout << "No orders found for table number " << tableNumber << "." << endl;
    }

    file.close();
    return totalPrice;
}

std::vector<Order> readOrders(const std::string& filename) {
    std::vector<Order> orders;
    std::ifstream file(filename);
    std::string line;

    while (getline(file, line)) {
        std::stringstream ss(line);
        std::string itemName, quantityStr, priceStr, paidStr;
        int tableNumber;
        bool paid;

        if (ss >> tableNumber >> itemName >> quantityStr >> priceStr >> paidStr) {
            int quantity = std::stoi(quantityStr);
            double price = std::stod(priceStr);
            paid = (paidStr == "1" || paidStr == "true");

            Order order(tableNumber);
            order.setPaid(paid);
            order.addOrderItem(OrderItem(new MenuItem(itemName, price), quantity));
            orders.push_back(order);
        }
    }

    return orders;
}

void writeOrders(const string& filename, const vector<Order>& orders) {
    ofstream file(filename);
    for (const auto& order : orders) {
        for (const auto& item : order.getOrderItems()) {
            file << order.getTableNumber() << ","
                 << item.getMenuItem()->getName() << ","
                 << item.getQuantity() << ","
                 << item.getMenuItem()->getPrice() * item.getQuantity() << ","
                 << order.isPaid() << "\n";
        }
    }
}

void removeItems(int table, const std::string& ordersFile, const std::string& reportFile, double& dailyTotal) {
    std::ifstream inFile(ordersFile);
    std::ofstream outFile("temp_orders.txt"); // Temporary file to write updated orders
    std::ofstream report(reportFile, std::ios::app); // Append to report file

    if (!inFile.is_open() || !outFile.is_open() || !report.is_open()) {
        cerr << "Unable to open files: " << ordersFile << " or temp_orders.txt or " << reportFile << endl;
        return;
    }

    std::string line;
    bool tableFound = false;
    double tableTotal = 0.0;

    // Copy orders to temp file, excluding orders for the specified table
    while (getline(inFile, line)) {
        std::stringstream ss(line);
        std::string tableNumStr, itemName, quantityStr, priceStr;

        if (getline(ss, tableNumStr, ',') &&
            getline(ss, itemName, ',') &&
            getline(ss, quantityStr, ',') &&
            getline(ss, priceStr, ',')) {
            try {
                int tableNum = std::stoi(tableNumStr);
                int quantity = std::stoi(quantityStr);
                double price = std::stod(priceStr);

                if (tableNum == table) {
                    report << "Table " << tableNum << ": " << itemName
                           << ", Quantity: " << quantity
                           << ", Price: " << price * quantity << "\n";
                    tableTotal += price * quantity;
                    tableFound = true;
                } else {
                    outFile << line << endl; // Write line to temp file
                }
            } catch (const std::invalid_argument& e) {
                cerr << "Error: Invalid format in file. Line skipped: " << line << endl;
            } catch (const std::out_of_range& e) {
                cerr << "Error: Number out of range in file. Line skipped: " << line << endl;
            }
        }
    }

    inFile.close();
    outFile.close();
    report.close();

    // Replace original file with temp file
    std::remove(ordersFile.c_str());
    std::rename("temp_orders.txt", ordersFile.c_str());

    if (tableFound) {
        dailyTotal += tableTotal;
        std::ofstream report(reportFile, std::ios::app);
        report << "Total for table " << table << ": " << std::fixed << std::setprecision(2) << tableTotal << "\n";
        report.close();
    } else {
        cout << "No orders found for table number: " << table << endl;
    }
}


void calculateBill(const int table, const std::string& filename, double& dailyTotal) {
    double total = seeYourOrder(table, filename);

    cout << "Choose tip percentage:" << endl;
    cout << "1. 5%" << endl;
    cout << "2. 10%" << endl;
    cout << "3. 15%" << endl;
    cout << "Enter your choice: ";
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

    double newTotal = total * (1 + tipPercentage);
    cout << "New Total (including " << tipPercentage * 100 << "% tip): " << fixed << setprecision(2) << newTotal << endl;

    cout << "Do you want to pay? (Y/N): ";
    char payChoice;
    cin >> payChoice;
    if (payChoice == 'Y' || payChoice == 'y') {
        removeItems(table, filename, basePath + "day_report.txt", dailyTotal);
        cout << "Payment successful." << endl;
    } else {
        cout << "Payment canceled." << endl;
    }
}


int main() {
    // Clear the daily report at the start
    std::ofstream report(basePath + "day_report.txt", std::ios::trunc);
    report.close();

    int choice;
    double dailyTotal = 0.0; // Track total sales for the day
    cout << "Welcome to the Restaurant Management System!" << endl;

    while (true) {
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
                cout << "1. See the Menu" << endl;
                cout << "2. See your orders" << endl;
                cout << "3. Ask for the Bill" << endl;
                cout << "4. Exit" << endl;
                cout << "Enter your choice: ";
                cin >> choice;

                switch (choice) {
                case 1:
                    do {
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
                            displayMenuItems(basePath + "appetizers.txt");
                            cout << "Do you want to order something from Appetizers? (Y/N): ";
                            char order_choice1;
                            cin >> order_choice1;
                            if (order_choice1 == 'Y' || order_choice1 == 'y') {
                                placeOrder(tableNumber, basePath + "appetizers.txt");
                            }
                            break;
                        case 2:
                            displayMenuItems(basePath + "main_course.txt");
                            cout << "Do you want to order something from Main Course? (Y/N): ";
                            char order_choice2;
                            cin >> order_choice2;
                            if (order_choice2 == 'Y' || order_choice2 == 'y') {
                                placeOrder(tableNumber, basePath + "main_course.txt");
                            }
                            break;
                        case 3:
                            displayMenuItems(basePath + "dessert.txt");
                            cout << "Do you want to order something from Desserts? (Y/N): ";
                            char order_choice3;
                            cin >> order_choice3;
                            if (order_choice3 == 'Y' || order_choice3 == 'y') {
                                placeOrder(tableNumber, basePath + "dessert.txt");
                            }
                            break;
                        case 4:
                            displayMenuItems(basePath + "drinks.txt");
                            cout << "Do you want to order something from Drinks? (Y/N): ";
                            char order_choice4;
                            cin >> order_choice4;
                            if (order_choice4 == 'Y' || order_choice4 == 'y') {
                                placeOrder(tableNumber, basePath + "drinks.txt");
                            }
                            break;
                        case 5:
                            cout << "Returning to main menu..." << endl;
                            break;
                        default:
                            cout << "Invalid choice!" << endl;
                            break;
                        }
                    } while (choice != 5);
                    break;

                case 2:
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
