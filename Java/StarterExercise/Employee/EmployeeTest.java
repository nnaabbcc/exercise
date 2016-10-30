import java.io.*;

public class EmployeeTest
{
    public static void main(String args[])
    {
        // Create two employee object
        Employee empOne = new Employee("James Simith");
        Employee empTwo = new Employee("Mary Anne");

        // call the member function
        empOne.empAge(26);
        empOne.empDesignation("Senior Soft Engineer");
        empOne.empSalary(1000);
        empOne.printEmployee();

        empTwo.empAge(21);
        empTwo.empDesignation("Software Engineer");
        empTwo.empSalary(500);
        empTwo.printEmployee();
    }
}
