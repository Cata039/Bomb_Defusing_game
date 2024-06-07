# Restaurant Management System

## Overview
The Restaurant Management System is designed to manage restaurant operations efficiently. It supports functionalities for both staff and customers, including handling menu items, orders, and billing. This README provides step-by-step instructions on how to use the system and an explanation of how it works.

## System Requirements
- A C++ compiler
- Access to the specified file path for data storage

## Running the System

1. Clone the repository to your local machine:
    ```sh
    git clone <repository-url>
    ```

2. Navigate to the project directory:
    ```sh
    cd Restaurant_management_system
    ```

3. Compile the program using a C++ compiler:
    ```sh
    g++ -o restaurant_management_system main.cpp
    ```

4. Run the compiled executable:
    ```sh
    ./restaurant_management_system
    ```

## Main Menu
Upon starting the system, you will be presented with the main menu:
```plaintext
Welcome to the Restaurant Management System!
1. Customer
2. Staff
3. Exit
Enter your choice:
```

### Custumer Section:
To access the customer section, staff must be logged in.
- Enter the table number:
```plaintext
Enter the table's number:
```
- Customer Menu:
```plaintext
1. See the Menu
2. See your orders
3. Ask for the Bill
4. Exit
Enter your choice:
```

1. See the Menu
You will be prompted to choose a menu category:
```plaintext
Menu Categories:
1. Appetizers
2. Main Course
3. Desserts
4. Drinks
5. That's all.
Enter your choice:
```
After displaying the items, you can choose to order from the displayed category:
```plaintext
Do you want to order something from <Category>? (Y/N):
```

2. See Your Orders
Displays the current orders for the table along with the total price:
```plaintext
Item: <Name>, Quantity: <Quantity>, Price: $<Price>
Total Price: $<Total>
```

3. Ask for the Bill
Calculates the bill including tips and allows for payment:
```plaintext
Choose tip percentage:
1. 5%
2. 10%
3. 15%
Enter your choice:

New Total (including <Tip>% tip): $<Total>

Do you want to pay? (Y/N):
```

4. Exit
Returns to the main menu.

### Staff Section:
To access the staff section, you need to log in:
- Login Prompt:
```plaintext
Enter your username:
Enter your password:
```
- Staff Menu:
```plaintext
1. Add new member to staff
2. Add new item to Menu
3. Delete item from the Menu
4. See Orders by Table
5. See All Orders
6. Close the Shift
7. Exit
Enter your choice:
```
1. Add New Member to Staff
Prompts for a new username and password to create a staff account:
```plaintext
Enter a new username:
Enter a new password:
Account created successfully!
```
2. Add New Item to Menu
Prompts to choose a category and add a new item with price:
```plaintext
What would you like to add:
1. main course
2. dessert
3. appetizers
4. drinks:

Enter the name of the food:
Enter price:
Enter allergens:
Food added successfully!
```
3. Delete Item from the Menu
Prompts to choose a category and delete an item by name:
```plaintext
Which category does the item belong to:
1. Main course
2. Dessert
3. Appetizers
4. Drinks

Enter the name of the item to delete:
Item '<Name>' deleted successfully from the menu.
```
4. See Orders by Table
Displays orders for a specific table:
```plaintext
Enter table number:
Item: <Name>, Quantity: <Quantity>, Price: $<Price>
Total: $<Total>
```
5. See All Orders
Displays all orders from all tables:
```plaintext
Table: <Number>, Item: <Name>, Quantity: <Quantity>, Price: $<Price>, Paid: <Yes/No>
```
6. Close the Shift
Allows staff to see the daily report and close the shift:
```plaintext
Enter username:
Enter password:

1. See the daily report
2. Exit
```plaintext
Enter username:
Enter password:

1. See the daily report
2. Exit
```
7. Exit
Logs out the staff and returns to the main menu.

### Exit the Program
Choose the exit option to close the program:
```plaintext
Exiting the program. Goodbye!
```

## How It Works

### **File Structure**

**Menu Files**: Store menu items for different categories.
- **appetizers.txt**
- **main_course.txt**
- **dessert.txt**
- **drinks.txt**
  
**Order Files**: Store customer orders and daily reports.
- **orders.txt**
- **day_report.txt**

**Staff File**: Store staff usernames and passwords.
- **staff.txt**
  
### **Class Descriptions**

- MenuItem: Represents a menu item with a name and price.
- OrderItem: Represents an item in an order with a reference to a MenuItem and quantity.
- Order: Represents an order placed by a customer with a table number, list of OrderItems, total price, and payment status.
- Table: Represents a table in the restaurant with a table number and status.
- Staff: Represents a staff member with a username and password.
  
### **Key Functionalities**

- **Login**: Validates staff login credentials.
- **Add New Member to Staff**: Adds a new staff member by appending to staff.txt.
- **Add New Item to Menu**: Adds a new item to the selected menu file (appetizers.txt, main_course.txt, etc.).
- **Delete Item from the Menu**: Deletes an item from the selected menu file by copying non-matching lines to a temporary file and replacing the original file.
- **See Orders by Table**: Reads and displays orders for a specific table from orders.txt.
- **See All Orders**: Reads and displays all orders from orders.txt.
- **Close the Shift**: Displays the daily report and clears the daily report file.
- **See the Menu**: Displays items from the selected menu file.
- **Place Order**: Adds an order to orders.txt.
- **See Your Orders**: Displays current orders for the table.
- **Ask for the Bill**: Calculates the total bill with tip and processes payment by removing the table's orders from orders.txt and appending to day_report.txt.

**Temporary Files**

Temporary files are created during operations that involve removing or modifying data in existing files, such as deleting menu items or processing payment for orders.

- **temp.txt**: Used when deleting an item from a menu. It stores lines that do not match the item to be deleted and then replaces the original file.
- **temp_orders.txt**: Used when removing items from orders. It stores orders that do not belong to the specified table and then replaces orders.txt.

## Notes
Ensure the files are correctly placed in the specified basePath directory.
The system maintains daily reports which are cleared at the start of each day.
This completes the user manual for the Restaurant Management System. Follow these instructions to manage restaurant operations effectively.

