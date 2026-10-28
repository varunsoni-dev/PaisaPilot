#include <stdio.h>
#include <string.h>

#define MAX_TRANSACTIONS 1000

#define INCOME 1
#define EXPENSE 2

#define DATA_FILE "data/transactions.txt"

/* Structure to store one transaction */
struct Transaction
{
    int id;
    int type;
    int amount;
    char category[30];
    char description[100];
};

/* Array to store transactions */
struct Transaction transactions[MAX_TRANSACTIONS];

int transaction_count = 0;
int next_id = 1001;


/* Function declarations */
void load_transactions(void);
void save_transactions(void);
void add_transaction(int type);
void view_transactions(void);
void show_dashboard(void);
void show_category_summary(void);
void money_survival_predictor(void);

/* Save all transactions to a text file */
void save_transactions(void)
{
    FILE *file;
    int i;

    file = fopen(DATA_FILE, "w");

    if (file == NULL)
    {
        printf("\nError: Could not save transactions.\n");
        printf("Please check whether the data folder exists.\n");
        return;
    }

    for (i = 0; i < transaction_count; i++)
    {
        fprintf(file, "%d %d %d %s %s\n",
                transactions[i].id,
                transactions[i].type,
                transactions[i].amount,
                transactions[i].category,
                transactions[i].description);
    }

    fclose(file);
}


/* Load previously saved transactions */
void load_transactions(void)
{
    FILE *file;

    file = fopen(DATA_FILE, "r");

    if (file == NULL)
    {
        printf("No previous transactions found. Starting fresh.\n");
        return;
    }

    while (transaction_count < MAX_TRANSACTIONS &&
           fscanf(file, "%d %d %d %29s %99[^\n]",
                  &transactions[transaction_count].id,
                  &transactions[transaction_count].type,
                  &transactions[transaction_count].amount,
                  transactions[transaction_count].category,
                  transactions[transaction_count].description) == 5)
    {
        if (transactions[transaction_count].id >= next_id)
        {
            next_id = transactions[transaction_count].id + 1;
        }

        transaction_count++;
    }

    fclose(file);
}


/* Add a new income or expense */
void add_transaction(int type)
{
    struct Transaction t;
    int choice;

    if (transaction_count >= MAX_TRANSACTIONS)
    {
        printf("\nTransaction limit reached!\n");
        return;
    }

    t.id = next_id;
    t.type = type;

    printf("\nEnter amount in whole rupees: ");
    if (scanf("%d", &t.amount) != 1 || t.amount <= 0)
    {
        printf("Invalid amount. Please enter a positive number.\n");
        return;
    }

    if (type == INCOME)
    {
        printf("\n--- Income Categories ---\n");
        printf("1. Salary\n");
        printf("2. Other\n");
        printf("Choose category: ");

        if (scanf("%d", &choice) != 1)
        {
            printf("Invalid category.\n");
            return;
        }

        switch (choice)
        {
            case 1:
                strcpy(t.category, "Salary");
                break;

            case 2:
                strcpy(t.category, "Other");
                break;

            default:
                printf("Invalid category choice.\n");
                return;
        }
    }
    else
    {
        printf("\n--- Expense Categories ---\n");
        printf("1. Food\n");
        printf("2. Travel\n");
        printf("3. Education\n");
        printf("4. Shopping\n");
        printf("5. Bills\n");
        printf("6. Health\n");
        printf("7. Entertainment\n");
        printf("8. Other\n");
        printf("Choose category: ");

        if (scanf("%d", &choice) != 1)
        {
            printf("Invalid category.\n");
            return;
        }

        switch (choice)
        {
            case 1:
                strcpy(t.category, "Food");
                break;

            case 2:
                strcpy(t.category, "Travel");
                break;

            case 3:
                strcpy(t.category, "Education");
                break;

            case 4:
                strcpy(t.category, "Shopping");
                break;

            case 5:
                strcpy(t.category, "Bills");
                break;

            case 6:
                strcpy(t.category, "Health");
                break;

            case 7:
                strcpy(t.category, "Entertainment");
                break;

            case 8:
                strcpy(t.category, "Other");
                break;

            default:
                printf("Invalid category choice.\n");
                return;
        }
    }

    printf("Enter description (one line): ");

    if (scanf(" %99[^\n]", t.description) != 1)
    {
        printf("Invalid description.\n");
        return;
    }

    transactions[transaction_count] = t;

    transaction_count++;
    next_id++;

    save_transactions();

    printf("\nTransaction added successfully!\n");
    printf("Transaction ID: %d\n", t.id);
}


/* Display all transactions */
void view_transactions(void)
{
    int i;

    if (transaction_count == 0)
    {
        printf("\nNo transactions recorded yet.\n");
        return;
    }

    printf("\n================ TRANSACTION HISTORY ================\n");

    printf("%-6s %-10s %-10s %-16s %s\n",
           "ID", "Type", "Amount", "Category", "Description");

    printf("-----------------------------------------------------\n");

    for (i = 0; i < transaction_count; i++)
    {
        printf("%-6d ", transactions[i].id);

        if (transactions[i].type == INCOME)
        {
            printf("%-10s ", "Income");
        }
        else
        {
            printf("%-10s ", "Expense");
        }

        printf("Rs.%-7d %-16s %s\n",
               transactions[i].amount,
               transactions[i].category,
               transactions[i].description);
    }

    printf("=====================================================\n");
}


