#include "../include/librarian.h"
#include "../include/staff.h"
#include "../include/student.h"
#include "../include/hashutil.h"
#include <fstream>
#include <sstream>
#include <iomanip>

using namespace std;

librarian::librarian() : user(){}

librarian::librarian(string username, string password, string name, string dept, string programme, string contact) : user(username, password, name, dept, programme, contact) {}

librarian::~librarian(){}

void librarian::registerUser(){}

bool librarian::loginUser(){
    ifstream file("librarianInfo.csv");

    string line, userid, pass;
    bool found = false;

    cout << "Enter Username: ";
    cin >> userid;
    cout << "Enter Password: ";
    cin >> pass;

    string hashedPass = customHash(pass);

    while(getline(file, line)){
        stringstream ss(line);
        string username, storedHashedPassword;

        getline(ss, username, ',');
        getline(ss, storedHashedPassword, ',');

        if(userid == username && hashedPass == storedHashedPassword){
            found = true;
            break;
        }
    }
    if(found){
        cout << "Login Successful!\n" << endl;
        cout << endl;
        return true;
    }
    else{
        cout << "Login Failed!\n" << endl;
        cout << endl;
        return false;
    }
}

void librarian::updatePassword(){
    ifstream file("librarianInfo.csv");
    ofstream outFile("templibrarianInfo.csv");

    string line, userid, pass, newPass;
    bool found = false;

    if(!file.is_open() || !outFile.is_open()){
        cout << "Error: Updating Password!\n" << endl;
        return;
    }

    cout << "Enter Username: ";
    cin.ignore();
    cin >> userid;
    cout << "Enter Previous Password: ";
    cin >> pass;

    string hashedPass = customHash(pass);

    while(getline(file, line)){
        if(line.find(',') == string::npos)
            continue;

        stringstream ss(line);
        string username, storedHashedPassword;

        getline(ss, username, ',');
        getline(ss, storedHashedPassword, ',');

        if(userid == username && hashedPass == storedHashedPassword){
            found = true;
            cout << "Enter your new Password:";
            cin >> newPass;
            storedHashedPassword = customHash(newPass);
        }

        outFile << username << "," << storedHashedPassword << "," << "\n";
    }

    file.close();
    outFile.close();

    if(found)
        cout << "\nPassword updated successfully!\n" << endl;
    else
        cout << "\nIncorrect Password!\nTry Again!\n" << endl;

    remove("librarianInfo.csv");
    rename("templibrarianInfo.csv", "librarianInfo.csv");
}

void librarian::updateLibrarianDetails(){
    ifstream file("librarianInfo.csv");
    ofstream outfile("templibrarianInfo.csv");

    string line, userid, pass;
    bool found = false;

    if(!file.is_open() || !outfile.is_open()){
        cout << "Error: Updating Librarian Details!\n" << endl;
        return;
    }

    cout << "Enter Username: ";
    cin >> userid;
    cout << "Enter Password: ";
    cin >> pass;
    pass=customHash(pass);

    while(getline(file, line)){
        if(line.find(',') == string::npos)
            continue;

        stringstream ss(line);
        string username, password, fullName, contact;

        getline(ss, username, ',');
        getline(ss, password, ',');
        getline(ss, fullName, ',');
        getline(ss, contact, ',');

        if(userid == username && pass == password){
            found = true;
            cout << "Enter your Full Name: ";
            cin.ignore();
            getline(cin, fullName);
            cout << "Enter you contact: ";
            getline(cin, contact);
        }

        outfile << username << "," << password << "," << fullName << "," << contact << "\n";
    }

    file.close();
    outfile.close();

    if(found)
        cout << "Librarian Details updated successfully!\n" << endl;
    else
        cout << "Incorrect Password!\nTry Again!\n" << endl;

    remove("librarianInfo.csv");
    rename("templibrarianInfo.csv", "librarianInfo.csv");
}

void librarian::displayLibrarianDetails(){
    ifstream file("librarianInfo.csv");

    string line;

    if(!file.is_open()){
        cout << "Error: Displaying Librarian Details!\n" << endl;
        return;
    }

    cout << "Librarian Details:" << endl;
    while(getline(file, line)){
        if(line.find(',') == string::npos)
            continue;

        stringstream ss(line);
        string username, password, fullName, contact;

        getline(ss, username, ',');
        getline(ss, password, ',');
        getline(ss, fullName, ',');
        getline(ss, contact, ',');

        cout << left << setw(30) << "Name: " + fullName << " | " << setw(15) << "Contact Info: " + contact << endl;
    }

    cout << endl;

    file.close();
}

//01. Search Book
void librarian::searchBookLib(){
    book search;
    search.searchBook();
}

//02. Add Books
void librarian::newBooksAddLib(){
    book newBook;
    newBook.addBook();
}

//03. Update Books
void librarian::updateBookStatusLib(){
    book updateBook;
    updateBook.updateBookQuantity();
}

//04. Issue Book
void librarian::issueBookLib(){
    book issuebooks;
    issuebooks.issueBook();
}

//05. Return Book
void librarian::returnBookLib(){
    book returnBook;
    returnBook.returnBook();
}

//06. Check Availability of Book
void librarian::availabilityBookLib(){
    book availableBook;
    availableBook.searchBook();
}

//07. Display All Available Book
void librarian::displayBookLib(){
    book disBook;
    disBook.displayAllBooks();
}

//08. Display All Issued Book
void librarian::displayIssuedBookLib(){
    book issuedBook;
    issuedBook.displayAllIssuedBook();
}

//09. Display Reservation Status of a Book
void librarian::displayReservationStatusLib(){
    book resStatusBook;
    resStatusBook.displayReservationStatus();
}

//10. Delete Book
void librarian::deleteBookLib(){
    book delBook;
    delBook.deleteBook();
}

//11. Add New Student
void librarian::addNewStudentLib(){
    student newStudent;
    newStudent.registerUser();
}

//12. Add New Staff
void librarian::addNewStaffLib(){
    staff newStaff;
    newStaff.registerUser();
}

//13. Delete Student Account
void librarian::deleteStudentLib(){
    student delStudent;
    delStudent.deleteMemberStudent();
}

//14. Delete Staff Account
void librarian::deleteStaffLib(){
    staff delStaff;
    delStaff.deleteMemberStaff();
}

//15. Display All Current Member Students
void librarian::displayStudentLib(){
    student displayStudent;
    displayStudent.displayAllMemberStudent();
}

//16. Display All Current Member Staffs
void librarian::displayStaffLib(){
    staff displayStaff;
    displayStaff.displayAllMemberStaff();
}

//17. Generate Fine Report
void librarian::generateReportLib(){
    book report;
    report.generateFineReport();
}