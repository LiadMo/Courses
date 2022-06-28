#include "Skill.h"
#include "iostream"
#include "exceptions.h"

using std::cout;
using std::endl;
namespace mtm {

    int Skill::getId() const {
        return this->id;
    }

    string Skill::getName() const {
        return this->name;
    }

    int Skill::getRequiredPoints() const {
        return this->requiredPoints;
    }

    std::ostream &operator<<(std::ostream &os, const Skill &skill) {
        os << skill.name << endl;// old: << " level: " << skill.requiredPoints << endl;
        return os;
    }

    bool operator<(const Skill &first, const Skill &second) {
        if (first.getId() < second.getId())
            return true;
        return false;
    }

    bool operator>(const Skill &first, const Skill &second) {
        if (first.getId() > second.getId())
            return true;
        return false;
    }

    bool operator==(const Skill &first, const Skill &second) {
        if (!(first < second) && !(first > second))
            return true;
        return false;
    }

    bool operator!=(const Skill &first, const Skill &second) {
        if (first == second)
            return false;
        return true;
    }

    bool operator<=(const Skill &first, const Skill &second) {
        if (!(first > second))
            return true;
        return false;
    }

    bool operator>=(const Skill &first, const Skill &second) {
        if (!(first < second))
            return true;
        return false;
    }

    Skill operator+(const Skill &skill, int to_add) {
        if (to_add < 0)
            throw mtm::NegativePoints();
        Skill s(skill.getId(), skill.getName(),skill.getRequiredPoints() + to_add);
        return s;
    }

    Skill operator+(int to_add,const Skill &skill) {
        return skill + to_add;
    }

    Skill Skill::operator++(int) {
        Skill copy = *this;
        this->requiredPoints+=1;
        return copy;
    }

    Skill &Skill::operator+=(int to_add) {
        if (to_add < 0)
            throw mtm::NegativePoints();
        this->requiredPoints = this->requiredPoints + to_add;
        return *this;
    }
}
