#include <iostream>
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
};

#include <iostream>
#include <vector>
#include <map>

using namespace std;

// Define your classes here...

int main() {
    // Create menu items
    MenuItem burger(1, "Burger", "Delicious beef burger with cheese and veggies", 9.99, "Main Course");
    MenuItem fries(2, "Fries", "Crispy golden fries", 3.99, "Side Dish");
    MenuItem soda(3, "Soda", "Refreshing cola drink", 1.99, "Beverage");

    // Create an order
    Order order(1, 10); // Order ID: 1, Table Number: 10

    // Display menu
    cout << "Menu:" << endl;
    cout << "1. Burger - $9.99" << endl;
    cout << "2. Fries - $3.99" << endl;
    cout << "3. Soda - $1.99" << endl;

    // Place order from keyboard input
    int choice;
    int quantity;
    char continueChoice;
    do {
        cout << "Enter item number: ";
        cin >> choice;

        cout << "Enter quantity: ";
        cin >> quantity;

        switch (choice) {
            case 1:
                order.addOrderItem(OrderItem(&burger, quantity, ""));
                break;
            case 2:
                order.addOrderItem(OrderItem(&fries, quantity, ""));
                break;
            case 3:
                order.addOrderItem(OrderItem(&soda, quantity, ""));
                break;
            default:
                cout << "Invalid choice!" << endl;
        }

        cout << "Do you want to continue? (Y/N): ";
        cin >> continueChoice;
    } while (continueChoice == 'Y' || continueChoice == 'y');

    // Display order details
    cout << "Order ID: " << order.getOrderId() << endl;
    cout << "Table Number: " << order.getTableNumber() << endl;
    cout << "Total Price: $" << order.getTotalPrice() << endl;
    cout << "Status: " << order.getStatus() << endl;

    // Display order items
    cout << "Order Items:" << endl;
    for (const OrderItem& item : order.getOrderItems()) {
        const MenuItem* menuItem = item.getMenuItem();
        cout << " - " << menuItem->getName() << " (Qty: " << item.getQuantity() << ")" << endl;
    }


    return 0;
}


