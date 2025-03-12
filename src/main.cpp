//Project Name: Library Management System LMS
//Team 08
//Semester 01 Year 02 
//Department CSE Programme CSE
//Islamic University Of Technology IUT

#include <iostream>
#include "../include/student.h"
#include "../include/staff.h"
#include "../include/librarian.h"
#include "../include/utility.h"

using namespace std;

int main(){
    while(true){
        int input, usertype;
        displayMenu();
        cout << "Enter your choice: ";
        cin >> input;

        if(input == 1)
            displayUserTypeMenuRegister();
        else if(input == 2)
            displayUserTypeMenuLogin();
        else if(input == 3)
            break;
        else{
            cout << "Invalid Input!" << endl;
            continue;
        }

        cout << "Enter user type: ";
        cin >> usertype;

        user* tempUser = nullptr;
        
        if(input == 1){
            if(usertype == 1){
                tempUser = new student();
                tempUser->registerUser();
                delete tempUser;
            }
            else
                cout << "Invalid registration type!" << endl;
        }
        else if(input == 2){ 
            switch(usertype){
                case 1:
                    tempUser = new student();
                    if(tempUser->loginUser())
                        handleStudentMenu();
                    else{
                        delete tempUser;
                        tempUser = nullptr;
                        return main(); 
                    }
                    break;
                case 2:
                    tempUser = new staff();
                    if(tempUser->loginUser())
                        handleStaffMenu();
                    else{
                        delete tempUser;
                        tempUser = nullptr;
                        return main(); 
                    }
                    break;
                case 3:
                    tempUser = new librarian();
                    if(tempUser->loginUser())
                        handleLibrarianMenu();
                    else{
                        delete tempUser;
                        tempUser = nullptr;
                        return main(); 
                    }
                    break;
                default:
                    cout << "Invalid user type!" << endl;
            }
            delete tempUser;
        }
    }
    return 0;
}

//Team Members:
// 220041214    Juhan Ahmed 
// 220041218    Abrar Shahriar
// 220041236    Md Adnan Samir
// 220041240    Farhan Ishraq Ayon 

//IUT CSE'22