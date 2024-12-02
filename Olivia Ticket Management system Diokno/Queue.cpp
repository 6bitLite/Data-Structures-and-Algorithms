#include <iostream>
#include <queue>
#include "Person.cpp" 

using namespace std;

class Queue {
private:
    queue<Person> q;
    int next_ticket_number;

public:
    Queue() : next_ticket_number(1) {}

    void Enqueue(string name) {
        string ticket = FormatTicketNumber(next_ticket_number++);
        Person new_person(name, ticket);
        q.push(new_person);
        cout << name << " added to the queue with Ticket #" << ticket << endl;
        cout << "Queue size: " << Size() << endl;
    }

    void AutoDequeue(bool is_manual = false) {
        if (is_manual) {
            cout << "\nAfter 1 minute..." << endl;
        }

        if (!IsEmpty()) {
            Person p = q.front();
            q.pop();
            cout << "Dequeue: " << p.name << " received a ticket (Ticket #" << p.ticket_number << ")" << endl;
            cout << "Queue size: " << Size() << endl;

            if (!IsEmpty()) {
                Peek();
            }
        }
        else {
            cout << "Queue is empty!" << endl;
        }
    }

    bool IsEmpty() {
        return q.empty();
    }

    int Size() {
        return q.size();
    }

    void Peek() {
        if (!IsEmpty()) {
            Person next_person = q.front();
            cout << "Next in line: " << next_person.name << " (Ticket #" << next_person.ticket_number << ")" << endl;
        }
    }

    void Position(string input) {
        int position = 1;
        queue<Person> temp_queue = q;
        bool found = false;

        while (!temp_queue.empty()) {
            Person p = temp_queue.front();
            temp_queue.pop();

            if (p.name == input || p.ticket_number == input) {
                found = true;
                break;
            }
            position++;
        }

        if (found) {
            cout << input << " is currently at position " << position << " in the queue." << endl;
        }
        else {
            cout << input << " not found in the queue." << endl;
        }
    }

private:
    string FormatTicketNumber(int number) {
        char buffer[4];
        snprintf(buffer, sizeof(buffer), "%03d", number);
        return string(buffer);
    }
};
