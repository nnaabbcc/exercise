import java.io.*;

public class Employee
{
    String name;
    int age;
    String designation;
    double salary;

    public Employee(String name)
    {
        this.name = name;
    }

    // set age
    public void empAge(int empAge)
    {
        age = empAge;
    }

    // set designation
    public void empDesignation(String empDesig)
    {
        designation = empDesig;
    }

    // set salary
    public void empSalary(double empSalary)
    {
        salary = empSalary;
    }

    // pring information
    public void printEmployee()
    {
        System.out.println("Name:" + name);
        System.out.println("Age:" + age);
        System.out.println("Designation:" + designation);
        System.out.println("Salary:" + salary);
    }
}
