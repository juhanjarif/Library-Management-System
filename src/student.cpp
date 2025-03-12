#include "../include/student.h"
#include "../include/hashutil.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

using namespace std;

student::student() : user() {}

student::student(string username, string password, string name, string dept, string programme, string contact) : user(username, password, name, dept, programme, contact) {}


student::~student(){}

void student::registerUser(){
    ifstream inFile("studentsInfo.csv");
    ofstream outFile("studentsInfo.csv", ios::app);

    if(!outFile.is_open() || !inFile.is_open()){
        cout << "Error Registering Students!\n" << endl;
        return;
    }

    string line, existingUsername;
    bool userExists = false;

    cout << "Enter Student ID: ";
    cin >> username;

    while(getline(inFile, line)){
        stringstream ss(line);
        getline(ss, existingUsername, ',');

        if(existingUsername == username){
            userExists = true;
            break;
        }
    }

    inFile.close();

    if(userExists){
        cout << "Error: Student ID already registered! Please log in.\n" << endl;
        return;
    }

    cout << "Enter Student Name: ";
    cin.ignore();
    getline(cin, fullName);

    cout << "Enter Department Name: ";
    cin >> department;

    cout << "Enter Programme Name: ";
    cin >> programme;

    cout << "Enter Contact: ";
    cin >> contact;

    cout << "Create a Password: ";
    cin >> password;

    string hashedPassword = customHash(password);

    outFile << username << "," << hashedPassword << "," << fullName << "," << department << "," << programme << "," << contact << "\n";
    outFile.close();

    cout << "Student Registration Successful!\n" << endl << endl;
}


bool student::loginUser(){
    ifstream file("studentsInfo.csv");

    string line, userid, pass;
    bool found = false;

    if(!file){
        cout << "Error: Logging in!\n" << endl;
        return false;
    }

    cout << "Enter Student ID: ";
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

void student::updatePassword(){
    ifstream file("studentsInfo.csv");
    ofstream outFile("tempstudentsInfo.csv");

    string line, userid, pass, newPass;
    bool found = false;

    if(!file.is_open() || !outFile.is_open()){
        cout << "Error: Updating Password!\n" << endl;
        return;
    }

    cout << "Enter Student ID: ";
    cin >> userid;
    cout << "Enter Previous Password: ";
    cin >> pass;

    string hashedPass = customHash(pass);

    while(getline(file, line)){
        if(line.find(',') == string::npos)
            continue;

        stringstream ss(line);
        string username, storedHashedPassword, fullName, department, programme, contact;

        getline(ss, username, ',');
        getline(ss, storedHashedPassword, ',');
        getline(ss, fullName, ',');
        getline(ss, department, ',');
        getline(ss, programme, ',');
        getline(ss, contact, ',');

        if(userid == username && hashedPass == storedHashedPassword){
            found = true;
            cout << "Enter your new Password:";
            cin >> newPass;
            storedHashedPassword = customHash(newPass);
        }

        outFile << username << "," << storedHashedPassword << "," << fullName << "," << department << "," << programme << "," << contact << "\n";
    }

    file.close();
    outFile.close();

    if(found)
        cout << "Password updated successfully!\n" << endl;
    else
        cout << "Incorrect Password!\nTry Again!\n" << endl;

    remove("studentsInfo.csv");
    rename("tempstudentsInfo.csv", "studentsInfo.csv");
}

void student::displayAllMemberStudent(){
    ifstream file("studentsInfo.csv");
    string line;

    if(!file.is_open()){
        cout << "Error: Displaying Student List!\n" << endl;
        return;
    }

    cout << "\nList of Current Students:" << endl;
    while(getline(file, line)){
        if(line.find(',') == string::npos)
            continue;

        stringstream ss(line);
        string username, password, fullName, department, programme, contact;

        getline(ss, username, ',');
        getline(ss, password, ',');
        getline(ss, fullName, ',');
        getline(ss, department, ',');
        getline(ss, programme, ',');
        getline(ss, contact, ',');

        cout << left << setw(30) << "Name: " + fullName << " | " << setw(20) << "Department: " + department << " | " << setw(25) << "Programme: " + programme << " | " << setw(15) << "Contact Info: " + contact << endl;
    }
    cout << endl;

    file.close();
}

void student::deleteMemberStudent(){
    ifstream file("studentsInfo.csv");
    ofstream tempfile("temp.csv");
    string line, username;
    bool isDeletedMember = false;

    if(!file.is_open() || !tempfile.is_open()){
        cout << "Error: Deleting Student!\n" << endl;
        return;
    }

    cout << "Enter the Student ID: ";
    cin >> username;

    while(getline(file, line)){
        stringstream ss(line);
        string studentID;

        getline(ss, studentID, ',');

        if(studentID == username){
            isDeletedMember = true;
            continue;
        }
        tempfile << line << "\n";
    }

    file.close();
    tempfile.close();

    remove("studentsInfo.csv");
    rename("temp.csv", "studentsInfo.csv");

    if(isDeletedMember)
        cout << "Student list was just updated as Student ID: " << username << " was deleted successfully!\n" << endl;
    else
        cout << "Student with Student ID " << username << " couldnot be found!\n" << endl;
}



//01. Search Book
void student::searchBookStd(){
    book search;
    search.searchBook();
}

//02. Reserve Book
void student::reserveBookStd(){
    book resBook;
    resBook.reserveBook();
}

//03. Check Availability of Book
void student::availabilityBookStd(){
    book availableBook;
    availableBook.searchBook();
}

//04. Display All Available Book
void student::displayBookStd(){
    book disBook;
    disBook.displayAllBooks();
}

//05. Request a Book to Add
void student::requestBookStd(){
    book reqBook;
    reqBook.requestBook();
}

//06. Track Due Date
void student::trackdueDateStd(){
    book trackDate;
    trackDate.trackDueDate();
}

//07. Check Fine Report
void student::generateReportStd(){
    book generateRep;
    generateRep.generateFineReport();
}