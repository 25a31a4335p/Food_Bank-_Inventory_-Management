#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include <ctime>
#include <limits>

using namespace std;

struct FoodItem {
    int id;
    string name;
    int quantity;
    string donor;
    string expiryDate;
};

time_t stringToDate(const string& date) {
    tm tmDate = {};

    stringstream ss(date);
    ss >> get_time(&tmDate, "%Y-%m-%d");

    if (ss.fail()) {
        return -1;
    }

    tmDate.tm_hour = 0;
    tmDate.tm_min = 0;
    tmDate.tm_sec = 0;

    return mktime(&tmDate);
}

int daysBetween(time_t start, time_t end) {
    double seconds = difftime(end, start);
    return static_cast<int>(seconds / (60 * 60 * 24));
}

struct CompareExpiry {
    bool operator()(const FoodItem& a, const FoodItem& b) {
        return stringToDate(a.expiryDate) > stringToDate(b.expiryDate);
    }
};

class InventoryManager {
private:
    vector<FoodItem> inventory;

    priority_queue<FoodItem,
                   vector<FoodItem>,
                   CompareExpiry> expiryQueue;

    int nextId = 1;

    void rebuildPriorityQueue() {
        while (!expiryQueue.empty()) {
            expiryQueue.pop();
        }

        for (const FoodItem& item : inventory) {
            expiryQueue.push(item);
        }
    }

public:

    // Add Item
    void addItem() {
        FoodItem item;
        item.id = nextId++;

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Enter item name: ";
        getline(cin, item.name);

        cout << "Enter quantity: ";
        cin >> item.quantity;

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Enter donor name: ";
        getline(cin, item.donor);

        cout << "Enter expiry date (YYYY-MM-DD): ";
        getline(cin, item.expiryDate);

        if (stringToDate(item.expiryDate) == -1) {
            cout << "Invalid date format. Item not added.\n";
            return;
        }

        inventory.push_back(item);
        expiryQueue.push(item);

        cout << "Item added successfully!\n";
    }

    // View Inventory
    void viewInventory() const {
        if (inventory.empty()) {
            cout << "Inventory is empty.\n";
            return;
        }

        cout << "\n========== Current Inventory ==========\n";

        cout << left
             << setw(5)  << "ID"
             << setw(20) << "Name"
             << setw(10) << "Qty"
             << setw(20) << "Donor"
             << setw(15) << "Expiry Date"
             << endl;

        cout << string(70, '-') << endl;

        for (const FoodItem& item : inventory) {
            cout << left
                 << setw(5)  << item.id
                 << setw(20) << item.name
                 << setw(10) << item.quantity
                 << setw(20) << item.donor
                 << setw(15) << item.expiryDate
                 << endl;
        }
    }

    // Search Item
    void searchItem() const {

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        string searchName;

        cout << "Enter item name to search: ";
        getline(cin, searchName);

        bool found = false;

        for (const FoodItem& item : inventory) {

            if (item.name == searchName) {

                cout << "\nItem Found:\n";

                cout << "ID: " << item.id << endl;
                cout << "Name: " << item.name << endl;
                cout << "Quantity: " << item.quantity << endl;
                cout << "Donor: " << item.donor << endl;
                cout << "Expiry Date: " << item.expiryDate << endl;

                found = true;
            }
        }

        if (!found) {
            cout << "Item not found.\n";
        }
    }

    // Update Quantity
    void updateQuantity() {
        int id;

        cout << "Enter item ID to update quantity: ";
        cin >> id;

        for (FoodItem& item : inventory) {

            if (item.id == id) {

                cout << "Enter new quantity: ";
                cin >> item.quantity;

                rebuildPriorityQueue();

                cout << "Quantity updated successfully!\n";
                return;
            }
        }

        cout << "Item not found.\n";
    }

    // Remove Item
    void removeItem() {

        int id;

        cout << "Enter item ID to remove: ";
        cin >> id;

        auto it = remove_if(
            inventory.begin(),
            inventory.end(),

            [id](const FoodItem& item) {
                return item.id == id;
            }
        );

        if (it != inventory.end()) {

            inventory.erase(it, inventory.end());

            rebuildPriorityQueue();

            cout << "Item removed successfully!\n";

        } else {

            cout << "Item not found.\n";
        }
    }

    // Show Soon To Expire Items
    void showSoonToExpireItems() {

        int alertDays;

        cout << "Enter number of days for expiry alert: ";
        cin >> alertDays;

        time_t now = time(nullptr);

        tm* localTime = localtime(&now);

        localTime->tm_hour = 0;
        localTime->tm_min = 0;
        localTime->tm_sec = 0;

        time_t today = mktime(localTime);

        priority_queue<FoodItem,
                       vector<FoodItem>,
                       CompareExpiry> tempQueue = expiryQueue;

        bool found = false;

        cout << "\n========== Soon-to-Expire Items ==========\n";

        while (!tempQueue.empty()) {

            FoodItem item = tempQueue.top();
            tempQueue.pop();

            time_t expiry = stringToDate(item.expiryDate);

            int daysLeft = daysBetween(today, expiry);

            if (daysLeft >= 0 && daysLeft <= alertDays) {

                cout << "ID: " << item.id
                     << " | Name: " << item.name
                     << " | Quantity: " << item.quantity
                     << " | Expiry Date: " << item.expiryDate
                     << " | Days Left: " << daysLeft
                     << endl;

                found = true;
            }
        }

        if (!found) {
            cout << "No items expiring within "
                 << alertDays
                 << " days.\n";
        }
    }

    // Remove Expired Items
    void removeExpiredItems() {

        time_t now = time(nullptr);

        tm* localTime = localtime(&now);

        localTime->tm_hour = 0;
        localTime->tm_min = 0;
        localTime->tm_sec = 0;

        time_t today = mktime(localTime);

        auto it = remove_if(
            inventory.begin(),
            inventory.end(),

            [today](const FoodItem& item) {
                return stringToDate(item.expiryDate) < today;
            }
        );

        if (it != inventory.end()) {

            inventory.erase(it, inventory.end());

            rebuildPriorityQueue();

            cout << "Expired items removed successfully.\n";

        } else {

            cout << "No expired items found.\n";
        }
    }
};

// Display Menu
void displayMenu() {

    cout << "\n========== Food Bank Inventory Management ==========\n";

    cout << "1. Add Food Donation\n";
    cout << "2. View Inventory\n";
    cout << "3. Search Food Item\n";
    cout << "4. Update Item Quantity\n";
    cout << "5. Remove Item\n";
    cout << "6. Show Soon-to-Expire Items\n";
    cout << "7. Remove Expired Items\n";
    cout << "8. Exit\n";

    cout << "Enter your choice: ";
}

// Main Function
int main() {

    InventoryManager manager;

    int choice;

    do {

        displayMenu();

        cin >> choice;

        switch (choice) {

            case 1:
                manager.addItem();
                break;

            case 2:
                manager.viewInventory();
                break;

            case 3:
                manager.searchItem();
                break;

            case 4:
                manager.updateQuantity();
                break;

            case 5:
                manager.removeItem();
                break;

            case 6:
                manager.showSoonToExpireItems();
                break;

            case 7:
                manager.removeExpiredItems();
                break;

            case 8:
                cout << "Exiting program. Thank you!\n";
                break;

            default:
                cout << "Invalid choice. Please try again.\n";
        }

    } while (choice != 8);

    return 0;
}
