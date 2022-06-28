#ifndef EXCEPTIONS
#define EXCEPTIONS
#include <exception>

namespace mtm {
    class Exception : public std::exception {
    };

    class NegativePoints : public Exception {
    };

    class SkillAlreadyLearned : public Exception {
    };

    class CanNotLearnSkill : public Exception {
    };

    class DidNotLearnSkill : public Exception {
    };

    class EmployeeNotAccepted : public Exception {
    };

    class EmployeeAlreadyExists : public Exception {
    };

    class EmployeeAlreadyHired : public Exception {
    };

    class EmployeeIsNotHired : public Exception {
    };

    class EmployeeNotSelected : public Exception {
    };

    class ManagerIsNotHired : public Exception {
    };

    class ManagerAlreadyHired : public Exception {
    };

    class CanNotHireManager : public Exception {
    };

    class CitizenAlreadyExists : public Exception {

    };

    class FacultyAlreadyExists : public Exception {

    };

    class WorkplaceAlreadyExists : public Exception {

    };

    class EmployeeDoesNotExist : public Exception {

    };

    class FacultyDoesNotExist : public Exception {

    };

    class ManagerDoesNotExist : public Exception {

    };

    class WorkplaceDoesNotExist : public Exception {

    };
}

#endif