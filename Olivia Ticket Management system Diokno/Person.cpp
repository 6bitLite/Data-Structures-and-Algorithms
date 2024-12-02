#include <string>
using namespace std;

class Person {
public:
    string name;
    string ticket_number;

    Person(string name, string ticket_number) : name(name), ticket_number(ticket_number) {}
};
