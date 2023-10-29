#pragma once

#include "main.h" // Include any other necessary headers

struct UserData {
    std::string name;
    std::string password;
    std::string role;
};

void showMenu(const UserData& user);
void searchStudentDetails();
void addStudentDetails();
void deleteStudentDetails();
void modifyStudentDetails();
