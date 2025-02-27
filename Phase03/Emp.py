class Employee:
    def __init__(self, emp_id, emp_name, emp_salary, emp_department):
        self.emp_id = emp_id
        self.emp_name = emp_name
        self.emp_salary = emp_salary
        self.emp_department = emp_department

    def emp_assign_department(self, new_department):
        """Assigns a new department to the employee."""
        self.emp_department = new_department
        print(f"{self.emp_name} has been reassigned to {self.emp_department} department.")

    def calculate_emp_salary(self, hours_worked):
        """Calculates the salary based on hours worked and adds overtime if applicable."""
        if hours_worked > 50:
            overtime_hours = hours_worked - 50
            overtime_amount = overtime_hours * (self.emp_salary / 50)
            total_salary = self.emp_salary + overtime_amount
        else:
            total_salary = self.emp_salary

        return total_salary

    def print_employee_details(self):
        """Prints the details of the employee."""
        print(f"Employee ID: {self.emp_id}")
        print(f"Employee Name: {self.emp_name}")
        print(f"Employee Salary: {self.emp_salary}")
        print(f"Employee Department: {self.emp_department}")

# Sample employee data
employees = [
    Employee("E7876", "ADAMS", 50000, "ACCOUNTING"),
    Employee("E7499", "JONES", 45000, "RESEARCH"),
    Employee("E7900", "MARTIN", 50000, "SALES"),
    Employee("E7698", "SMITH", 55000, "OPERATIONS")
]

# Testing the methods
print("Before Department Change:")
employees[0].print_employee_details()

# Changing department
employees[0].emp_assign_department("HR")

print("\nAfter Department Change:")
employees[0].print_employee_details()

# Calculating salary with overtime
hours_worked = 55
new_salary = employees[0].calculate_emp_salary(hours_worked)
print(f"\nSalary after {hours_worked} hours of work: {new_salary}")