/* Display total income, expenses, and balance */
void show_dashboard(void)
{
    int i;
    int total_income = 0;
    int total_expenses = 0;
    int balance;

    for (i = 0; i < transaction_count; i++)
    {
        if (transactions[i].type == INCOME)
        {
            total_income += transactions[i].amount;
        }
        else if (transactions[i].type == EXPENSE)
        {
            total_expenses += transactions[i].amount;
        }
    }

    balance = total_income - total_expenses;

    printf("\n============= FINANCIAL DASHBOARD =============\n");

    printf("Total Income   : Rs. %d\n", total_income);
    printf("Total Expenses : Rs. %d\n", total_expenses);
    printf("Current Balance: Rs. %d\n", balance);

    printf("================================================\n");
}


/* Display expense totals and highest spending category */
void show_category_summary(void)
{
    char categories[8][30] =
    {
        "Food",
        "Travel",
        "Education",
        "Shopping",
        "Bills",
        "Health",
        "Entertainment",
        "Other"
    };

    int category_totals[8] = {0};

    int i, j;
    int highest_index = -1;

    /* Calculate total spending in each category */
    for (i = 0; i < transaction_count; i++)
    {
        if (transactions[i].type == EXPENSE)
        {
            for (j = 0; j < 8; j++)
            {
                if (strcmp(transactions[i].category, categories[j]) == 0)
                {
                    category_totals[j] += transactions[i].amount;
                    break;
                }
            }
        }
    }

    printf("\n========== CATEGORY-WISE EXPENSE SUMMARY ==========\n");

    /* Find the category with the highest spending */
    for (i = 0; i < 8; i++)
    {
        if (category_totals[i] > 0)
        {
            printf("%-16s Rs. %d\n",
                   categories[i],
                   category_totals[i]);

            if (highest_index == -1 ||
                category_totals[i] > category_totals[highest_index])
            {
                highest_index = i;
            }
        }
    }

    /* Display the highest spending category */
    if (highest_index == -1)
    {
        printf("\nNo expenses recorded yet.\n");
    }
    else
    {
        printf("\n----------------------------------------------\n");
        printf("Highest Spending Category: %s\n",
               categories[highest_index]);

        printf("Amount Spent: Rs. %d\n",
               category_totals[highest_index]);
    }

    printf("===================================================\n");
}

/* Estimate how many days the remaining money will last */
void money_survival_predictor(void)
{
    int i;
    int total_income = 0;
    int total_expenses = 0;
    int balance;
    int days;
    int average_daily_spending;
    int estimated_days;

    /* Calculate income and expenses */
    for (i = 0; i < transaction_count; i++)
    {
        if (transactions[i].type == INCOME)
        {
            total_income += transactions[i].amount;
        }
        else if (transactions[i].type == EXPENSE)
        {
            total_expenses += transactions[i].amount;
        }
    }

    balance = total_income - total_expenses;

    printf("\n========== MONEY SURVIVAL PREDICTOR ==========\n");

    printf("Current Balance: Rs. %d\n", balance);

    if (balance <= 0)
    {
        printf("Your balance is zero or negative.\n");
        printf("Please review your spending.\n");
    }
    else
    {
        printf("\nFor how many days have you tracked your expenses? ");
        if (scanf("%d", &days) != 1 || days <= 0)
        {
            printf("Please enter a valid number of days.\n");
            printf("==============================================\n");
            return;
        }

        average_daily_spending = total_expenses / days;

        printf("Total Expenses: Rs. %d\n", total_expenses);
        printf("Average Daily Spending: Rs. %d\n",
               average_daily_spending);

        if (average_daily_spending == 0)
        {
            printf("\nNo daily spending to calculate yet.\n");
        }
        else
        {
            estimated_days = balance / average_daily_spending;

            printf("Estimated Money Duration: %d days\n",
                   estimated_days);

            printf("\nNote: This is an estimate based on your");
            printf("\nspending during the period you entered.\n");
        }
    }

    printf("==============================================\n");
}


/* Main function */
int main(void)
{
    int choice;

    printf("====================================\n");
    printf("          PAISAPILOT\n");
    printf("     Personal Finance Tracker\n");
    printf("====================================\n");

    load_transactions();

    while (1)
    {
        printf("\n--------------- MAIN MENU ---------------\n");
        printf("1. Add Income\n");
        printf("2. Add Expense\n");
        printf("3. View Transaction History\n");
        printf("4. Financial Dashboard\n");
        printf("5. Category-wise Expense Summary\n");
        printf("6. Money Survival Predictor\n");
        printf("7. Exit\n");
        printf("------------------------------------------\n");

        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1)
        {
            printf("Please enter a number.\n");
            break;
        }

        switch (choice)
        {
            case 1:
                add_transaction(INCOME);
                break;

            case 2:
                add_transaction(EXPENSE);
                break;

            case 3:
                view_transactions();
                break;

            case 4:
                show_dashboard();
                break;

            case 5:
                show_category_summary();
                break;

            case 6:
                money_survival_predictor();
                break;

            case 7:
                printf("\nThank you for using PaisaPilot!\n");
                return 0;

            default:
                printf("\nInvalid choice. Please select 1-7.\n");
        }
    }

    return 0;
}