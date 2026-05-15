# Food Bank Inventory Management System

A C++ console-based application designed to help food banks manage food donations, track inventory, monitor expiry dates using priority queues, and generate alerts for soon-to-expire food items.

## Project Overview

Food banks receive many donations daily, and managing these items manually can be difficult. This project provides a simple inventory management system that allows users to:

- Add donated food items
- Store item quantity and expiry date
- Track items based on expiry date
- Generate alerts for soon-to-expire food
- Remove expired or distributed items
- Display current inventory

The system uses a **priority queue** to prioritize food items that expire soonest.

## Features

- Add new food donations
- View all inventory items
- Track expiry dates
- Alert users about soon-to-expire items
- Remove expired items
- Search food items by name
- Update item quantity
- Priority queue implementation for expiry tracking

## Technologies Used

- C++
- Standard Template Library
- Priority Queue
- Object-Oriented Programming
- Console-based interface

## Data Structures Used

### Priority Queue

A priority queue is used to store food items according to their expiry dates.

Items with the earliest expiry date have the highest priority, so they can be distributed first.

### Vector

A vector is used to store the general inventory list.

## Project Structure

```text
Food-Bank-Inventory-Management/
│
├── main.cpp
├── README.md
└── screenshots/
