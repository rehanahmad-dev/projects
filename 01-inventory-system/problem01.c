#include <fstream>
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <vector>

using namespace std;

class Item {
 public:
  int id, quantity;
  string name, description;
  float price;

  Item(int id, const string& name, const string& description, int quantity,
       float price)
      : id(id),
        name(name),
        description(description),
        quantity(quantity),
        price(price) {}

  void DisplayItem() const {
    cout << "Item ID: " << id << endl;
    cout << "Name: " << name << endl;
    cout << "Description: " << description << endl;
    cout << "Quantity: " << quantity << endl;
    cout << "Price: Rs" << price << endl;
  }

  void UpdateQuantity(int newQuantity) {
    if (newQuantity >= 0) {
      quantity = newQuantity;
      cout << "(\nQuantity updated successfully)." << endl;
    } else {
      cout << "(\nInvalid quantity)." << endl;
    }
  }
};

class Inventory {
 private:
  map<int, shared_ptr<Item>> items;

 public:
  void AddItem(const shared_ptr<Item>& item) {
    items[item->id] = item;
    cout << "(\nItem added to inventory)." << endl;
  }

  void RemoveItem(int itemId) {
    auto it = items.find(itemId);
    if (it != items.end()) {
      items.erase(it);
      cout << "(\nItem has been removed from the inventory.)" << endl;
    } else {
      cout << "(\nItem not found in inventory.)" << endl;
    }
  }

  shared_ptr<Item> FindItem(int itemId) {
    auto it = items.find(itemId);
    if (it != items.end()) {
      return it->second;
    }
    return nullptr;
  }

  void DisplayInventory() const {
    for (const auto& pair : items) {
      pair.second->DisplayItem();
      cout << "-----------------------" << endl;
    }
  }

  void SaveToFile(const string& filename) {
    ofstream file(filename);
    if (!file.is_open()) {
      cout << "Error: Cannot open file for writing." << endl;
      return;
    }

    for (const auto& pair : items) {
      const shared_ptr<Item>& item = pair.second;

      file << "Item ID :" << item->id << "\nItem name :" << item->name
           << "\nDescription :" << item->description
           << "\nQuantity:" << item->quantity << "\nItem Price :" << item->price
           << '\n';
    }
    file.close();
    cout << "(\nInventory saved to file.)" << endl;
  }

  void LoadFromFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
      cout << "Error: Cannot open file for reading." << endl;
      return;
    }

    items.clear();
    int id, quantity;
    string name, description;
    float price;

    while (file >> id >> ws && getline(file, name, ',') &&
           getline(file, description, ',') >> quantity >> ws >> price) {
      shared_ptr<Item> item =
          make_shared<Item>(id, name, description, quantity, price);
      AddItem(item);
    }
    file.close();
    cout << "(\nInventory loaded from the file.)" << endl;
  }
};

int main() {
  Inventory inventory;

  inventory.LoadFromFile("inventory.c++");

  while (true) {
    cout << "\n>>>>>> Inventory Management System <<<<<<\n";
    cout << "1. View Inventory\n";
    cout << "2. Add Item\n";
    cout << "3. Remove Item\n";
    cout << "4. Update Item Quantity\n";
    cout << "5. Save Inventory to File\n";
    cout << "6. Search Item by ID\n";
    cout << "7. Exit\n\n";
    cout << "Enter your choice: ";

    int choice;
    cin >> choice;

    switch (choice) {
      case 1:
        inventory.DisplayInventory();
        break;

      case 2: {
        int id, quantity;
        string name, description;
        float price;

        cout << "Enter Item ID:";
        cin >> id;
        cin.ignore();

        cout << "Enter Item Name:";
        cin.ignore();
        getline(cin, name);

        cout << "Enter Item Description:";
        getline(cin, description);

        cout << "Enter Item Quantity:";
        cin >> quantity;

        cout << "Enter Item Price: Rs";
        cin >> price;

        shared_ptr<Item> newItem =
            make_shared<Item>(id, name, description, quantity, price);
        inventory.AddItem(newItem);
        break;
      }

      case 3: {
        int idToRemove;
        cout << "Enter Item ID to Remove:";
        cin >> idToRemove;
        inventory.RemoveItem(idToRemove);
        break;
      }

      case 4: {
        int id_to_update, newQuantity;
        cout << "Enter Item ID to Update Quantity:";
        cin >> id_to_update;
        shared_ptr<Item> item_to_update = inventory.FindItem(id_to_update);
        if (item_to_update != nullptr) {
          cout << "Enter New Quantity:";
          cin >> newQuantity;
          item_to_update->UpdateQuantity(newQuantity);
        } else {
          cout << "Item not found in inventory." << endl;
        }
        break;
      }

      case 5:
        inventory.SaveToFile("inventory.c++");
        break;

      case 6: {
        int idToSearch;
        cout << "Enter Item ID to Search: ";
        cin >> idToSearch;
        shared_ptr<Item> foundItem = inventory.FindItem(idToSearch);
        if (foundItem != nullptr) {
          cout << "Item found:\n";
          foundItem->DisplayItem();
        } else {
          cout << "Item not found in inventory." << endl;
        }
        break;
      }

      case 7:
        inventory.SaveToFile("inventory.c++");
        return 0;

      default:
        cout << "\n[Note] = Invalid choice (Please try again)." << endl;
    }
  }

  return 0;
}
