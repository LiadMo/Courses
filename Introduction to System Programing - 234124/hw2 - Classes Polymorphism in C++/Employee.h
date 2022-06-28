#ifndef EMPLOYEE
#define EMPLOYEE
#include <string>
#include <set>
#include "Skill.h"
#include "Citizen.h"
#include <iostream>
#include "ComparePointers.h"


/**
 *
 * Represent Employee object (extends Citizen class)
 *
 * The following functions are available:
 *
 * Employee           - Return a new object of employee - c'tor
 * getId              - Return the ID of a Order
 * getFirstName       - Return the first name
 * getLastName        - Return the last name
 * getBirthYear       - return the birthday year
 * getScore           - return the score
 * getSalary          - return the salary
 * setSalary
 * setScore
 * hasSkill
 * learnSkill
 * forgetSkill
 * printShort         - return ostream object with the short blueprint
 * printLong          - return ostream object with the long blueprint
 * clone              - return a new copy of an employee (allocate new memory)
 */


namespace mtm {
    using std::set;
    using std::string;

    class Employee : public Citizen {
        int salary;
        int score;
        set<Skill> skills;

    public:
        Employee() = delete;

        /**
         * Employee(const Employee &toCopy) - copy c'tor
         * @param toCopy - another employee to copy
         */
        Employee(const Employee &toCopy) = default;

        /**
         * Employee(int id, string firstName, string lastName, int birthYear) - c'tor
         * @param id - employee id
         * @param firstName  - employee first mame
         * @param lastName - employee lase name
         * @param birthYear - employee birth year
         */
        Employee(int id, string firstName, string lastName, int birthYear);

        // member function

        /**
         * getScore
         * @return - the score of employee
         */
        int getScore() const;

        /**
         * getSalary
         * @return - the salary of employee
         */
        int getSalary() const override;

        /**
         * setSalary - set the sum to add / dec from employee salary
         * @param toAdd - the sum to add / dec from employee salary
         */
        void setSalary(int toAdd);

        /**
         * setScore - set the sum to add / dec from employee score
         * @param toAdd - the sum to add / dec from enployee score
         */
        void setScore(int toAdd);

        /**
         * hasSkill - check if employee have skill
         * @param skill_id  - the skill ID
         * @return - Return true if the employee has the skill, else return false
         */
        bool hasSkill(int skill_id);

        /**
         * learnSkill - tech the employee skill
         * @param skill - the skill to learn
         */
        void learnSkill(Skill& skill);

        /**
         * forgetSkill- delete the skill from, the employee
         * @param skill_id - the skill ID to forget
         */
        void forgetSkill(int skill_id);

        /**
         * printShort - return os with short blueprint
         * @param os - Ostream
         * @return Ostream
         */
        std::ostream& printShort(std::ostream &os) override;

        /**
         * printShort - return os with long blueprint
         * @param os -Ostream
         * @return Ostream
         */
        std::ostream& printLong(std::ostream &os) override;

        /**
         * clone - copy an Employee
         * @return - a new Employee
         */
        Employee* clone() const override;
    };
}
#endif //EMPLOYEE
