# 🏨 Hotel Sea Breeze — Management System

A command-line Hotel Management System built in C as a semester project. It handles customer bookings, room assignments, billing, and data persistence using file I/O.

---

## 📋 Features

- **Customer Check-In** — Add guests with full details (name, CNIC, phone, room type, dates)
- **Auto Room Assignment** — Automatically assigns the first available room (out of 20)
- **View Guest Details** — Look up any booking by room number
- **Update Records** — Modify guest name, phone, check-out date, or room number
- **Room Availability** — See which rooms are booked and which are free
- **Bill Generation** — Automatically calculates total charges based on room type and days stayed
- **Delete Records** — Remove a guest's booking upon check-out
- **Data Persistence** — All records are saved to and loaded from `hotel_data.txt`
- **Login System** — Simple admin authentication before accessing the system

---

## 🏗️ Project Structure

```
hotel-management-system/
├── final_project.c     # Main source file (all logic)
├── hotel_data.txt      # Auto-generated data file (created on first save)
└── README.md
```

---

## 💻 How to Compile & Run

### Prerequisites
- GCC compiler (or any standard C compiler)

### Compile
```bash
gcc final_project.c -o hotel
```

### Run
```bash
./hotel
```

---

## 🔐 Default Login Credentials

| Field    | Value   |
|----------|---------|
| Username | `admin` |
| Password | `12345` |

---

## 🧭 Menu Options

```
1 --> Add Customer
2 --> Show Details
3 --> Update Information
4 --> Room Availability
5 --> Generate Bill
6 --> Delete Customer
7 --> View Hotel Charges
8 --> Exit & Save
```

---

## 💰 Room Charges

| Room Type   | Per Night  | Service Charge |
|-------------|------------|----------------|
| Single Room | Rs. 10,000 | Rs. 1,200      |
| Double Room | Rs. 20,000 | Rs. 2,000      |

**Bill Formula:** `(Room Rate × Days) + Service Charge`

---

## 📦 Data Storage

Records are saved in a plain-text CSV format in `hotel_data.txt`. Data is:
- **Loaded** automatically when the program starts
- **Saved** after every add, update, or delete operation, and on exit

---

## ⚙️ Technical Details

- Language: **C**
- Max Rooms: **20**
- Data Format: Comma-separated values (CSV) in `hotel_data.txt`
- Terminal colors supported via ANSI escape codes (green for available rooms)

---

## 🚧 Limitations & Future Improvements

- Password is stored in plain text (no encryption)
- No date validation on check-in/check-out input
- Single admin user only
- Could be extended with: multi-floor room maps, payment tracking, or a GUI

---

## 👤 Author

**[Muhammad Ahsan]**  
Computer Systems Engineering — NED University  
*Semester Project*
