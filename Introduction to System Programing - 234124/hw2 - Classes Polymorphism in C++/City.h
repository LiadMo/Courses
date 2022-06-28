#ifndef CITY
#define CITY

#include "Citizen.h"
#include "Employee.h"
#include "Manager.h"
#include "Workplace.h"
#include "Faculty.h"
#include "Skill.h"
#include "exception"
#include "ComparePointers.h"
#include <memory>

/**
*
* Represent City
*
* The following functions are available:
* is_employee_exists - checks if an employee exists
* is_manager_exists - checks if a manager exists
 * is_faculty_exists - checks if a faculty exists
 * is_workplace_exists - checks if a workplace exists
 * addEmployee - adds an employee to the set
 * addManager - adds a manager to the set
 * addFaculty - adds a faculty to the set
 * createWorkplace - adds a workplace to the set
 * teachAtFaculty - tries to teach an employee a skill
 * hireEmployeeAtWorkplace - hires an employee for a workplace
 * hireManagerAtWorkplace - hires a manager for a workplace
 * fireEmployeeAtWorkplace - removes an employee for a workplace (his manager's set)
 * fireManagerAtWorkplace - removes a manager from a workplace
 * getAllAboveSalary - prints all of the citizens that earns more than a specific sum
 * isWorkingInTheSameWorkplace - checks if two employees works for the same workplace
 * printAllEmployeesWithSkill - prints a short print of every employee in the city
*/
namespace mtm {
    using std::shared_ptr;
    using std::string;
    using std::ostream;

    class City {
        set<Citizen*, ComparePointers> citizens;
        set<Faculty<Condition>* > faculties;
        set<Workplace*> workplaces;
        string name;

    public:
        City() = delete;
        City(const City& toCopy) = default;
        City(string cityName) : name(cityName) {};
        ~City() {
            for (Citizen* citizen : this->citizens)
                delete citizen;

            for(Faculty<Condition>* faculty : this->faculties)
                delete faculty;

            for(Workplace* workplace : this->workplaces)
                delete workplace;
        };

        bool is_employee_exists(int id) const;
        bool is_manager_exists(int id) const;
        bool is_faculty_exists(int id) const;
        bool is_workplace_exists(int id) const;

        void addEmployee(int id, string firstName, string lastName, int birthYear);
        void addManager(int id, string firstName, string lastName, int birthYear);
        void addFaculty(int id, Skill &skill, int addedPoints, Condition *cond);
        void createWorkplace(int id, string name, int workersSalary, int managersSalary);
        void teachAtFaculty(int employee_id, int faculty_id);

        template<class EmployeeCondition>
        void hireEmployeeAtWorkplace(EmployeeCondition empCondition, int employee_id, int manager_id, int workplace_id){
            if (!is_employee_exists(employee_id))
                throw EmployeeDoesNotExist();
            if (!is_manager_exists(manager_id))
                throw ManagerDoesNotExist();
            if(!is_workplace_exists(workplace_id))
                throw WorkplaceDoesNotExist();

            for (Citizen* citizen : this->citizens){
                if (citizen->getId() == employee_id) {
                    Employee *employee = dynamic_cast<Employee *>(citizen);
                    if (employee) {
                        for (Workplace *workplace: this->workplaces)
                            if (workplace->getId() == workplace_id) {
                                workplace->template hireEmployee(empCondition, employee, manager_id);
                            }
                    }
                    else {
                        throw EmployeeDoesNotExist();
                    }

                }
            }
        }
        void hireManagerAtWorkplace(int manager_id, int workplace_id);
        void fireEmployeeAtWorkplace(int employee_id, int manager_id, int workplace_id);
        void fireManagerAtWorkplace(int manager_id, int workplace_id);
        int getAllAboveSalary(ostream& os, int minimum_salary);
        bool isWorkingInTheSameWorkplace(int employee1_id, int employee2_id);
        ostream& printAllEmployeesWithSkill(ostream& os, int skill_id);
    };
}


#endif //CITY
