#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>

using namespace std;

// MenuItem class represents a menu item in the restaurant
class MenuItem {
private:
    int itemId;
    string name;
    string description;
    double price;
    string category;

public:
    MenuItem(int id, string n, string desc, double p, string cat)
            : itemId(id), name(n), description(desc), price(p), category(cat) {}

    // Accessors
    int getItemId() const { return itemId; }
    string getName() const { return name; }
    string getDescription() const { return description; }
    double getPrice() const { return price; }
    string getCategory() const { return category; }
};

// OrderItem class represents an item in an order
class OrderItem {
private:
    const MenuItem* menuItem;
    int quantity;
    string notes;

public:
    OrderItem(const MenuItem* item, int qty, string nt)
            : menuItem(item), quantity(qty), notes(nt) {}

    // Accessors
    const MenuItem* getMenuItem() const { return menuItem; }
    int getQuantity() const { return quantity; }
    string getNotes() const { return notes; }
};

// Order class represents an order placed by a customer
class Order {
private:
    int orderId;
    int tableNumber;
    vector<OrderItem> orderItems;
    double totalPrice;
    string status;

public:
    Order(int id, int tableNum)
            : orderId(id), tableNumber(tableNum), totalPrice(0), status("Pending") {}

    // Accessors
    int getOrderId() const { return orderId; }
    int getTableNumber() const { return tableNumber; }
    double getTotalPrice() const { return totalPrice; }
    string getStatus() const { return status; }

    // Methods
    void addOrderItem(const OrderItem& item) {
        orderItems.push_back(item);
        totalPrice += item.getMenuItem()->getPrice() * item.getQuantity();
    }

    // Method to retrieve order items
    const vector<OrderItem>& getOrderItems() const {
        return orderItems;
    }
};


// Table class represents a table in the restaurant
class Table {
private:
    int tableNumber;
    string status;
    vector<Order> orders;

public:
    Table(int num) : tableNumber(num), status("Vacant") {}

    // Accessors
    int getTableNumber() const { return tableNumber; }
    string getStatus() const { return status; }

    // Methods
    void setStatus(string newStatus) { status = newStatus; }
    void addOrder(const Order& order) { orders.push_back(order); }
    // Add more methods as needed
};

// Function to load menu items from a file
vector<MenuItem> loadMenuFromFile(const string& filename) {
    vector<MenuItem> menu;
    ifstream file(filename);
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            int id;
            string name, desc, category;
            double price;
            ss >> id >> name >> price;
            getline(ss, desc);
            getline(ss, category);
            menu.push_back(MenuItem(id, name, desc, price, category));
        }
        file.close();
    } else {
        cerr << "Unable to open file: " << filename << endl;
    }
    return menu;
}

// Customer class represents a customer in the restaurant
class Customer {
private:
    int customerId;
    string name;
    string contactInfo;

public:
    Customer(int id, string n, string contact)
            : customerId(id), name(n), contactInfo(contact) {}

    // Accessors
    int getCustomerId() const { return customerId; }
    string getName() const { return name; }
    string getContactInfo() const { return contactInfo; }

    // Method to place order
    void placeOrder(const vector<MenuItem>& menu, Table& table) {
        // Display categorized menu
        map<string, vector<MenuItem>> categorizedMenu;
        for (const MenuItem& item : menu) {
            categorizedMenu[item.getCategory()].push_back(item);
        }

        cout << "Menu:" << endl;
        int categoryIndex = 1;
        for (const auto& category : categorizedMenu) {
            cout << categoryIndex++ << ". " << category.first << endl;
        }

        int choice;
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice < 1 || choice > categorizedMenu.size()) {
            cout << "Invalid choice!" << endl;
            return;
        }

        // Get the selected category
        auto it = categorizedMenu.begin();
        advance(it, choice - 1);
        string selectedCategory = it->first;

        // Display items in selected category
        cout << selectedCategory << " Items:" << endl;
        const vector<MenuItem>& selectedCategoryMenu = categorizedMenu[selectedCategory];
        for (const MenuItem& item : selectedCategoryMenu) {
            cout << item.getItemId() << ". " << item.getName() << " - $" << item.getPrice() << endl;
        }

        // Create an order
        Order order(table.getTableNumber(), table.getTableNumber()); // Order ID same as table number

        // Place order from keyboard input
        char continueChoice;
        do {
            cout << "Enter item number: ";
            cin >> choice;

            if (choice < 1 || choice > selectedCategoryMenu.size()) {
                cout << "Invalid item choice!" << endl;
                continue;
            }

            const MenuItem& selectedItem = selectedCategoryMenu[choice - 1];
            int quantity;
            cout << "Enter quantity: ";
            cin >> quantity;
            order.addOrderItem(OrderItem(&selectedItem, quantity, ""));

            cout << "Do you want to continue? (Y/N): ";
            cin >> continueChoice;
        } while (continueChoice == 'Y' || continueChoice == 'y');

        // Add the order to the table
        table.addOrder(order);

        // Display order details
        cout << "Order placed successfully!" << endl;
    }
};

// Staff class represents a staff member in the restaurant
class Staff {
private:
    string username;
    string password;

public:
    Staff(string uname, string pwd) : username(uname), password(pwd) {}

    // Accessors
    string getUsername() const { return username; }
    string getPassword() const { return password; }
};

// Function to perform staff login
bool staffLogin(const vector<Staff>& staffList, string username, string password) {
    for (const Staff& staff : staffList) {
        if (staff.getUsername() == username && staff.getPassword() == password) {
            return true; // Login successful
        }
    }
    return false; // Login failed
}

int main() {
    // Load menu items from files
    vector<MenuItem> appetizers = loadMenuFromFile("C:/Users/jemna/CLionProjects/Restaurant_management_system/appetizers.txt");
    vector<MenuItem> mainCourse = loadMenuFromFile("C:/Users/jemna/CLionProjects/Restaurant_management_system/main_course.txt");
    vector<MenuItem> desserts = loadMenuFromFile("C:/Users/jemna/CLionProjects/Restaurant_management_system/desserts.txt");
    vector<MenuItem> drinks = loadMenuFromFile("C:/Users/jemna/CLionProjects/Restaurant_management_system/drinks.txt");

    // Create a table
    Table table(1); // Assuming table number is 1

    int choice;
    cout << "Welcome to the Restaurant Management System!" << endl;
    cout << "1. Customer" << endl;
    cout << "2. Staff" << endl;
    cout << "Enter your choice: ";
    cin >> choice;

    if (choice == 1) {
        // Customer functionality
        Customer customer(1, "John Doe", "123-456-7890");

        cout << "Menu Categories:" << endl;
        cout << "1. Appetizers" << endl;
        cout << "2. Main Course" << endl;
        cout << "3. Desserts" << endl;
        cout << "4. Drinks" << endl;

        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                customer.placeOrder(appetizers, table);
                break;
            case 2:
                customer.placeOrder(mainCourse, table);
                break;
            case 3:
                customer.placeOrder(desserts, table);
                break;
            case 4:
                customer.placeOrder(drinks, table);
                break;
            default:
                cout << "Invalid choice!" << endl;
                break;
        }
    }


    return 0;
}

