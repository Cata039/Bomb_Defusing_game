#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string.h>

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
    } else {
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
    } else {
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
        order.saveToFile("C:\\faculta\\PP\\game\\orders.txt");

        cout << "Order placed successfully!" << endl;
    } else {
        cout << "Order could not be placed. Product not available." << endl;
    }
}


//int checkUserExistence(const char *name, const char *surname) {
//    FILE *file = fopen("C:\\faculta\\PP\\online_shop_2\\clients.csv", "r");
//    if (file == NULL) {
//        printf("Error: Unable to open the file.\n");
//        return 0;
//    }
//
//    char line[MAX_NAME_LENGTH + 2]; //+2 for comma and newline
//    while (fgets(line, sizeof(line), file)) {
//        char *token = strtok(line, ",");
//        if (strcmp(token, name) == 0) {
//            token = strtok(NULL, ",");
//            token[strcspn(token, "\n")] = '\0';
//            if (strcmp(token, surname) == 0) {
//                fclose(file);
//                return 1;
//            }
//        }
//    }
//
//    fclose(file);
//    return 0;
//}

bool checkUserExistence(const string& username, const string& password) {
    ifstream file("C:\\faculta\\PP\\game\\staff.txt");
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
            cout<<"1.Add new member to staff"<<endl;
            cout<<"2.Add new item to Menu"<<endl;
            cout<<"3.See Orders"<<endl;
            cout<<"4.Exit"<<endl;
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
                case 1:

                    cout << "Choice 1 selected" << endl;
                    break;
                case 2:

                    cout << "Choice 2 selected" << endl;
                    break;
                case 3:

                    cout << "Choice 3 selected" << endl;
                    break;
                case 4:
                    cout << "Exiting..." << endl;
                    break;
                default:
                    cout << "Invalid choice. Please try again." << endl;
                    break;
            }
        } while (choice != 4);
    } else {
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

        // Create a table
        Table table(tableNumber);
        cout << "1.See the Menu"<<endl;
        cout << "2.See your orders"<<endl;
        cout << "3.Ask for the Bill"<<endl;
        cout << "4.Exit"<<endl;
        cout << "Enter your choice"<<endl;
        cin >> choice;

        switch(choice){
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
                            displayMenuItems("C:\\faculta\\PP\\game\\appetizers.txt");
                            cout << "Do you want to order something from Appetizers? (Y/N): ";
                            char order_choice1;
                            cin >> order_choice1;
                            if (order_choice1 == 'Y' || order_choice1 == 'y') {
                                placeOrder(tableNumber, "C:\\faculta\\PP\\game\\appetizers.txt");
                            }
                            break;
                        case 2:
                            displayMenuItems("C:\\faculta\\PP\\game\\main_course.txt");
                            cout << "Do you want to order something from Main Course? (Y/N): ";
                            char order_choice2;
                            cin >> order_choice2;
                            if (order_choice2 == 'Y' || order_choice2 == 'y') {
                                placeOrder(tableNumber, "C:\\faculta\\PP\\game\\main_course.txt");
                            }
                            break;
                        case 3:
                            displayMenuItems("C:\\faculta\\PP\\game\\dessert.txt");
                            cout << "Do you want to order something from Desserts? (Y/N): ";
                            char order_choice3;
                            cin >> order_choice3;
                            if (order_choice3 == 'Y' || order_choice3 == 'y') {
                                placeOrder(tableNumber, "C:\\faculta\\PP\\game\\dessert.txt");
                            }
                            break;
                        case 4:
                            displayMenuItems("C:\\faculta\\PP\\game\\drinks.txt");
                            cout << "Do you want to order something from Drinks? (Y/N): ";
                            char order_choice4;
                            cin >> order_choice4;
                            if (order_choice4 == 'Y' || order_choice4 == 'y') {
                                placeOrder(tableNumber, "C:\\faculta\\PP\\game\\drinks.txt");
                            }
                            break;
                        case 5:
                            cout << "Exiting..." << endl;
                            break;
                        default:
                            cout << "Invalid choice!" << endl;
                            break;
                    }
                } while (choice != 5);
                break;

            case 2:
                cout<<"see your orders"<<endl;
                break;
            case 3:
                cout<<"the bill"<<endl;
                break;
        }


    } else if (choice == 2) {
       login("C:\\faculta\\PP\\game\\staff.txt");
    }

    return 0;
}
