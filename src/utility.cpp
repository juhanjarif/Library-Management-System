#include "../include/utility.h"
#include "../include/student.h"
#include "../include/staff.h"
#include "../include/librarian.h"
#include <iostream>
#include <iomanip>

using namespace std;

void displayMenu(){
    cout << "Welcome to IUT Library Management System" << endl;
    cout << "1. Register" << endl;
    cout << "2. Login" << endl;
    cout << "3. Exit" << endl;
    cout << endl;
}

void displayUserTypeMenuLogin(){
    cout << "Login as: " << endl;
    cout << "1. Student" << endl;
    cout << "2. Staff" << endl;
    cout << "3. Librarian" << endl;
    cout << endl;
}

void displayUserTypeMenuRegister(){
    cout << "Register as: " << endl;
    cout << "1. Student" << endl;
    cout << endl;
}

void displayStudentFunction(){
    cout << "**Student**" << endl;

    cout << "01. Search Book" << endl;
    cout << "02. Reserve Book" << endl;
    cout << "03. Check Availability of Book" << endl;
    cout << "04. Display All Available Book" << endl;
    cout << "05. Request a Book to Add" << endl;
    cout << "06. Track Due Date" << endl;
    cout << "07. Check Fine Report" << endl;

    cout << endl;
    cout << "99. Update Password" << endl;
    cout << "00. Logout" << endl;
}

void displayStaffFunction(){
    cout << "**Staff**" << endl;

    cout << "01. Search Book" << endl;
    cout << "02. Add Books" << endl;
    cout << "03. Update Books Amount" << endl;
    cout << "04. Issue Book" << endl;
    cout << "05. Return Book" << endl;
    cout << "06. Check Availability of Book" << endl;
    cout << "07. Display All Available Book" << endl;
    cout << "08. Display All Issued Book" << endl;
    cout << "09. Display Reservation Status of a Book" << endl;
    cout << "10. Add New Student" << endl;
    cout << "11. Display All Current Member Students" << endl;
    cout << "12. Generate Fine Report" << endl;

    cout << endl;
    cout << "99. Update Password" << endl;
    cout << "00. Logout" << endl;  
}

void displayLibrarianFunctions(){
    cout << "**Librarian**" << endl;

    cout << "01. Search Book" << endl;
    cout << "02. Add Books" << endl;
    cout << "03. Update Books Amount" << endl;
    cout << "04. Issue Book" << endl;
    cout << "05. Return Book" << endl;
    cout << "06. Check Availability of Book" << endl;
    cout << "07. Display All Available Book" << endl;
    cout << "08. Display All Issued Book" << endl;
    cout << "09. Display Reservation Status of a Book" << endl;
    cout << "10. Delete Book" << endl;
    cout << "11. Add New Student" << endl;
    cout << "12. Add New Staff" << endl;
    cout << "13. Delete Student Account" << endl;
    cout << "14. Delete Staff Account" << endl;
    cout << "15. Display All Current Member Students" << endl;
    cout << "16. Display All Current Member Staffs" << endl;
    cout << "17. Generate Fine Report" << endl;
    cout << "18. Update Librarian Details" << endl;
    cout << "19. Display Librarian Details" << endl;
    
    cout << endl;
    cout << "99. Update Password" << endl;
    cout << "00. Logout" << endl;
}

void handleStudentMenu(){
    student tempStudent;
    librarian tempLibrarian;
    int choice;

    do{
        displayStudentFunction();
        cout << "Enter your choice: ";
        cin >> choice;
        
        switch(choice){
            case 1: 
                tempStudent.searchBookStd();
                break;
            case 2: 
                tempStudent.reserveBookStd();
                break;
            case 3: 
                tempStudent.availabilityBookStd();
                break;
            case 4:
                tempStudent.displayBookStd();
                break;
            case 5: 
                tempStudent.requestBookStd();
                break;
            case 6: 
                tempStudent.trackdueDateStd();
                break;
            case 7:
                tempStudent.generateReportStd();
                break;
            case 99:
                tempStudent.updatePassword();
                break;
            case 0:
                cout << "Logged out!\n" << endl;
                cout << endl;
                return;
            default:
                cout << "Invalid choice!\n" << endl;
        }
    } while(true);
}

void handleStaffMenu(){
    staff tempStaff;
    librarian tempLibrarian;
    int choice;

    do{
        displayStaffFunction();
        cout << "Enter your choice: ";
        cin >> choice;
        
        switch(choice){
            case 1:
                tempStaff.searchBookStaff();
                break;
            case 2:
                tempStaff.newBooksAddStaff();
                break;
            case 3:
                tempStaff.updateBookStaff();
                break;
            case 4:
                tempStaff.issueBookStaff();
                break;
            case 5:
                tempStaff.returnBookStaff();
                break;
            case 6:
                tempStaff.availabilityBookStaff();
                break;
            case 7:
                tempStaff.displayBookStaff();
                break;
            case 8:
                tempStaff.displayIssuedBookStaff();
                break;
            case 9:
                tempStaff.displayReservationStatusStaff();
                break;
            case 10:
                tempStaff.addNewStudentStaff();
                break;
            case 11:
                tempStaff.displayStudentStaff();
                break;
            case 12:
                tempStaff.generateReportStaff();
                break;
            case 99:
                tempStaff.updatePassword();
                break;
            case 0:
                cout << "Logged out!\n" << endl;
                cout << endl;
                return;
            default:
                cout << "Invalid choice!\n" << endl;
        }
    } while(true);
}

void handleLibrarianMenu(){
    librarian tempLibrarian;
    int choice;
    do{
        displayLibrarianFunctions();
        cout << "Enter your choice: ";
        cin >> choice;
        
        switch(choice){
            case 1:
                tempLibrarian.searchBookLib();
                break;
            case 2:
                tempLibrarian.newBooksAddLib();
                break;
            case 3:
                tempLibrarian.updateBookStatusLib();
                break;
            case 4:
                tempLibrarian.issueBookLib();
                break;
            case 5:
                tempLibrarian.returnBookLib();
                break;
            case 6:
                tempLibrarian.availabilityBookLib();
                break;
            case 7:
                tempLibrarian.displayBookLib();
                break;
            case 8:
                tempLibrarian.displayIssuedBookLib();
                break;
            case 9:
                tempLibrarian.displayReservationStatusLib();
                break;
            case 10:
                tempLibrarian.deleteBookLib();
                break;
            case 11:
                tempLibrarian.addNewStudentLib();
                break;
            case 12:
                tempLibrarian.addNewStaffLib();
                break;
            case 13:
                tempLibrarian.deleteStudentLib();
                break;
            case 14:
                tempLibrarian.deleteStaffLib();
                break;
            case 15:
                tempLibrarian.displayStudentLib();
                break;
            case 16:
                tempLibrarian.displayStaffLib();
                break;
            case 17:
                tempLibrarian.generateReportLib();
                break;
            case 18:
                tempLibrarian.updateLibrarianDetails();
                break;
            case 19:
                tempLibrarian.displayLibrarianDetails();
                break;
            case 99:
                tempLibrarian.updatePassword();
                break;
            case 0:
                cout << "Logged out!\n" << endl;
                cout << endl;
                return;
            default:
                cout << "Invalid choice!\n" << endl;
        }
    } while(true);
}