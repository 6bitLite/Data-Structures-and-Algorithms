#include <iostream>
using namespace std;

int main() {
    float num1, num2;
    char operation;

    
        cout << "Enter num: ";
        cin >> num1;
        cout << "Enter another num: ";
        cin >> num2;

        cout << "Enter Operation: ";
        cin >> operation;

        switch (operation)
        {
        case '+':       
            cout <<"Result: " << num1 + num2 << endl;
            break;
        case '-':       
            cout <<"Result: " << num1 - num2 << endl;
            break;
        case '*':       
            cout <<"Result: " << num1 * num2 << endl;
            break;
        case '/':
        if (num1 !=0)
            cout << "Result: " << num1 / num2 << endl;
        else
            cout <<"Error: that is not allowed! " << endl;
            break;

        default:
            break;
            
    }
    return 0;
}



