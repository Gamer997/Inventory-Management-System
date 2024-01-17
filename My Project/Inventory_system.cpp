#include<iostream>
#include<vector>
#include<string>
#include<sstream>
#include<fstream>
#include<iomanip>

using namespace std;

struct Product
{
private:
    int id;
    string name;
    string category;
    double price;
    int quantity;

public:
    Product(int id, string name, string category, double price, int quantity)
    {
        this->id = id;
        this->name = name;
        this->category = category;
        this->price = price;
        this->quantity = quantity;
    }

    int getId() const {
        return id;
    }

    void setId(int id) {
        this->id = id;
    }

    string getName() const {
        return name;
    }

    void setName(string name) {
        this->name = name;
    }

    string getCategory() const {
        return category;
    }

    void setCategory(string category) {
        this->category = category;
    }

    double getPrice() const {
        return price;
    }

    void setPrice(double price) {
        this->price = price;
    }

    int getQuantity() const {
        return quantity;
    }

    void setQuantity(int quantity) {
        this->quantity = quantity;
    }
};



struct Inventory
{
private:
    vector<Product> products;

public:
    void addProduct(Product product)
    {
        bool found = false;
        for (auto& p : products)
        {
            if (p.getId() == product.getId())
            {
                cout << "Id already Exist." << endl;
                found = true;
                break;
            }
        }
        if (!found)
        {
            products.push_back(product);
            cout << "Product added successfully." << endl;
            cout << "-----------------------------------------------------------" << endl;
        }
    }

    void removeProduct(int id)
    {
        bool found = false;
        for (auto i = products.begin(); i != products.end(); i++)
        {
            if (i->getId() == id)
            {
                products.erase(i);
                found = true;
                cout << "Product removed successfully." << endl;
                cout << "-----------------------------------------------------------" << endl;
                break;
            }
        }
        if (!found)
        {
            cout << "Id does not exist" << endl;
        }
    }

    Product* findProduct(int id)
    {
        for (auto i = products.begin(); i != products.end(); i++)
        {
            if (i->getId() == id)
            {
                return &(*i);
            }
        }
        return nullptr;
    }

    void updateProduct(int id, string name, string category, double price, int quantity)
    {
        bool found = false;
        for (auto i = products.begin(); i != products.end(); i++)
        {
            if (i->getId() == id)
            {
                i->setName(name);
                i->setCategory(category);
                i->setPrice(price);
                i->setQuantity(quantity);
                found = true;
                break;
            }
        }
        if (!found)
        {
            cout << "ID does not exist." << endl;
        }
    }

    void printProduct() const {
        // Set the width for each column
        const int idWidth = 5;
        const int nameWidth = 20;
        const int categoryWidth = 15;
        const int priceWidth = 0;
        const int quantityWidth = 10;

        // Print table header
        cout << "\n___________________________________________________________________________\n";
        cout << left << setw(idWidth) << "ID"
            << setw(nameWidth) << "Name"
            << setw(categoryWidth) << "Category"
            << setw(priceWidth) << "Price";
           cout << "     Quantity" << endl;

        // Loop through products and print each product in a row
        for (auto i = products.begin(); i != products.end(); i++) {
            cout << left << setw(idWidth) << i->getId()
                << setw(nameWidth) << i->getName()
                << setw(categoryWidth) << i->getCategory()
                << setw(priceWidth) << "$" << fixed << setprecision(2) << i->getPrice();  // Assuming price is a double
                cout<<"     "<< setw(quantityWidth) << i->getQuantity() << endl;
        }

        cout << "\n___________________________________________________________________________\n\n";
    }



    void saveInventoryToFile(string filename)
    {
        ofstream file;
        file.open(filename, ios::out | ios::app);
        for (int i = 0; i < products.size(); i++)
        {
            Product p = products[i];
            file << p.getId() << "," << p.getName() << "," << p.getCategory() << "," << p.getPrice() << "," << p.getQuantity() << endl;
        }
        file.close();
    }

