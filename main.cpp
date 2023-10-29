#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <sstream>
#include "menu.h"

using namespace std;

map<string, UserData> users;

void loadUserData() {
    ifstream file("secure.txt");
    string line;

    while (getline(file, line)) {
        istringstream iss(line);
        string enrollment, name, password, role;
        iss >> enrollment >> name >> password >> role;
        users[enrollment] = {name, password, role};
    }
    file.close();
}

void saveUserData() {
    ofstream file("secure.txt");
    for (const auto& user : users) {
        file << user.first << " " << user.second.name << " " << user.second.password << " " << user.second.role << "\n";
    }
    file.close();
}

void signUp() {
    string enrollment, name, password, role;

    cout << "Enter Enrollment/ID Number: ";
    cin >> enrollment;

    if (users.find(enrollment) != users.end()) {
        cout << "Enrollment/ID Number already exists. Please check your credentials.\n";
        return;
    }

    cout << "Enter Name: ";
    cin.ignore();
    getline(cin, name);

    cout << "Enter Password: ";
    cin >> password;

    cout << "Enter Role (student/faculty/supporting staff): ";
    cin >> role;

    users[enrollment] = {name, password, role};
    saveUserData();

    cout << "Successfully registered. You can now log in.\n";
    showMenu(users[enrollment]);
}

void login() {
    string enrollment, password;

    cout << "Enter Enrollment/ID Number: ";
    cin >> enrollment;

    cout << "Enter Password: ";
    cin >> password;

    if (users.find(enrollment) != users.end() && users[enrollment].password == password) {
        cout << "Successfully logged in.\n";
        showMenu(users[enrollment]);
    } else {
        cout << "Incorrect enrollment number or password. Please try again.\n";
    }
}

int main() {
    loadUserData();

    cout << "Welcome to the STUDEX: The University Address Book\n";
    cout << "---------------------------------------"<<endl;
    cout << "1. Sign Up\n";
    cout << "2. Login\n";

    int choice;
    cout << "Enter your choice: ";
    cin >> choice;

    if (choice == 1) {
        signUp();
    } else if (choice == 2) {
        login();
    } else {
        cout << "Invalid choice. Exiting...\n";
    }

    return 0;
    
}
