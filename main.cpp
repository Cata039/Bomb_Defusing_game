#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <unordered_map>

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

//// Function to load menu items from a file
//vector<MenuItem> loadMenuFromFile(const string& filename) {
//    vector<MenuItem> menu;
//    ifstream file(filename);
//    if (file.is_open()) {
//        string line;
//        while (getline(file, line)) {
//            stringstream ss(line);
//            int id;
//            string name, desc, category;
//            double price;
//            ss >> id >> name >> price;
//            getline(ss, desc);
//            getline(ss, category);
//            menu.push_back(MenuItem(id, name, desc, price, category));
//        }
//        file.close();
//    } else {
//        cerr << "Unable to open file: " << filename << endl;
//    }
//    return menu;
//}

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
    bool staffLogin(const vector<Staff> &staffList, string username) {
        for (const Staff &staff: staffList) {
            if (staff.getUsername() == username) {
                return true; // Login successful
            }
        }
        return false; // Login failed
    }


    void displayMenuItems(const string &filename) {
        ifstream file(filename);
        if (file.is_open()) {
            string line;
            while (getline(file, line)) {
                stringstream ss(line);
                string item1, item2;
                getline(ss, item1, ',');
                getline(ss, item2, ',');
                cout << "Name: " << item1 << ", Price: " << item2 << endl;
            }
            file.close();
        } else {
            cerr << "Unable to open file: " << filename << endl;
        }
    }

// Function to find the price of a menu item by its name
double findPriceByName(const vector<MenuItem>& menu, const string& name) {
    for (const MenuItem& item : menu) {
        if (item.getName() == name) {
            return item.getPrice();
        }
    }
    return 0.0; // Return 0 if item not found
}

// Function to place an order  E O PROBLEMA CA NU IMI AFISEAZA CORECT PRETUL IN FISIER...SI NICI NU IA CUM TREBUIE STRINGUL
//IN CARE SCRIU ITEMUL PE CARE IL COMAND(nu imi ia primul caracter :/ )
void placeOrder(int tableNumber, const vector<MenuItem>& menu, unordered_map<int, int>& tableOrderCounts) {
    ofstream orderFile("C:\\faculta\\PP\\game\\orders.txt", ios::app); // Append mode
    if (orderFile.is_open()) {
        string food;
        int quantity;
        cout << "Enter the name of the food: ";
        cin.ignore(); // Ignore previous newline character
        getline(cin, food);
        cout << "Enter the quantity: ";
        cin >> quantity;


//        cout << "Food: " << food << endl; // Debug output
        double itemPrice = findPriceByName(menu, food);
//        cout << "Price per item: " << itemPrice << endl; // Debug output
        double totalPrice = itemPrice * quantity;



        // Write to file in the specified format
        int orderCount = ++tableOrderCounts[tableNumber];
        orderFile << tableNumber << "," << orderCount
                  << "," << food << "," << quantity
                  << "," << totalPrice << endl;

        orderFile.close();
        cout << "Order placed successfully!" << endl;
    } else {
        cerr << "Unable to open order file!" << endl;
    }
}

vector<MenuItem> loadMenuFromFile(const string& filename) {
    vector<MenuItem> menu;
    ifstream file(filename);
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string name, priceStr, alergens;
            double price;
            getline(ss, name, ',');
            getline(ss, priceStr, ',');
            price = stod(priceStr); // Convert price string to double
            getline(ss, alergens);
            menu.push_back(MenuItem(0, name, "", price, alergens)); // Assuming ID and description are not used in the file
        }
        file.close();
    } else {
        cerr << "Unable to open file: " << filename << endl;
    }
    return menu;
}


int main() {

        // Load menu items from files
        vector<MenuItem> appetizers = loadMenuFromFile("C:\\faculta\\PP\\game\\appetizers.txt");
        vector<MenuItem> mainCourse = loadMenuFromFile("C:\\faculta\\PP\\game\\main_course.txt");
        vector<MenuItem> desserts = loadMenuFromFile("C:\\faculta\\PP\\game\\dessert.txt");
        vector<MenuItem> drinks = loadMenuFromFile("C:\\faculta\\PP\\game\\drinks.txt");

        unordered_map<int, int> tableOrderCounts;



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
        // Create a table
        Table table(tableNumber);

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
                    displayMenuItems("C:\\faculta\\PP\\game\\appetizers.txt");
                    cout << "Do you want to order something from Appetizers? (Y/N): ";
                    char order_choice1;
                    cin >> order_choice1;
                    cin.ignore();
                    if (order_choice1 == 'Y' || order_choice1 == 'y') {
                        placeOrder(tableNumber, appetizers,tableOrderCounts);
                    }
                    break;
                case 2:
                    displayMenuItems("C:\\faculta\\PP\\game\\main_course.txt");
                    cout << "Do you want to order something from Main Course? (Y/N): ";
                    char order_choice2;
                    cin >> order_choice2;
                    cin.ignore();
                    if (order_choice2 == 'Y' || order_choice2 == 'y') {
                        placeOrder(tableNumber, mainCourse,tableOrderCounts);
                    }
                    break;
                case 3:
                    displayMenuItems("C:\\faculta\\PP\\game\\dessert.txt");
                    cout << "Do you want to order something from Desserts? (Y/N): ";
                    char order_choice3;
                    cin >> order_choice3;
                    cin.ignore();
                    if (order_choice3 == 'Y' || order_choice3 == 'y') {
                        placeOrder(tableNumber, desserts, tableOrderCounts);
                    }
                    break;
                case 4:
                    displayMenuItems("C:\\faculta\\PP\\game\\drinks.txt");
                    cout << "Do you want to order something from Drinks? (Y/N): ";
                    char order_choice4;
                    cin >> order_choice4;
                    cin.ignore();
                    if (order_choice4 == 'Y' || order_choice4 == 'y') {
                        placeOrder(tableNumber, drinks,tableOrderCounts);
                    }
                    break;
                case 5:
                    printf("Exiting...\n");
                    break;
                default:
                    cout << "Invalid choice!" << endl;
                    break;
            }
        } while (choice != 5);

    } else if (choice == 2) {
        // Staff login and functionality can be implemented here
    }

    return 0;


}
