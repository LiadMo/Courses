#ifndef MANAGER
#define MANAGER
#include "Citizen.h"
#include "Employee.h"
#include "set"
#include "ComparePointers.h"
/**
 *
 * Represent Manager
 *
 * The following functions are available:
 * A manager is a citizen - all functions of citizen are available
 * setSalary - adds a positive amount to the manager's salary
 * hasEmployee - checks by id if an employee works for the manager
 * addEmployee - adds an employee to the manager's employees set
 * removeEmployee - removes an employee from the set
 * setEmployeeSalary - set a positive amount of salary for the employee by his id
 * clearEmployeeSet - remove al employees from the set
 * setEmployeesSalary - adds the same amount to all of the employees salary
 *
 */
namespace mtm {
    class Manager : public Citizen {
        int salary;
        set<Employee*, ComparePointers> employees;

    public:
        Manager() = delete;
        Manager(const Manager& toCopy) = default;
        Manager(int id, string firstName, string lastName, int birthYear);
        ~Manager() override = default;

        // TODO: add const to all fun
        // member function
        int getSalary() const override; // return the salary
        void setSalary(int toAdd); // ADD or SUB amount to manager salary

        bool hasEmployee(int employee_id);

        void addEmployee(Employee* toAdd); // hire employee
        void removeEmployee(int id); // expel employee

        void setEmployeeSalary(int employee_id,int toAdd);
        void clearEmployeeSet();
        void setEmployeesSalary(int toAdd);

        std::ostream &printShort(std::ostream &os) override; // template to short print
        std::ostream &printLong(std::ostream &os) override; // template to long print
        std::ostream &printEmployees(std::ostream &os); // template to Employees short print
        Manager *clone() const override; // implement clone method (copy (Create a new Manager) and return Citizen pointer)
    };
}

#endif //MANAGER
