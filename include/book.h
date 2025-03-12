#ifndef BOOK_H
#define BOOK_H

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <chrono>
#include <algorithm>

using namespace std;

class book{
private:
    string isbn, author, title, publication;
    int quantity;

public:
    book();
    book(string isbn, string author, string title, string publication, int quantity);
    ~book();

    void addBook();
    static void searchBook();
    static void displayAllBooks();
    static void updateBookQuantity();
    static void deleteBook();
    static bool isValidStudentID(const string& studentID);
    static void issueBook();
    static void displayAllIssuedBook();
    static void reserveBook();
    static void returnBook();
    static void requestBook();
    static void displayReservationStatus();
    static void trackDueDate();
    static void generateFineReport();
};

#endif
