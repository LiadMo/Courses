#include "City.h"
#include "Employee.h"

namespace mtm {
    bool City::is_employee_exists(int id) const{
        for (Citizen *iterator: this->citizens)
            if (iterator->getId() == id) {
                Employee* employee = dynamic_cast<Employee*>(iterator);
                if (employee)
                    return true;
                else
                    return false;
            }
        return false;
    }

    bool City::is_manager_exists(int id) const{
        for (Citizen *iterator: this->citizens)
            if (iterator->getId() == id) {
                Manager* manager = dynamic_cast<Manager*>(iterator);
                if (manager)
                    return true;
                else
                    return false;
            }
        return false;
    }

    bool City::is_faculty_exists(int id) const{
        for (Faculty<Condition> *iterator: this->faculties)
            if (iterator->getId() == id)
                return true;
        return false;
    }

    bool City::is_workplace_exists(int id) const{
        for (Workplace *iterator: this->workplaces)
            if (iterator->getId() == id)
                return true;
        return false;
    }


    void City::addEmployee(int id, string firstName, string lastName, int birthYear) {
        if (is_employee_exists(id) || is_manager_exists(id))
            throw CitizenAlreadyExists();

        Citizen *toAdd = new Employee(id, firstName, lastName, birthYear);
        this->citizens.insert(toAdd);
    }

    void City::addManager(int id, string firstName, string lastName, int birthYear) {
        if (is_manager_exists(id) || is_employee_exists(id))
            throw CitizenAlreadyExists();

        Citizen *toAdd = new Manager(id, firstName, lastName, birthYear);
        this->citizens.insert(toAdd);
    }

    void City::addFaculty(int id, Skill &skill, int addedPoints, Condition *cond) {
        if (is_faculty_exists(id))
            throw FacultyAlreadyExists();

        Faculty<Condition> *toAdd = new Faculty<Condition>(id, skill, addedPoints, cond);
        this->faculties.insert(toAdd);
    }

    void City::createWorkplace(int id, string name, int workersSalary, int managersSalary) {
        if (is_workplace_exists(id))
            throw WorkplaceAlreadyExists();

        Workplace *toAdd = new Workplace(id, name, workersSalary, managersSalary);
        this->workplaces.insert(toAdd);
    }

    void City::teachAtFaculty(int employee_id, int faculty_id) {
        if (!is_employee_exists(employee_id))
            throw EmployeeDoesNotExist();

        if (!is_faculty_exists(faculty_id))
            throw FacultyDoesNotExist();

        for (Citizen *citizen: this->citizens) {
            if (citizen->getId() == employee_id) {
                for (Faculty<Condition> *faculty: this->faculties) {
                    if (faculty->getId() == faculty_id) {
                        Employee* employee = dynamic_cast<Employee *>(citizen);
                        if (employee)
                            faculty->teach(employee);
                        else
                            throw EmployeeDoesNotExist();
                    }
                }
            }
        }
    }

    void City::hireManagerAtWorkplace(int manager_id, int workplace_id) {
        if (!is_manager_exists(manager_id))
            throw ManagerDoesNotExist();
        if(!is_workplace_exists(workplace_id))
            throw WorkplaceDoesNotExist();

        for (Citizen* citizen : this->citizens) {
            if (citizen->getId() == manager_id){
                Manager* manager = dynamic_cast<Manager*>(citizen);
                if (manager) {
                    for (Workplace *workplace: this->workplaces) {
                        if (workplace->getId() == workplace_id) {
                            workplace->hireManager(manager);
                            return;
                        }
                    }
                }
                else {
                    throw ManagerDoesNotExist();
                }
            }
        }
    }

    int City::getAllAboveSalary(ostream &os, int minimum_salary) {
        int counter = 0;
        for (Citizen* citizen : this->citizens)
            if (citizen->getSalary() >= minimum_salary) {
                counter++;
                citizen->printShort(os);
            }
        return counter;
    }


    bool City::isWorkingInTheSameWorkplace(int employee1_id, int employee2_id) {
        if (!is_employee_exists(employee1_id) || !is_employee_exists(employee2_id))
            throw EmployeeDoesNotExist();

        for (Workplace* workplace : this->workplaces)
            if ((workplace->isEmployeeHired(employee1_id)) && (workplace->isEmployeeHired(employee2_id)))
                return true;

        return false;
    }

    ostream &City::printAllEmployeesWithSkill(ostream &os, int skill_id) {
        for (Citizen* citizen : this->citizens) {
            Employee* employee = dynamic_cast<Employee*>(citizen);
            if(employee && employee->hasSkill(skill_id))
                employee->printShort(os);
        }
        return os;
    }

    void City::fireEmployeeAtWorkplace(int employee_id, int manager_id, int workplace_id) {
        if (!is_employee_exists(employee_id))
            throw EmployeeDoesNotExist();
        if(!is_manager_exists(manager_id))
            throw ManagerDoesNotExist();
        if(!is_workplace_exists(workplace_id))
            throw WorkplaceDoesNotExist();

        for (Workplace* workplace : this->workplaces)
            if (workplace->getId() == workplace_id)
                workplace->fireEmployee(employee_id,manager_id);
    }

    void City::fireManagerAtWorkplace(int manager_id, int workplace_id) {
        if(!is_manager_exists(manager_id))
            throw ManagerDoesNotExist();
        if(!is_workplace_exists(workplace_id))
            throw WorkplaceDoesNotExist();

        for (Workplace* workplace : this->workplaces)
            if (workplace->getId() == workplace_id) {
                workplace->fireManager_clean(manager_id);
            }
    }
}