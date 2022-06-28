#ifndef FACULTY
#define FACULTY
#include "Skill.h"
#include "Employee.h"
#include "exceptions.h"

/**
*
* Represent Faculty
*
* The following functions are available:
* getSkill - returns the skill learnt in the faculty
 * getId - returns the id
 * gerAddedPoints - returns the amount of points an employee gets for learning the skill
 * teach - if an employee is able to learn the skill, the skill is added to his set
*/
 //TODO: check if we can implement the methods in .cpp file
 namespace mtm {
     class Condition{
     public:
         virtual bool operator()(Employee* employee) = 0;
     };

     template<class Condition>
     class Faculty {
         Condition* condition;
         int id;
         Skill skill;
         int addedPoints;

     public:
         Faculty() = delete;
         Faculty(int id, Skill &skill, int addedPoints, Condition* condition) : condition(condition), id(id),skill(skill), addedPoints(addedPoints) {}
         Faculty(const Faculty& faculty) = default;
         ~Faculty() = default;

         Skill getSkill() {
             return this->skill;
         }
         int getId() {
             return this->id;
         }
         int getAddedPoints() {
             return this->addedPoints;
         }

         void teach(Employee* employee) {
             if(!(*condition)(employee))
                 throw EmployeeNotAccepted();
             employee->learnSkill(this->skill);
             employee->setScore(this->addedPoints);
         }
     };
 }



#endif //FACULTY
