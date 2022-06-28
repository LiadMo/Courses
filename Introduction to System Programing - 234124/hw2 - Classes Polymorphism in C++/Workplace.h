#ifndef WORKPLACE
#define WORKPLACE
#include "Manager.h"
#include "set"
#include "exceptions.h"
#include "ComparePointers.h"
/**
 *
 * Represent Workplace
 *
 * The following functions are available:
 * FindManager - returns a pointer to the manager
 * isEmployeeHired -  bool func - checks if the employee is hired
 * isManagerHired -  bool func - checks if the manager is hired
 * hireManager - adds a manager to the managers set
 * fireEmployee - removes employee from his manager's employees set
 * fireManager - removes the manager from the managers set
 * fireManager_clean - removes the manager and removes the employees from his set
 * getManagersSalary - returns the mangers salary of the workplace
 * getWorkersSalary - returns the employees salary of the workplace
 * getName - returns the name of the workplace
 * getId - returns the id of the workplace
 *
 */
namespace mtm {
    using std::set;
    using std::string;

    class Workplace {
        int id;
        string name;
        int workersSalary;
        int managersSalary;
        set<Manager*, ComparePointers> managers;

    public:
        Workplace() = delete;
        Workplace(const Workplace& toCopy) = default;
        Workplace(int id, string name, int workersSalary, int managersSalary) : id(id), name(name), workersSalary(workersSalary),managersSalary(managersSalary), managers() {};
        ~Workplace() = default;


        template<class Qualifications>
        void hireEmployee(Qualifications min_qualifications, Employee* employee, int manager_id) {
            if (!min_qualifications(employee))
                throw EmployeeNotSelected();

            if (!isManagerHired(manager_id))
                throw ManagerIsNotHired();

            for (Manager* manager : this->managers) {
                if (manager->getId() == manager_id) {

                    if (manager->hasEmployee(employee->getId()))
                        throw EmployeeAlreadyHired();
                    else {
                        manager->addEmployee(employee);
                        employee->setSalary(this->workersSalary);
                    }
                }
            }
        }

        Manager* FindManager(int manager_id);
        bool isEmployeeHired(int employee_id);
        bool isManagerHired(int manager_id);
        void hireManager(Manager* manager);
        void fireEmployee(int employee_id, int manager_id); // TODO: fix in 'fireEmployee' the exception order if needed
        void fireManager(int manager_id);
        void fireManager_clean(int manager_id);
        int getManagersSalary() const;
        int getWorkersSalary() const;
        string getName() const;
        int getId() const;
        friend std::ostream &operator<<(std::ostream &os, const Workplace &workplace);
    };

}
#endif //WORKPLACE
