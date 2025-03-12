#ifndef STUDENT_H
#define STUDENT_H

#include "user.h"
#include "book.h"

using namespace std;

class student : public user{
public:
    student();
    student(string username, string password, string name, string dept, string programme, string contact);
    ~student() override;

    void registerUser() override;
    bool loginUser() override;
    void updatePassword() override;

    static void displayAllMemberStudent();
    static void deleteMemberStudent();

    void searchBookStd();
    void reserveBookStd();
    void availabilityBookStd();
    void displayBookStd();
    void requestBookStd();
    void trackdueDateStd();
    void generateReportStd();
};

#endif
