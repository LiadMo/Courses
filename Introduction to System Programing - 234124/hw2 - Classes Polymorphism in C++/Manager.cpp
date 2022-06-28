#include "Manager.h"
#include "exceptions.h"
#include "iostream"

namespace mtm {
    using std::cout;
    using std::endl;

    Manager::Manager(int id, string firstName, string lastName, int birthYear) : Citizen(id, firstName, lastName, birthYear), salary(0), employees() {}


    int Manager::getSalary() const {
        return this->salary;
    }

    void Manager::setSalary(int toAdd) {
        this->salary += toAdd;
        if (this->salary < 0)
            this->salary = 0;
    }

    bool Manager::hasEmployee(int employee_id) {
        for (Employee* employee : this->employees)
            if (employee->getId() == employee_id)
                return true;
        return false;
    }

    void Manager::clearEmployeeSet() {
        this->employees.clear();
    }

    void Manager::addEmployee(Employee* toAdd) {
        if (this->hasEmployee(toAdd->getId()))
            throw EmployeeAlreadyHired();

        this->employees.insert(toAdd);
    }

    void Manager::removeEmployee(int id) {
        for (Employee* employee : this->employees) {
            if (employee->getId() == id) {
                this->employees.erase(employee);
                return;
            }
        }
        throw EmployeeIsNotHired();
    }

    void Manager::setEmployeesSalary(int toAdd) {
        for (Employee* employee : this->employees)
            employee->setSalary(toAdd);
    }

    void Manager::setEmployeeSalary(int employee_id, int toAdd) {
        if (!hasEmployee(employee_id))
            throw EmployeeIsNotHired();

        for (Employee* employee : this->employees)
            if (employee->getId() == employee_id)
                employee->setSalary(toAdd);
    }

    Manager* Manager::clone() const {
        return new Manager(*this);
    }


    std::ostream &Manager::printEmployees(std::ostream &os) {
        for (const Employee* iterator: this->employees){
            Employee(*iterator).printShort(os);
        }
        return os;
    }

    std::ostream &Manager::printShort(std::ostream &os) {
        os << this->getFirstName() << " " << this->getLastName() << endl;
        os << "Salary: " << this->salary << endl;
        return os;
    }

    std::ostream &Manager::printLong(std::ostream &os) {
        os << this->getFirstName() << " " << this->getLastName() << endl;
        os << "id - " << this->getId() << " birth_year - " << this->getBirthYear() << endl;
        os << "Salary: " << this->salary << endl;
        if (!this->employees.empty()){
            os << "Employees: " << endl;
            for (const Employee* iterator: this->employees)
                Employee(*iterator).printShort(os);
        }
        return os;
    }
}