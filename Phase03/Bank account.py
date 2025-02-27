class BankAccount:
    def __init__(self, account_number, customer_name, balance, date_of_opening):
        self.account_number = account_number
        self.customer_name = customer_name
        self.balance = balance
        self.date_of_opening = date_of_opening

    def deposit(self, amount):
        """Deposits a given amount into the account."""
        if amount > 0:
            self.balance += amount
            print(f"₹{amount} deposited successfully. New balance: ₹{self.balance}")
        else:
            print("Deposit amount must be positive.")

    def withdraw(self, amount):
        """Withdraws a given amount from the account if sufficient balance is available."""
        if amount > 0:
            if self.balance >= amount:
                self.balance -= amount
                print(f"₹{amount} withdrawn successfully. Remaining balance: ₹{self.balance}")
            else:
                print("Insufficient balance.")
        else:
            print("Withdrawal amount must be positive.")

    def check_balance(self):
        """Displays the current account balance."""
        print(f"Account Balance: ₹{self.balance}")

    def print_account_details(self):
        """Prints the account details."""
        print(f"Account Number: {self.account_number}")
        print(f"Customer Name: {self.customer_name}")
        print(f"Date of Opening: {self.date_of_opening}")
        print(f"Current Balance: ₹{self.balance}")

# Creating a sample bank account
account = BankAccount("123456789", "John Doe", 5000, "2023-05-10")

# Testing the methods
account.print_account_details()

print("\nPerforming Transactions:")
account.deposit(2000)
account.withdraw(1000)
account.check_balance()