    void loadInventoryFromFile(string filename)
    {
        ifstream file;
        file.open(filename);

        if (file.is_open())
        {
            string line;
            while (getline(file, line))
            {
                stringstream ss(line);
                string idStr, name, category, priceStr, quantityStr;
                getline(ss, idStr, ',');
                getline(ss, name, ',');
                getline(ss, category, ',');
                getline(ss, priceStr, ',');
                getline(ss, quantityStr, ',');

                int id = stoi(idStr);
                double price = stod(priceStr);
                int quantity = stoi(quantityStr);

                Product p(id, name, category, price, quantity);
                products.push_back(p);
            }

            file.close();
        }
        else {
            cout << "Error: Could not open file " << filename << endl;
        }
    }
};

struct Order {
    int productId;
    string productName;
    string category;
    double price;
    int quantity;

    Order(int productId, const string& productName, const string& category, double price, int quantity)
        : productId(productId), productName(productName), category(category), price(price), quantity(quantity) {}
};


struct User {
    string name;
    string password;
    string type; // "Admin" or "User"
    vector<Order> orderHistory;
    // Constructor
    User(string name, string password, string type) : name(name), password(password), type(type) {}

    // Getter and Setter
    string getName() const {
        return name;
    }

    void setName(string name) {
        this->name = name;
    }

    string getPassword() const {
        return password;
    }

    void setPassword(string password) {
        this->password = password;
    }

    string getType() const {
        return type;
    }

    void setType(string type) {
        this->type = type;
    }
};

// Customer Structure (Inherited from User)

struct Customer : public User {
    Customer(string name, string password) : User(name, password, "User") {}
    vector<Order> orderHistory;
    
    // Customer Methods
    void placeOrder() {
        // Implementation for placing an order
    }

    void viewItemsInInventory() {
        // Implementation for viewing items in inventory
    }


    void showOrdersHistory() {
        // Implementation for showing order history
    }
};

// Administrator Structure (Inherited from User)
struct Administrator : public User {
public:
    Administrator(string name, string password) : User(name, password, "Admin") {}

    // Administrator Methods
    void manageInventory() {
        // Implementation for managing inventory
    }

    
};




void viewAllUsers(const string& filename) {
    // Implementation for viewing all users


    ifstream file(filename);

    cout << "-----------------------------------------------------------" << endl;
    cout << "------------------------ All Users ------------------------" << endl;
    cout << "-----------------------------------------------------------" << endl;

    if (file.is_open()) {
        string line;
        cout << left << setw(20) << "Username" << setw(20) << "User Type" << endl;
        cout << "-----------------------------------------------------------" << endl;

        while (getline(file, line)) {
            stringstream ss(line);
            string name, password, type;
            getline(ss, name, ',');
            getline(ss, password, ',');
            getline(ss, type, ',');

            cout << left << setw(20) << name << setw(20) << type << endl;
        }

        file.close();
    }
    else {
        cout << "Error: Could not open file " << filename << endl;
    }

    cout << "-----------------------------------------------------------" << endl;

}
User* authenticateUser(const string& username, const string& password, const vector<User>& users) {
    for (const auto& user : users) {
        if (user.getName() == username && user.getPassword() == password) {
            return new User(user);
        }
    }
    return nullptr;
}


void showOrderHistory(const User& user) {
    cout << "-----------------------------------------------------------" << endl;
    cout << "--------------- Order History for " << user.name << " ---------------" << endl;
    cout << "-----------------------------------------------------------" << endl;

    if (user.orderHistory.empty()) {
        cout << "No order history available." << endl;
    }
    else {
        cout << left << setw(5) << "ID" << setw(20) << "Product" << setw(15) << "Category" << setw(10) << "Price"
            << setw(10) << "Quantity" << endl;
        cout << "-----------------------------------------------------------" << endl;

        for (const auto& order : user.orderHistory) {
            cout << left << setw(5) << order.productId << setw(20) << order.productName << setw(15) << order.category
                << setw(10) << "$" << fixed << setprecision(2) << order.price << setw(10) << order.quantity << endl;
        }
    }

    cout << "-----------------------------------------------------------" << endl;
}

