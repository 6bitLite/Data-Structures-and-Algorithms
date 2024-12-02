#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>

using namespace std;


struct PasswordEntry {
    string website;
    string username;
    string password;
};


string generatePassword(int length) {
    const string chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*";
    string password = "";
    srand(time(0));

    for (int i = 0; i < length; i++) {
        password += chars[rand() % chars.length()];
    }
    return password;
}


void displayMenu() {
    cout << "1. Generate and Add Password\n";
    cout << "2. View Stored Passwords\n";
    cout << "3. Update Password\n";
    cout << "4. Delete Password\n";
    cout << "5. Exit\n";
    cout << "Choose an option: ";
}


void addPassword(vector<PasswordEntry>& passwordManager) {
    PasswordEntry entry;    
    int passwordLength;
    cout << "\nEnter Website: ";
    cin.ignore(); 
    getline(cin, entry.website);
    cout << "Enter Username: ";
    getline(cin, entry.username);
    cout << "Enter password length: ";
    cin >> passwordLength;
    
    entry.password = generatePassword(passwordLength);
    passwordManager.push_back(entry);
    cout << "Password generated and added successfully!\n";
    cout << "Generated Password: " << entry.password << "\n";
}


void viewPasswords(const vector<PasswordEntry>& passwordManager) {
    if (passwordManager.empty()) {
        cout << "\nNo passwords stored.\n";
        return;
    }
    cout << "\nStored Passwords:\n";
    for (const auto& entry : passwordManager) {
        cout << "Website: " << entry.website 
             << ", Username: " << entry.username 
             << ", Password: " << entry.password << '\n';
    }
}


void updatePassword(vector<PasswordEntry>& passwordManager) {
    string website;
    cout << "\nEnter Website to update password for: ";
    cin.ignore();
    getline(cin, website);

    for (auto& entry : passwordManager) {
        if (entry.website == website) {
            int passwordLength;
            cout << "Enter new password length: ";
            cin >> passwordLength;
            entry.password = generatePassword(passwordLength);
            cout << "Password updated!\n";
            return;
        }
    }
    cout << "Website not found.\n";
}


void deletePassword(vector<PasswordEntry>& passwordManager) {
    string website;
    cout << "\nEnter Website to delete password for: ";
    cin.ignore();
    getline(cin, website);

    for (auto it = passwordManager.begin(); it != passwordManager.end(); ++it) {
        if (it->website == website) {
            passwordManager.erase(it);
            cout << "Password entry deleted successfully!\n";
            return;
        }
    }
    cout << "Website not found.\n";
}


int main() {
    vector<PasswordEntry> passwordManager;
    int choice;

    while (true) {
        displayMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                addPassword(passwordManager);
                break;
            case 2:
                viewPasswords(passwordManager);
                break;
            case 3:
                updatePassword(passwordManager);
                break;
            case 4:
                deletePassword(passwordManager);
                break;
            case 5:
                cout << "Exiting...\n";
                return 0;
            
        }
    }

    return 0;
}
