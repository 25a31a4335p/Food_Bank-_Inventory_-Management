# 🍱 Food Bank Inventory Management System

A simple console-based **Food Bank Inventory Management System** developed in **C++**. This project helps food banks and donation centers efficiently manage donated food items, track expiry dates, update stock quantities, and remove expired items before they become science experiments in storage. 🥫

---

## ✨ Features

- ➕ Add food donation details  
- 📋 View complete inventory  
- 🔍 Search food items by name  
- ✏️ Update item quantity  
- ❌ Remove food items from inventory  
- ⏳ Display soon-to-expire food items  
- 🚨 Remove expired food items automatically  
- ⚡ Priority Queue implementation for expiry tracking  
- 📅 Date handling using C++ time library  

---

## 🛠️ Technologies Used

- 💻 C++
- 📚 STL Vector
- ⚡ Priority Queue
- 🔤 String Streams
- 📅 Time Library

---

## 📂 Data Structures Used

### 📦 Vector
Stores all food items in the inventory.

### ⚡ Priority Queue
Tracks items based on expiry date for efficient alerts and management.

---

## 📜 Menu Options

```text
1. Add Food Donation
2. View Inventory
3. Search Food Item
4. Update Item Quantity
5. Remove Item
6. Show Soon-to-Expire Items
7. Remove Expired Items
8. Exit
```

---

## 🧪 Sample Input

```text
Enter item name: Rice
Enter quantity: 50
Enter donor name: ABC Foundation
Enter expiry date (YYYY-MM-DD): 2026-06-20
```

---

## 🖥️ Sample Output

```text
Item added successfully!

Current Inventory:
ID   Name                 Qty       Donor               Expiry Date
----------------------------------------------------------------------
1    Rice                 50        ABC Foundation      2026-06-20
```

---

## ▶️ How to Run

### 🔹 Compile the Program

```bash
g++ foodbank.cpp -o foodbank
```

### 🔹 Run the Program

```bash
./foodbank
```

Windows users, naturally, get to do things differently because operating systems enjoy drama:

```bash
foodbank.exe
```

---

## 🎯 Project Objective

The main objective of this project is to reduce food wastage and improve food distribution management by efficiently tracking donated food items and their expiry dates.

---

## 🚀 Future Enhancements

- 💾 File handling for permanent data storage  
- 🔐 Admin login system  
- 🖼️ GUI version  
- 🗄️ Database integration  
- 📧 Automatic email/SMS expiry alerts  

---

## 👨‍💻 Team Members

-  M. Sushmitha  
-  B. Sritha  
-  V. Spoorthi  
-  K. Sanjay  
-  K. Yashwanth  

```
