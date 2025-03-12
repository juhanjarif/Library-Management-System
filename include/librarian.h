#ifndef LIBRARIAN_H
#define LIBRARIAN_H

#include "user.h"
#include "book.h"
#include "student.h"
#include "staff.h"

using namespace std;

class librarian : public user{
public:
    librarian();
    librarian(string username, string password, string name, string dept, string programme, string contact);
    ~librarian() override;

    void registerUser() override;
    bool loginUser() override;
    void updatePassword() override;

    void updateLibrarianDetails();
    static void displayLibrarianDetails();

    void searchBookLib();
    void newBooksAddLib();
    void updateBookStatusLib();
    void issueBookLib();
    void returnBookLib();
    void availabilityBookLib();
    void displayBookLib();
    void displayIssuedBookLib();
    void displayReservationStatusLib();
    void deleteBookLib();
    void addNewStudentLib();
    void addNewStaffLib();
    void deleteStudentLib();
    void deleteStaffLib();
    void displayStudentLib();
    void displayStaffLib();
    void generateReportLib();
};

#endif