void placeOrder(Inventory& inventory_) {
    int productId, quantity;
    string category;
    inventory_ .loadInventoryFromFile("inventory.csv");
    // Display available products
    inventory_.printProduct();

    cout << "Enter the ID of the product you want to order: ";
    cin >> productId;

    // Find the product in the inventory
    Product* product = inventory_.findProduct(productId);

    if (product != nullptr) {
        cout << "Enter the quantity you want to order: ";
        cin >> quantity;

        // Check if there is enough quantity in the inventory
        if (quantity > 0 && quantity <= product->getQuantity()) {
            // Get the category of the product
            category = product->getCategory();

            // Update the quantity in the inventory
            product->setQuantity(product->getQuantity() - quantity);

            // Write the order to the CSV file
            ofstream orderFile("orders.csv", ios::out | ios::app);

            if (orderFile.is_open()) {
                orderFile << productId << "," << product->getName() << "," << category << "," << product->getPrice() << "," << quantity << endl;
                orderFile.close();
                cout << "Order placed successfully!" << endl;
            }
            else {
                cout << "Error: Could not open orders file." << endl;
            }
        }
        else {
            cout << "Invalid quantity or insufficient stock." << endl;
        }
    }
    else {
        cout << "Product not found." << endl;
    }
}






void signUpUser(vector<User>& users) {
    string username, password, type;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;
    cout << "Are you a User or an Administrator? (U/A): ";
    cin >> type;

    if (type == "U" || type == "u") {
        users.push_back(Customer(username, password));
    }
    else if (type == "A" || type == "a") {
        users.push_back(Administrator(username, password));
    }
    else {
        cout << "Invalid user type. Signup failed." << endl;
    }
}

// Function to load user data from file
void loadUserData(vector<User>& users, const string& filename) {
    ifstream file(filename);

    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string name, password, type;
            getline(ss, name, ',');
            getline(ss, password, ',');
            getline(ss, type, ',');

            if (type == "User") {
                users.push_back(Customer(name, password));
            }
            else if (type == "Admin") {
                users.push_back(Administrator(name, password));
            }
            else {
                cout << "Invalid user type in file. Skipping user." << endl;
            }
        }

        file.close();
    }
    else {
        cout << "Error: Could not open file " << filename << endl;
    }
}

// Function to save user data to file
void saveUserData(const vector<User>& users, const string& filename) {
    ofstream file(filename, ios::out | ios::trunc);

    if (file.is_open()) {
        for (const auto& user : users) {
            file << user.getName() << "," << user.getPassword() << "," << user.getType() << endl;
        }

        file.close();
    }
    else {
        cout << "Error: Could not open file " << filename << endl;
    }
}


