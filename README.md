# PaisaPilot 💰

### A Personal Finance Tracker Built with C

PaisaPilot is a command-line personal finance management application developed in C. It helps users record their income and expenses, monitor their balance, analyze spending categories, and estimate how long their remaining money may last.

The project demonstrates fundamental C programming concepts through a practical, real-world application.

## ✨ Features

* **Income Management:** Record income with categories and descriptions.
* **Expense Tracking:** Record expenses across different spending categories.
* **Transaction History:** View previously recorded transactions.
* **Financial Dashboard:** Calculate total income, total expenses, and current balance.
* **Category-wise Expense Summary:** Analyze spending across categories and identify the highest-spending category.
* **Money Survival Predictor:** Estimate how many days the remaining balance may last based on average daily spending.
* **Data Persistence:** Store transactions in a text file and load them when the application starts.

## 🛠️ Tech Stack

* **Language:** C
* **Compiler:** GCC
* **Concepts:** Structures, arrays, functions, loops, conditional statements, strings, and file handling.
* **Storage:** Text file

## 📁 Project Structure

```text
PaisaPilot/
├── src/
│   └── main.c
├── data/
│   └── transactions.txt
├── .gitignore
└── README.md
```

The `transactions.txt` file is created when transactions are saved successfully. The `data` directory must exist before running the application.

## ⚙️ Requirements

* GCC compiler
* Visual Studio Code or another C-compatible editor
* Windows, Linux, or another environment configured with GCC

## 🚀 Getting Started

### 1. Clone the repository

```bash
git clone https://github.com/YOUR-USERNAME/PaisaPilot.git
cd PaisaPilot
```

Replace `YOUR-USERNAME` with your GitHub username.

### 2. Compile the program

```bash
gcc -std=c99 -Wall -Wextra -pedantic src/main.c -o paisapilot
```

### 3. Run the application

On Windows PowerShell:

```powershell
.\paisapilot.exe
```

On Linux:

```bash
./paisapilot
```

Run the executable from the project root directory so the application can access `data/transactions.txt`.

## 📊 Money Survival Predictor

The predictor calculates an estimated daily spending amount from the recorded expenses and the number of days entered by the user.

**Formula:**

Average Daily Spending = Total Expenses / Number of Days

Estimated Duration = Current Balance / Average Daily Spending

The result is an estimate, not a guarantee. Its usefulness depends on entering an appropriate tracking period and maintaining a representative spending history.

## 🎓 Learning Outcomes

This project provides practical experience with:

* Structures and arrays
* Functions and modular programming
* Loops and conditional logic
* String handling
* Text-file operations using `fopen()`, `fprintf()`, `fscanf()`, and `fclose()`
* Basic financial calculations

## 🔮 Future Improvements

* Automatic transaction date tracking
* Monthly budgets and spending limits
* Budget alerts
* Improved input validation
* More detailed financial reports

## 👨‍💻 Author

**Your Name**

First-year B.E. Computer Science Engineering student

## 📜 License

This project is available for educational and learning purposes.
