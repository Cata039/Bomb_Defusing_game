#include "DineTech.h"

// Definitions for MenuItem class
MenuItem::MenuItem(const string& n, double p) : name(n), price(p) {}
string MenuItem::getName() const { return name; }
double MenuItem::getPrice() const { return price; }

// Definitions for OrderItem class
OrderItem::OrderItem(const MenuItem* item, int qty) : menuItem(item), quantity(qty) {}
const MenuItem* OrderItem::getMenuItem() const { return menuItem; }
int OrderItem::getQuantity() const { return quantity; }
string OrderItem::getProductName() const { return menuItem->getName(); }
double OrderItem::getProductPrice() const { return menuItem->getPrice(); }

// Definitions for Order class
Order::Order(int tableNum) : tableNumber(tableNum), totalPrice(0), paid(false) {}
int Order::getTableNumber() const { return tableNumber; }
double Order::getTotalPrice() const { return totalPrice; }
bool Order::isPaid() const { return paid; }
void Order::setPaid(bool isPaid) { paid = isPaid; }
string Order::toString() const {
    stringstream ss;
    ss << "Table Number: " << tableNumber << "\n";
    for (const auto& item : orderItems) {
        ss << "Product: " << item.getProductName() << ", Quantity: " << item.getQuantity()
           << ", Price: $" << item.getProductPrice() << "\n";
    }
    ss << "Paid: " << (paid ? "Yes" : "No") << "\n";
    return ss.str();
}
void Order::addOrderItem(const OrderItem& item) {
    orderItems.push_back(item);
    totalPrice += item.getMenuItem()->getPrice() * item.getQuantity();
}
const vector<OrderItem>& Order::getOrderItems() const { return orderItems; }
void Order::saveToFile(const string& filename) const {
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

// Definitions for Table class
Table::Table(int num) : tableNumber(num), status("Vacant") {}
int Table::getTableNumber() const { return tableNumber; }
string Table::getStatus() const { return status; }
void Table::setStatus(const string& newStatus) { status = newStatus; }

// Definitions for Staff class
Staff::Staff(const string& uname, const string& pwd) : username(uname), password(pwd) {}
string Staff::getUsername() const { return username; }
string Staff::getPassword() const { return password; }

// Function definitions
void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void pause() {
    cout << "Press Enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

// Function implementations
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
            return stod(priceStr);
        }
    }

    return -1;
}

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

        MenuItem menuItem(product_name, price);
        OrderItem orderItem(&menuItem, quantity);
        Order order(tableNumber);
        order.addOrderItem(orderItem);
        order.saveToFile(basePath + "orders.txt");

        cout << "Order placed successfully!" << endl;
    } else {
        cout << "Order could not be placed. Product not available." << endl;
    }
}

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

    ofstream file(basePath + "staff.txt", ios::app);
    if (!file.is_open()) {
        cerr << "Error: Unable to open staff file" << endl;
        return;
    }

    file << username << " " << password << endl;
    file.close();

    cout << "Account created successfully!" << endl;
}

void menu() {
    string name, price, alergen;
    int nr;

    cout << "What would you like to add:\n 1. main course\n 2. dessert\n 3. appetizers\n 4. drinks: \n";
    cin >> nr;

    if (nr > 4 || nr < 1) {
        cout << "Error: Invalid response, try 1, 2, or 3." << endl;
        return;
    }

    ofstream file;
    if (nr == 1) {
        file.open(basePath + "main_course.txt", ios::app);
    }
    else if (nr == 2) {
        file.open(basePath + "dessert.txt", ios::app);
    }
    else if (nr == 3) {
        file.open(basePath + "appetizers.txt", ios::app);
    }
    else if (nr == 4) {
        file.open(basePath + "drinks.txt", ios::app);
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
    getline(cin, alergen);

    file << endl << name << "," << price << "," << alergen;
    file.close();

    cout << "Food added successfully!" << endl;
}

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
    cin.ignore();
    getline(cin, itemName);

    fstream file(filename, ios::in | ios::out);

    if (!file.is_open()) {
        cerr << "Error: Unable to open file" << endl;
        return;
    }

    bool itemFound = false;
    string line;
    ofstream temp("temp.txt");

    while (getline(file, line)) {
        stringstream ss(line);
        string name;
        getline(ss, name, ',');
        name.erase(0, name.find_first_not_of(" \t\n\r\f\v"));
        name.erase(name.find_last_not_of(" \t\n\r\f\v") + 1);

        if (name == itemName) {
            itemFound = true;
        } else {
            temp << line << endl;
        }
    }

    file.close();
    temp.close();

    remove(filename.c_str());
    rename("temp.txt", filename.c_str());

    if (itemFound) {
        cout << "Item '" << itemName << "' deleted successfully from the menu." << endl;
    } else {
        cout << "Item '" << itemName << "' not found in the menu." << endl;
    }
    pause();
}

void displayOrders(int table, const string& filename) {
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
    pause();
}

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
    pause();
}

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
    pause();
}

void login(const string& staffFile) {
    string username;
    string password;

    if (!isLoggedIn) {
        clearScreen();
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
        clearScreen(); // Clear the screen before showing the menu
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
                clearScreen();
                displayOrders(tableNumber, filen);
                break;
            }
            case 5:
                clearScreen();
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
                            clearScreen();
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
    pause();
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