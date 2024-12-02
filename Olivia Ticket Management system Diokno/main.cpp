#include <iostream>
#include <string>
#include "Queue.cpp" 

using namespace std;

int main() {
    Queue ticketQueue;
    int choice;
    string input;

    cout << "Welcome to Olivia Rodrigo's Concert Ticketing System!" << endl;
    cout << "\n     1. Enqueue a person\n     2. Check your position in the queue\n     3. Exit\n";

    while (true) {
        cout << "\nChoose an option: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 1:
            cout << "Enter the name: ";
            getline(cin, input);
            ticketQueue.Enqueue(input);
            break;

        case 2:
            cout << "Enter your name or ticket number: ";
            getline(cin, input);
            ticketQueue.Position(input);
            break;

        case 3:
            cout << "Exiting system." << endl;
            return 0;

        default:
            cout << "Invalid option. Please try again." << endl;
        }

        if (ticketQueue.Size() == 3) {
            ticketQueue.AutoDequeue(true);
        }
    }

    return 0;
}
