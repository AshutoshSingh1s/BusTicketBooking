# 🚌 Tour Bus Booking System - C++ Project

This is a console-based Tour Bus Booking System written in **C++**, which allows users to manage tour buses and book tickets for customers. It uses binary file handling to store bus and ticket data persistently.

---

## 📂 Features

- Add new tour buses with details
- View specific bus details
- Display all available buses
- Delete a tour bus
- Book a ticket by destination and customer name
- Display all booked tickets
- Persistent storage using binary files

---

## 🛠️ Requirements

- C++ compiler (e.g., `g++`)
- VS Code or any C++ IDE
- Works on **Windows**, **Linux**, or **macOS**

---

## 💻 How to Run

1. **Save the source file:**

   Save your code as:


2. **Open terminal in VS Code** or any terminal window.

3. **Compile the program:**

```bash
g++ -o tourbus tourbus.cpp
./tourbus       # Linux/macOS
tourbus.exe     # Windows (or just `tourbus`)

## 📋 Menu Options & Inputs

```text
1. Add a New Tour Bus
   - Bus ID           → e.g., 101
   - Destination      → e.g., Delhi
   - Time             → e.g., 8:30am
   - Fare             → e.g., 500

2. Show Selected Bus
   - Enter Bus ID     → e.g., 101

3. Display All Buses
   - No input needed

4. Delete a Bus
   - Enter Bus ID     → e.g., 101

5. Book a Ticket
   - Destination      → e.g., Delhi (must match exactly)
   - Customer Name    → e.g., John

6. Display Booked Tickets
   - No input needed

7. Exit
