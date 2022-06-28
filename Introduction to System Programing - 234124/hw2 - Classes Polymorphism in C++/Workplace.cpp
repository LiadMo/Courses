#include "Workplace.h"
#include "exceptions.h"
#include "Workplace.h"
#include "iostream"

namespace mtm {
    using std::cout;
    using std::endl;

    int Workplace::getManagersSalary() const {
        return this->managersSalary;
    }

    int Workplace::getWorkersSalary() const {
        return this->workersSalary;
    }

    std::string Workplace::getName() const {
        return this->name;
    }

    int Workplace::getId() const {
        return this->id;
    }

    void Workplace::hireManager(Manager *manager) {
        for (Manager* iterator : this->managers)
            if (iterator->getId() == manager->getId())
                throw ManagerAlreadyHired();

//        if (manager->is_hired)
//            throw CanNotHireManager();

        if(manager->getSalary() > 0)
            throw CanNotHireManager();

//        manager->is_hired = true;
        this->managers.insert(manager);
        manager->setEmployeesSalary(this->workersSalary);
        manager->setSalary(this->managersSalary);
    }

    void Workplace::fireEmployee(int employee_id, int manager_id) {
        if (!isManagerHired(manager_id))
            throw ManagerIsNotHired();

        for (Manager* manager : this->managers)
            if (manager->getId() == manager_id) {
                manager->setEmployeeSalary(employee_id,-(this->workersSalary)); // throw EmployeeIsNotHired() exs if employee isn't in manager
                manager->removeEmployee(employee_id); // throw EmployeeIsNotHired() exs if employee isn't in manager
            }
    }

    void Workplace::fireManager(int manager_id) {
        if (!isManagerHired(manager_id))
            throw ManagerIsNotHired();

        Manager* manager = FindManager(manager_id);
        manager->setSalary(-((this->managersSalary)));
        manager->setEmployeesSalary(-((this->workersSalary)));
        this->managers.erase(manager);

//        for (Manager* manager : this->managers)
//            if (manager->getId() == manager_id) {
//                manager->setSalary(-(this->managersSalary));
//                manager->setEmployeesSalary(-(this->workersSalary));
//                this->managers.erase(manager);
//            }
    }

    void Workplace::fireManager_clean(int manager_id) {
        if (!isManagerHired(manager_id))
            throw ManagerIsNotHired();

        Manager* manager = FindManager(manager_id);
        manager->setSalary(-((this->managersSalary)));
        manager->setEmployeesSalary(-((this->workersSalary)));
        this->managers.erase(manager);
        manager->clearEmployeeSet();

//        for (Manager* manager : this->managers)
//            if (manager->getId() == manager_id) {
//                manager->setSalary(-(this->managersSalary));
//                manager->setEmployeesSalary(-(this->workersSalary));
//                this->managers.erase(manager);
//                manager->clearEmployeeSet();
//            }
    }


    bool Workplace::isManagerHired(int manager_id) {
        for (Manager* manager : this->managers)
            if (manager->getId() == manager_id)
                return true;
        return false;
    }

    bool Workplace::isEmployeeHired(int employee_id) {
        for (Manager* manager : this->managers)
            if (manager->hasEmployee(employee_id))
                return true;
        return false;
    }

    std::ostream &operator<<(std::ostream &os, const Workplace &workplace) {
        if (!workplace.managers.empty()) {
            os << "Workplace name - " << workplace.name <<" Groups:" << endl;
            for (Manager *manager: workplace.managers) {
                os << "Manager " << manager->getFirstName() << " " << manager->getLastName() << endl;
                os << "id - " << manager->getId() << " birth_year - " << manager->getBirthYear() << endl << "Salary: "
                   << manager->getSalary() << endl;
                os << "Employees: " << endl;
                manager->printEmployees(os);
            }
        }
        else
            os << "Workplace name - " << workplace.getName() << endl;
        return os;
    }

    Manager* Workplace::FindManager(int manager_id) {
        for (Manager* manager: this->managers)
            if (manager->getId() == manager_id)
                return manager;
        return nullptr;
    }
}