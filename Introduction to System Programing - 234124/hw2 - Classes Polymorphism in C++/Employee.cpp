#include <string>
#include "Skill.h"
#include "Employee.h"
#include "exceptions.h"


namespace mtm {
    using std::string;
    using std::cout;
    using std::endl;

    Employee::Employee(int id, string firstName, string lastName, int birthYear) :
            Citizen(id, firstName, lastName, birthYear),salary(0), score(0), skills() {}

    int Employee::getSalary() const {
        return this->salary;
    }

    int Employee::getScore() const {
        return this->score;
    }

    void Employee::learnSkill(Skill& skill) {
        if (this->hasSkill(skill.getId()))
            throw SkillAlreadyLearned();

        if (this->score < skill.getRequiredPoints())
            throw mtm::CanNotLearnSkill();

        this->skills.insert(skill);
    }

    void Employee::forgetSkill(int skill_id) {
        for (Skill skill_iterator : this->skills) {
            if (skill_iterator.getId() == skill_id){
                this->skills.erase(skill_iterator);
                return;
            }
        }
        throw mtm::DidNotLearnSkill();

//        if (!this->hasSkill(skill_id))
//            throw mtm::DidNotLearnSkill();
//        for(Skill skill_iter : this->skills)
//            if(skill_iter.getId() == skill_id)
//                this->skills.erase(skill_iter);
    }


    bool Employee::hasSkill(int skill_id) {
        for (const Skill& skill_iterator : this->skills)
            if (skill_iterator.getId() == skill_id)
                return true;

        return false;
    }

    void Employee::setSalary(int toAdd) {
        this->salary += toAdd;
        if (this->salary < 0)
            this->salary = 0;
    }

    void Employee::setScore(int toAdd) {
        this->score += toAdd;
        if (this->score < 0)
            this->score = 0;
    }

    Employee* Employee::clone() const {
        return new Employee(*this);
    }

    std::ostream &Employee::printShort(std::ostream &os) {
        os << this->getFirstName() << " " << this->getLastName() << endl;
        os << "Salary: " << this->salary << " Score: " << this->getScore() << endl;
        return os;
    }

    std::ostream &Employee::printLong(std::ostream &os) {
        os << this->getFirstName() << " " << this->getLastName() << endl;
        os << "id - " << this->getId() << " birth_year - " << this->getBirthYear() << endl;
        if (!this->skills.empty()) {
            os << "Salary: " << this->salary << " Score: " << this->getScore() << " Skills: " << endl;
            for (const Skill& skill_iterator: this->skills)
                os << skill_iterator.getName() << endl;
        }
        else
            os << "Salary: " << this->salary << " Score: " << this->getScore() << endl;

        return os;
    }
}
