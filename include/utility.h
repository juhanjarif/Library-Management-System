#ifndef UTILITY_H
#define UTILITY_H

#include "user.h"
#include "student.h"
#include "staff.h"
#include "librarian.h"

using namespace std;

void displayMenu();
void displayUserTypeMenuLogin();
void displayUserTypeMenuRegister();
void displayStudentFunction();
void displayStaffFunction();
void displayLibrarianFunctions();
void handleStudentMenu();
void handleStaffMenu();
void handleLibrarianMenu();

#endif