void manageInventory(Inventory& inventory) {
    char choice;
    do {
        cout << "Please choose an option:" << endl;
        cout << "1. Add a product" << endl;
        cout << "2. Remove a product" << endl;
        cout << "3. Find a product" << endl;
        cout << "4. Update a product" << endl;
        cout << "5. View all products" << endl;
        cout << "6. Save inventory to file" << endl;
        cout << "7. Load Inventory from file" << endl;
        cout << "Q. Quit" << endl;
        cin >> choice;

        switch (choice) {
        case '1': {
            int id;
            string name, category;
            double price;
            int quantity;
            cout << "Enter ID: ";
            cin >> id;
            cout << "Enter product name: ";
            cin >> name;
            cout << "Enter product category: ";
            cin >> category;
            cout << "Enter product price: $ ";
            cin >> price;
            cout << "Enter product quantity: ";
            cin >> quantity;
            Product product(id, name, category, price, quantity);
            inventory.addProduct(product);
            break;
        }

        case '2': {
            int id;
            cout << "Enter product id: ";
            cin >> id;
            inventory.removeProduct(id);
            break;
        }

        case '3': {
            int id;
            cout << "Enter product id: ";
            cin >> id;
            Product* product = inventory.findProduct(id);
            if (product) {
                cout << "Name: " << product->getName() << endl;
                cout << "Category: " << product->getCategory() << endl;
                cout << "Price: $ " << product->getPrice() << endl;
                cout << "Quantity: " << product->getQuantity() << endl;
                cout << "-----------------------------------------------------------" << endl;
            }
            else {
                cout << "Product not found." << endl;
                cout << "-----------------------------------------------------------" << endl;
            }
            break;
        }

        case '4': {
            int id;
            string name, category;
            double price;
            int quantity;
            cout << "Enter the product id: ";
            cin >> id;
            cout << "Enter new product name: ";
            cin >> name;
            cout << "Enter new product category: ";
            cin >> category;
            cout << "Enter new product price: $ ";
            cin >> price;
            cout << "Enter new product quantity: ";
            cin >> quantity;
            inventory.updateProduct(id, name, category, price, quantity);
            cout << "Product updated successfully." << endl;
            cout << "-----------------------------------------------------------" << endl;
            break;
        }

        case '5': {
            inventory.printProduct();
            break;
        }
        case '6': {
            inventory.saveInventoryToFile("inventory.csv");
            cout << "Inventory saved to file." << endl;
            cout << "-----------------------------------------------------------" << endl;
            break;
        }
        case '7': {
            inventory.loadInventoryFromFile("inventory.csv");
            cout << "Inventory loaded from file." << endl;
            cout << "-----------------------------------------------------------" << endl;
            break;
        }
        case 'q':
        case 'Q':

            cout << "Exiting inventory management." << endl;
            cout << "-----------------------------------------------------------" << endl;
            return;

        default:
            cout << "Invalid Choice. Please Try again" << endl;
            cout << "-----------------------------------------------------------" << endl;
            break;
        }
    } while (true);
}


