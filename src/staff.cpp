#include "../include/staff.h"
#include "../include/hashutil.h"
#include <fstream>
#include <sstream>
#include <iomanip>

using namespace std;

staff::staff() : user() {}

staff::staff(string username, string password, string name, string dept, string programme, string contact) : user(username, password, fullName, department, programme, contact) {}

staff::~staff() {}

void staff::registerUser(){
    ifstream readFile("staffInfo.csv");
    ofstream file("staffInfo.csv", ios::app);

    string line, userid;
    bool userNameExists = false;

    if(!file.is_open() || !readFile.is_open()){
        cout << "Error: Registering Staff!\n" << endl;
        return;
    }

    cout << "Enter Personal Details. If any field is not applicable then enter N/A." << endl;

    cout << "Enter Name: ";
    cin.ignore();
    getline(cin, fullName);

    cout << "Enter Contact: ";
    cin >> contact;

    cout << "Create you Username: ";
    cin >> username;

    while(getline(readFile, line)){
        stringstream ss(line);
        getline(ss, userid, ',');

        if(userid == username){
            userNameExists = true;
            break;
        }
    }
    readFile.close();

    if(userNameExists){
        cout << "Error: Username already exists!\nEnter a valid username!\n" << endl;
        return;
    }

    cout << "Create a Password: ";
    cin >> password;

    string hashedPassword = customHash(password);

    file << username << "," << hashedPassword << "," << fullName << "," << contact << "\n";

    cout << "Staff Added Successful!" << endl;
    cout << endl;

    file.close();
    
}

bool staff::loginUser(){
    ifstream file("staffInfo.csv");

    string line, userid, pass;
    bool found = false;

    cout << "Enter Username: ";
    cin >> userid;
    cout << "Enter Password: ";
    cin >> pass;

    string hashedPass = customHash(pass);

    while(getline(file, line)){
        if(line.find(',') == string::npos) 
            continue;

        stringstream ss(line);
        string username, storedHashedPassword;

        getline(ss, username, ',');
        getline(ss, storedHashedPassword, ',');
        
        if(userid == username && hashedPass  == storedHashedPassword){
            found = true;
            break;
        }
    }
    if(found){
        cout << "Login Successful!" << endl;
        cout << endl;
        return true;
    } 
    else{
        cout << "Login Failed!" << endl;
        cout << endl;
        return false;
    }
}

void staff::updatePassword(){
    ifstream file("staffInfo.csv");
    ofstream outFile("tempstaffInfo.csv");

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
        string username, storedHashedPassword, fullName, contact;

        getline(ss, username, ',');
        getline(ss, storedHashedPassword, ',');
        getline(ss, fullName, ',');
        getline(ss, contact, ',');

        if(userid == username && hashedPass  == storedHashedPassword){
            found = true;
            cout << "Enter your new Password:";
            cin >> newPass;

            string newHashedPass = customHash(newPass);
            storedHashedPassword = newHashedPass;
        }

        outFile << username << "," << storedHashedPassword << "," << fullName << "," << contact << "\n";
    }

    file.close();
    outFile.close();

    if(found)
        cout << "Password updated successfully!\n" << endl;
    else
        cout << "Incorrect Password!\nTry Again!\n" << endl;

    remove("staffInfo.csv");
    rename("tempstaffInfo.csv", "staffInfo.csv");
}

void staff::displayAllMemberStaff(){
    ifstream file("staffInfo.csv");
    string line;

    if(!file.is_open()){
        cout << "Error: Displaying Staff List!" << endl;
        return;
    }

    cout << "\nList of Current Staff:" << endl;
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

void staff::deleteMemberStaff(){
    ifstream file("staffInfo.csv");
    ofstream tempfile("temp.csv");
    string line, username;
    bool isDeletedMember = false;

    if(!file.is_open() || !tempfile.is_open()){
        cout << "Error: Deleting Staff!\n" << endl;
        return;
    }

    cout << "Enter the User Name: ";
    cin >> username;

    while(getline(file, line)){
        stringstream ss(line);
        string userID;

        getline(ss, userID, ',');

        if(userID == username){
            isDeletedMember = true;
            continue;
        }
        tempfile << line << "\n";
    }

    file.close();
    tempfile.close();

    remove("staffInfo.csv");
    rename("temp.csv", "staffInfo.csv");

    if(isDeletedMember)
        cout << "Staff Memeber list was just updated as UserID: " << username << " was deleted successfully!" << endl;
    else
        cout << "Staff with UserID " << username << " couldnot be found!" << endl;
}

//01. Search Book
void staff::searchBookStaff(){
    book search;
    search.searchBook();
}

//02. Add Books
void staff::newBooksAddStaff(){
    book newBook;
    newBook.addBook();
}

//03. Update Books
void staff::updateBookStaff(){
    book updateBook;
    updateBook.updateBookQuantity();
}

//04. Issue Book
void staff::issueBookStaff(){
    book issueBook;
    issueBook.issueBook();
}

//05. Return Book
void staff::returnBookStaff(){
    book returnBook;
    returnBook.returnBook();
}

//06. Check Availability of Book
void staff::availabilityBookStaff(){
    book availableBook;
    availableBook.searchBook();
}

//07. Display All Available Book
void staff::displayBookStaff(){
    book displayBook;
    displayBook.displayAllBooks();
}

//08. Display All Issued Book
void staff::displayIssuedBookStaff(){
    book issuedBook;
    issuedBook.displayAllIssuedBook();
}

//09. Display Reservation Status of a Book
void staff::displayReservationStatusStaff(){
    book resStatusBook;
    resStatusBook.displayReservationStatus();
}

//10. Add New Student
void staff::addNewStudentStaff(){
    student newStudent;
    newStudent.registerUser();
}

//11. Display All Current Member Students
void staff::displayStudentStaff(){
    student displayStudent;
    displayStudent.displayAllMemberStudent();
}

//12. Generate Fine Report
void staff::generateReportStaff(){
    book report;
    report.generateFineReport();
}