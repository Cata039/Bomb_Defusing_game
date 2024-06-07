#ifndef DINETECH_H
#define DINETECH_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iomanip>
#include <limits>

using namespace std;

// Forward declarations
class Order;
class MenuItem;

// Variable declarations
extern bool isLoggedIn;
extern const string basePath;

// Function declarations
void clearScreen();
void pause();
void displayMenuItems(const string& filename);
double getProductPrice(const string& filename, const string& product_name);
bool isProductAvailable(const string& filename, const string& product_name);
void placeOrder(int tableNumber, const string& menuFile);
bool checkUserExistence(const string& username, const string& password);
bool checkUsernameExists(const string& username);
void create();
void menu();
void deleteItemMenu();
void displayOrders(int table, const string& filename);
void displayAllOrders(const string& filename);
bool confirmUsernameAndPassword(const string& username, const string& password);
void seeDailyReport();
void login(const string& staffFile);
double seeYourOrder(int tableNumber, const string& filename);
std::vector<Order> readOrders(const std::string& filename);
void writeOrders(const string& filename, const vector<Order>& orders);
void removeItems(int table, const std::string& ordersFile, const std::string& reportFile, double& dailyTotal);
void calculateBill(int table, const std::string& filename, double& dailyTotal);

// Class declarations
class MenuItem {
private:
    string name;
    double price;
public:
    MenuItem(const string& n, double p);
    string getName() const;
    double getPrice() const;
};

class OrderItem {
private:
    const MenuItem* menuItem;
    int quantity;
public:
    OrderItem(const MenuItem* item, int qty);
    const MenuItem* getMenuItem() const;
    int getQuantity() const;
    string getProductName() const;
    double getProductPrice() const;
};

class Order {
private:
    int tableNumber;
    double totalPrice;
    vector<OrderItem> orderItems;
    bool paid;
public:
    Order(int tableNum);
    int getTableNumber() const;
    double getTotalPrice() const;
    bool isPaid() const;
    void setPaid(bool isPaid);
    string toString() const;
    void addOrderItem(const OrderItem& item);
    const vector<OrderItem>& getOrderItems() const;
    void saveToFile(const string& filename) const;
};

class Table {
private:
    int tableNumber;
    string status;
public:
    Table(int num);
    int getTableNumber() const;
    string getStatus() const;
    void setStatus(const string& newStatus);
};

class Staff {
private:
    string username;
    string password;
public:
    Staff(const string& uname, const string& pwd);
    string getUsername() const;
    string getPassword() const;
};

#endif // DINETECH_H