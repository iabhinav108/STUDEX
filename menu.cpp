#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <unordered_map>
#include "menu.h"

using namespace std;

struct Student {
    string enrollment;
    string firstName;
    string lastName;
    string email;
    string phone;
};
vector<Student> students;
unordered_map<string, Student> studentMap;

void loadStudentData() {
    ifstream file("student.txt");
    string line;

    while (getline(file, line)) {
        istringstream iss(line);
        Student student;
        iss >> student.enrollment >> student.firstName >> student.lastName >> student.email >> student.phone;
        students.push_back(student);
        studentMap[student.enrollment] = student;
    }
    file.close();
}

void saveStudentData() {
    ofstream file("student.txt");
    for (const Student& student : students) {
        file << student.enrollment << " " << student.firstName << " " << student.lastName << " " << student.email << " " << student.phone << "\n";
    }
    file.close();
}

void showMenu(const UserData& user) {
    loadStudentData();

    int choice;
    while (true) {
        cout << "\nStudent Details Menu\n";
        cout << "1. Search Student Details\n";
        cout << "2. Add Student Details\n";
        cout << "3. Delete Student Details\n";
        cout << "4. Modify Student Details\n";
        cout << "5. Back to Main Menu\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                searchStudentDetails();
                break;
            case 2:
                addStudentDetails();
                break;
            case 3:
                deleteStudentDetails();
                break;
            case 4:
                modifyStudentDetails();
                break;
            case 5:
                saveStudentData();
                cout << "-------------------------------------"<<endl;
                cout << "\nThank you for using STUDEX\n";
                cout << "This project was created as part of academic work for CSET:202 Data Structures Using C++ by: "<<endl;
                cout << "1. Abhinav Srivastava"<<endl;
                cout << "2. V Harshath"<<endl;
                cout << "3. Aadarsh Singh Tomar"<<endl;
                return;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    }
}

void searchStudentDetails() {
    string query;
    cout << "Enter Enrollment Number to search: ";
    cin.ignore();
    getline(cin, query);

    auto it = studentMap.find(query);
    if (it != studentMap.end()) {
        const Student& student = it->second;
        cout << "Student Details Found:\n";
        cout << "Enrollment Number: " << student.enrollment << "\n";
        cout << "First Name: " << student.firstName << "\n";
        cout << "Last Name: " << student.lastName << "\n";
        cout << "Email: " << student.email << "\n";
        cout << "Phone: " << student.phone << "\n";
    } else {
        cout << "Student not found.\n";
    }
}

void addStudentDetails() {
    Student student;
    cout << "Enter Student Details:\n";
    cout << "Enrollment Number: ";
    cin >> student.enrollment;
    cout << "First Name: ";
    cin >> student.firstName;
    cout << "Last Name: ";
    cin >> student.lastName;

    while (true) {
        cout << "Email: ";
        cin >> student.email;
        if (student.email.find('@') == string::npos) {
            cout << "Email must contain '@'. Please re-enter.\n";
        } else {
            break;
        }
    }

    while (true) {
        cout << "Contact Number: ";
        cin >> student.phone;
        if (student.phone.length() != 10 || !all_of(student.phone.begin(), student.phone.end(), ::isdigit)) {
            cout << "Invalid phone number. Please re-enter with exactly 10 digits.\n";
        } else {
            break;
        }
    }

    students.push_back(student);
    studentMap[student.enrollment] = student;
    cout << "Student Details added successfully.\n";
}

void deleteStudentDetails() {
    string query;
    cout << "Enter Enrollment Number, First Name, or Last Name to delete: ";
    cin.ignore();
    getline(cin, query);

    auto it = studentMap.find(query);
    if (it != studentMap.end()) {
        studentMap.erase(it);
        students.erase(remove_if(students.begin(), students.end(),
                                 [query](const Student& student) {
                                     return student.enrollment == query;
                                 }), students.end());
        cout << "Student Details deleted successfully.\n";
    } else {
        cout << "Student not found.\n";
    }
}

void modifyStudentDetails() {
    string query;
    cout << "Enter Enrollment Number, First Name, or Last Name to modify: ";
    cin.ignore();
    getline(cin, query);

    auto it = studentMap.find(query);
    if (it != studentMap.end()) {
        Student& student = it->second;
        cout << "Enter new Student Details:\n";
        cout << "First Name: ";
        cin >> student.firstName;
        cout << "Last Name: ";
        cin >> student.lastName;
        cout << "Email: ";
        cin >> student.email;
        cout << "Phone: ";
        cin >> student.phone;
        cout << "Student Details modified successfully.\n";
    } else {
        cout << "Student not found.\n";
    }
}

