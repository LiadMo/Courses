#ifndef CITIZEN
#define CITIZEN
#include <string>


/**
 *
 * Represent Citizen ** abstract ** object
 *
 * The following functions are available:
 *
 * getId              - Return the ID of a Order
 * getFirstName       - Return the first name
 * getLastName        - Return the last name
 * getBirthYear       - return the birthday year
 * getSalary          - Pure virtual function, return the salary of the object
 * printShort         - Pure virtual function, return ostream object with the short blueprint of the object
 * printLong          - Pure virtual function, return ostream object with the long blueprint of the object
 * clone              - return a new copy of an object (allocate new memory)
 */


namespace mtm {
    using std::string;
    using std::ostream;

    class Citizen {
        int id;
        string firstName;
        string lastName;
        int birthYear;


    public:
        Citizen() = delete;
        Citizen(const Citizen &toCopy) = default;
        Citizen(int id, string firstName, string lastName, int birthYear);
        virtual ~Citizen() = default;

        // methods
        /**
         * getId
         * @return - the ID of a Order
         */
        int getId() const;

        /**
         * getFirstName
         * @return - the first name
         */
        string getFirstName() const;

        /**
         * getLastName
         * @return - the last name
         */
        string getLastName() const;

        /**
         * getBirthYear
         * @return - the birthday year
         */
        int getBirthYear() const;

        /**
         * getSalary - Pure virtual function
         * @return - the salary of the object
         */
        virtual int getSalary() const = 0;

        /**
         * printShort - Pure virtual function, print in os object the blueprint
         * @param os - ostream object
         * @return - short blueprint of the object
         */
        virtual ostream& printShort(ostream& os) = 0;

        /**
         * printLong - Pure virtual function, print in os object the blueprint
         * @param os - ostream object
         * @return - short blueprint of the object
         */
        virtual ostream& printLong(ostream& os) = 0;

        /**
         * clone - Pure virtual function, copy an element
         * @return new copy of an object
         */
        virtual Citizen *clone() const = 0;
    };

    // overloading operators functions
    bool operator<(const Citizen &first, const Citizen &second);
    bool operator>(const Citizen &first, const Citizen &second);
    bool operator==(const Citizen &first, const Citizen &second);
    bool operator!=(const Citizen &first, const Citizen &second);
    bool operator<=(const Citizen &first, const Citizen &second);
    bool operator>=(const Citizen &first, const Citizen &second);
}

#endif //CITIZEN
