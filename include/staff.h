#ifndef STAFF_H
#define STAFF_H

#include "user.h"
#include "book.h"
#include "student.h"

using namespace std;

class staff : public user{
public:
    staff();
    staff(string username, string password, string name, string dept, string programme, string contact);
    ~staff() override;

    void registerUser() override;
    bool loginUser() override;
    void updatePassword() override;

    static void displayAllMemberStaff();
    static void deleteMemberStaff();

    void searchBookStaff();
    void newBooksAddStaff();
    void updateBookStaff();
    void issueBookStaff();
    void returnBookStaff();
    void availabilityBookStaff();
    void displayBookStaff();
    void displayIssuedBookStaff();
    void displayReservationStatusStaff();
    void addNewStudentStaff();
    void displayStudentStaff();
    void generateReportStaff();
};

class student;

#endif
