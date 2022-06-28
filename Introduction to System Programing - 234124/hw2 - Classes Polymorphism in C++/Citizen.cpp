#include "Citizen.h"
#include "iostream"

namespace mtm {
    using std::cout;
    using std::endl;

    Citizen::Citizen(int id, string firstName, string lastName, int birthYear)  : id(id), firstName(firstName), lastName(lastName), birthYear(birthYear) {}

    int Citizen::getId() const {
        return this->id;
    }

    int Citizen::getBirthYear() const {
        return this->birthYear;
    }

    string Citizen::getFirstName() const {
        return this->firstName;
    }

    string Citizen::getLastName() const {
        return this->lastName;
    }

    bool operator<(const Citizen &first, const Citizen &second) {
        if (first.getId() < second.getId())
            return true;
        return false;
    }

    bool operator>(const Citizen &first, const Citizen &second) {
        if (first.getId() > second.getId())
            return true;
        return false;
    }

    bool operator==(const Citizen &first, const Citizen &second) {
        if (!(first < second) && !(first > second))
            return true;
        return false;
    }

    bool operator!=(const Citizen &first, const Citizen &second) {
        if (first == second)
            return false;
        return true;
    }

    bool operator<=(const Citizen &first, const Citizen &second) {
        if (!(first > second))
            return true;
        return false;
    }

    bool operator>=(const Citizen &first, const Citizen &second) {
        if (!(first < second))
            return true;
        return false;
    }
}
