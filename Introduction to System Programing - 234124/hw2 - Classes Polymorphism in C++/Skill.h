#ifndef SKILL
#define SKILL
#include <string>

/**
 *
 * Represent Skill
 *
 * The following functions are available:
 * getId - returns the id of the skill
 * getName - returns the name of the skill
 * getRequiredPoints - returns the required point an Employee needs to learn the skill
 */
namespace mtm {
    using std::string;

    class Skill {
        int id;
        string name;
        int requiredPoints;

    public:
        Skill() = delete;
        Skill(const Skill &toCopy) {
            this->id = toCopy.getId();
            this->name = toCopy.getName();
            this->requiredPoints = toCopy.getRequiredPoints();
        }
        Skill(int id, string name, int requiredPoints) : id(id), name(name), requiredPoints(requiredPoints) {}
        ~Skill() = default;

        int getId() const;
        string getName() const;
        int getRequiredPoints() const;
        Skill operator++(int);
        Skill& operator+=(int to_add);
        friend std::ostream &operator<<(std::ostream &os, const Skill &skill);
    };

    bool operator<(const Skill &first, const Skill &second);
    bool operator>(const Skill &first, const Skill &second);
    bool operator==(const Skill &first, const Skill &second);
    bool operator!=(const Skill &first, const Skill &second);
    bool operator<=(const Skill &first, const Skill &second);
    bool operator>=(const Skill &first, const Skill &second);
    Skill operator+(const Skill &skill, int to_add);
    Skill operator+(int to_add,const Skill &skill);
}
#endif //SKILL
