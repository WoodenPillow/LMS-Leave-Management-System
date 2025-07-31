# 🗂️ Leave Management System (LMS)

A CLI-based **Leave Management System** developed in C for managing employee leaves across three roles: **Admin**, **Staff**, and **Leave Approver**. It includes user login, role-based menus, leave application workflows, and file read/write capabilities.

---

## 🧩 System Roles & Features

### 👨‍💼 Admin
- Add new employees
- View employee list
- View leave summaries
- Read/write employee data from/to files

### 👷 Staff
- View own leave records
- Apply for leave
- Cancel leave requests
- View pending leave status

### 📝 Leave Approver
- Approve or reject leave requests
- View all staff leave records
- See which staff are currently on leave
- Save leave summary reports

---

## 🔐 Login Credentials (Default)
| Role             | Username  | Password  |
|------------------|-----------|-----------|
| Admin            | `admin`   | `admin`   |
| Staff            | `staff`   | `staff`   |
| Leave Approver   | `leaveapp`| `leaveapp`|

---

## 📁 File Structure

This system likely depends on the following (based on `#include "Functions.h"`):

- `main.c` – Main control flow and role menu switching
- `Functions.h` / `Functions.c` – Implementations for functions like:
  - `add_employee()`
  - `apply_for_leave()`
  - `view_employees()`
  - `view_leaves()`, etc.

Ensure `Functions.h` and any associated `.c` files are present for a successful compile.

---

## 🛠️ Compile & Run

### 🔧 Compile:
```bash
gcc main.c Functions.c -o main