int main() {
    vector<User> users;
    const string userFilename = "users.txt";

    // Load user data from file
    loadUserData(users, userFilename);

    
    cout << ".--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--.." << endl;
    cout << "/ .. \\\\.. \\\\.. \\\\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\";
    cout << "\\ \\/\\\\ `'\\\\ `'\\\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ \\/ /" << endl;
    cout << " \\/ /`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'\\/ / " << endl;
    cout << " / /\\                                                                            / /\\ " << endl;
    cout << "/ /\\ \\  __ __  __ __ __  ____ __  __ ______   ___   ____  _  _                  / /\\ \\" << endl;
    cout << "\\ \\/ /  || ||\\ || || || ||    ||\\ || | || |  // \\\\  || \\\\ \\\\//                  \\ \\/ /" << endl;
    cout << " \\/ /   || ||\\\\|| \\\\ // ||==  ||\\\\||   ||   ((   )) ||_//  )/                    \\/ / " << endl;
    cout << " / /\\   || || \\||  \\V/  ||___ || \\||   ||    \\\\_/  || \\\\ \\\\ //                     / /\\ " << endl;
    cout << "/ /\\ \\                                                                          / /\\ \\" << endl;
    cout << "\\ \\/ /  ___  ___  ___  __  __  ___    ___   ____ ___  ___  ____ __  __ ______   \\ \\/ /" << endl;
    cout << " \\/ /   ||||\\ || || || ||    ||\\ || | || |  // \\\\  || \\\\ \\\\//                  \\/ / " << endl;
    cout << " / /\\   ||| \\/ || || || ||==  || \\\\|   ||   ((   )) || || )/                    / /\\ " << endl;
    cout << "/ /\\ \\  ||    || || || || \\|| || ||    ||    \\\\_/  || || \\\\                     / /\\ \\" << endl;
    cout << "\\ \\/ /                                                                          \\ \\/ /" << endl;
    cout << " \\/ /    __  _  _  __  ______  ____ ___  ___                                     \\/ / " << endl;
    cout << " / /\\   (( \\ \\\\// (( \\ | || | ||    ||\\\\//||                                     / /\\ " << endl;
    cout << "/ /\\ \\   \\\\   )/   \\\\    ||   ||==  || \\/ ||                                    / /\\ \\" << endl;
    cout << "\\ \\/ /   \\_)) //   \\_))   ||   ||___ ||    ||                                    \\ \\/ /" << endl;
    cout << " \\/ /                                                                            \\/ / " << endl;
    cout << " / /\\.--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--. / /\\ " << endl;
    cout << "/ /\\ \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\/ /" << endl;
    cout << "\\ `\\'`\\ `\\'`\\ `\\'`\\ `\\'`\\ `\\'`\\ `\\'`\\ `\\'`\\ `\\'`\\ `\\'`\\ `\\'`\\ `\\'`\\ `\\'`\\ `\\'`\\ `' /" << endl;
    cout << " `--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'";



    char choice;
    do {
        cout << "Please choose an option:" << endl;
        cout << "1. Login" << endl;
        cout << "2. Signup" << endl;
        cout << "Q. Quit" << endl;
        cin >> choice;

        switch (choice) {
        case '1': {
            string username, password;
            cout << "Enter username: ";
            cin >> username;
            cout << "Enter password: ";
            cin >> password;

            // Authenticate user
            User* currentUser = authenticateUser(username, password, users);
            Inventory inv_1;
            if (currentUser != nullptr) {
                // User authenticated, display menu based on user type
                while (choice != 'Q' && choice != 'q')
                {
                    cout << "Please choose an option:" << endl;
                    if (currentUser->getType() == "Admin") {
                        cout << "***********************" << endl;
                        cout << "\n[1] Manage Inventory" << endl;
                        cout << "[2] View All Users" << endl;
                        cout << "[Q] Exit to login Page" << endl;
                        cout << "**************************" << endl<<endl;
                        string choice_;
                        cin.ignore();
                        getline(cin,choice_);
                        

                        if (choice_ == "1") {
                            manageInventory(inv_1);
                        }
                        if(choice_ == "2") {
                            viewAllUsers("users.txt");
                        }
                        if (choice_ == "Q"){
                            choice = 'Q';
                            
                        }
                        else {
                            cout << "Invalid choice\n";
                        }
                        
                    }
                    else {
                        cout << "1. Place Order" << endl;
                        cout << "2. View Items in Inventory" << endl;
                        cout << "3. Show Orders History" << endl;
                        cout << "Q. Logout" << endl;

                        cin >> choice;
                        Inventory v1;

                        switch (choice) {
                            // Handle menu options based on user type
                        case '1':
                            cout << "case 3" << endl;
                            placeOrder(v1);

                            break;
                        case '2':
                            v1.loadInventoryFromFile("inventory.csv");
                            v1.printProduct();
                            break;
                        case '3':
                            cout << "Order History" << endl;
                            showOrderHistory(*currentUser);
                            break;
                        default:
                            cout << "Invalid input\n";
                            break;
                        }



                    }
                    
                    


                } 
                /*while (choice != 'Q' && choice != 'q');*/

                // Deallocate memory for the current user object
                delete currentUser;
            }
            else {
                cout << "Invalid username or password. Login failed." << endl;
            }
            break;
        }

        case '2': {
            signUpUser(users);
            // Save user data to file after signing up
            saveUserData(users, userFilename);
            cout << "Signup successful. You can now login." << endl;
            break;
        }

        case 'q':
        case 'Q':
            cout << "Goodbye!" << endl;
            return 0;

        default:
            cout << "Invalid Choice. Please Try again" << endl;
            break;
        }

    } while (true);

    return 0;

}