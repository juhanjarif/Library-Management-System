#include "../include/book.h"
#include <cmath>

book::book() : isbn(""), author(""), title(""), publication(""), quantity(0) {}

book::book(string isbn, string author, string title, string publication, int quantity) : isbn(isbn), author(author), title(title), publication(publication), quantity(quantity) {}

book::~book() {}

//adding new book
void book::addBook(){
    ifstream bookFile("bookList.csv");
    ofstream bookFileOut("bookList.csv", ios::app);
    ifstream reqFile("requestedBookList.csv");
    ofstream tempFile("tempRequestedBookList.csv");

    if(!bookFileOut.is_open() || !bookFile.is_open()){
        cout << "Error: Unable to Add a Book!" << endl;
        return;
    }

    if(!reqFile.is_open() || !tempFile.is_open()){
        cout << "Error: Processing Requested Book List!" << endl;
        return;
    }

    string isbn, title, author, publication;
    int quantity;
    while(true){
        cout << "Enter ISBN: ";
        cin.ignore();
        cin >> isbn;
        if(isbn.empty())
            cout << "Error: isbn cannot be empty! Please enter a valid isbn.\n";
        else
            break;
        
    }

    string line, existingISBN;
    bool isbnExists = false;

    while(getline(bookFile, line)){
        stringstream ss(line);
        getline(ss, existingISBN, ',');

        if(existingISBN == isbn){
            isbnExists = true;
            break;
        }
    }

    bookFile.close();

    if(isbnExists){
        cout << "Warning: Same ISBN Found!\nEnter a valid ISBN!\n" << endl;
        return;
    }

    cin.ignore();
    
    while(true){
        cout << "Enter Title of the Book: ";
        getline(cin, title);

        if (title.empty())
            cout << "Error: Title cannot be empty! Please enter a valid title.\n";
        else
            break;
    }

    while(true){
        cout << "Enter Author Name: ";
        getline(cin, author);

        if(author.empty())
            cout << "Error: Author name cannot be empty! Please enter a valid author name.\n";
        else
            break;
    }

    while(true){
        cout << "Enter Publication Name: ";
        getline(cin, publication);

        if(publication.empty())
            cout << "Error: Publication name cannot be empty! Please enter a valid publication name.\n";
        else
            break;
    }

    while(true){
        cout << "Enter Quantity of the Book: ";
        cin >> quantity;
        if(quantity<1)
            cout << "Error: Quantity must be a positive number!\n";
        else
            break;
    }

    bookFileOut << isbn << "," << title << "," << author << "," << publication << "," << quantity << "\n";
    bookFileOut.close();

    cout << "Book added successfully!\n" << endl;

    string reqISBN;
    bool requestFound = false;

    while(getline(reqFile, line)){
        stringstream ss(line);
        getline(ss, reqISBN, ',');

        if(reqISBN == isbn){
            requestFound = true;
            continue;
        }
        tempFile << line << "\n";
    }

    reqFile.close();
    tempFile.close();

    remove("requestedBookList.csv");
    rename("tempRequestedBookList.csv", "requestedBookList.csv");

    if(requestFound)
        cout << "Book request found for this book is now deleted!\n" << endl;

    cout << endl;
}

//searching and checking availablility of book
void book::searchBook(){
    ifstream file("bookList.csv");
    string line, searchTerm;
    bool isFound = false;

    if(!file.is_open()){
        cout << "Error: Searching Book!\n" << endl;
        return;
    }

    cout << "Enter the keyword of the Book to search: ";
    cin.ignore();
    getline(cin, searchTerm);

    transform(searchTerm.begin(), searchTerm.end(), searchTerm.begin(), ::tolower);

    while(getline(file, line) ){
        if(line.find(',') == string::npos)
            continue;

        stringstream ss(line);
        string isbn, title, author, publication;
        int quantity;

        getline(ss, isbn, ',');
        getline(ss, title, ',');
        getline(ss, author, ',');
        getline(ss, publication, ',');
        ss >> quantity;

        transform(isbn.begin(), isbn.end(), isbn.begin(), ::tolower);
        transform(title.begin(), title.end(), title.begin(), ::tolower);
        transform(author.begin(), author.end(), author.begin(), ::tolower);
        transform(publication.begin(), publication.end(), publication.begin(), ::tolower);

        if((isbn.find(searchTerm) != string::npos) || (title.find(searchTerm) != string::npos) || (author.find(searchTerm) != string::npos) || (publication.find(searchTerm) != string::npos)){
            isFound = true;

            cout << endl;
            if(quantity > 0)
                cout << "Book Available!\nisbn: " << isbn << "\ntitle: " << title << "\nauthor: " << author << "\npublication name: " << publication << "\nquantity available: " << quantity << endl;
            else
                cout << "Book is currently not available\nisbn: " << isbn << "\ntitle: " << title << "\nauthor: " << author << "\npublication name: " << publication << "\nquantity available: " << quantity << endl;
        }
        cout << endl;
    }

    file.close();

    if(!isFound)
        cout << "Book not available in the library!\n" << endl;

}

//displaying all books
void book::displayAllBooks(){
    ifstream file("bookList.csv");
    string line;

    if(!file.is_open()){
        cout << "Error: Displaying Book!\n" << endl;
        return;
    }

    cout << "List of the Books Available:" << endl;

    while(getline(file, line)){
        if(line.find(',') == string::npos)
            continue;

        stringstream ss(line);
        string isbn, title, author, publication;
        int quantity;

        getline(ss, isbn, ',');
        getline(ss, title, ',');
        getline(ss, author, ',');
        getline(ss, publication, ',');
        ss >> quantity;

        cout << "\nisbn: " << isbn << "\ntitle: " << title << "\nauthor: " << author << "\npublication name: " << publication << "\nquantity available: " << quantity << endl;
    }

    cout << endl;
    file.close();
}

//updating book quantity when new books are added in the library
void book::updateBookQuantity(){
    ifstream file("bookList.csv");
    ofstream tempfile("temp.csv");

    string line, searchTerm;
    bool isUpdated = false, isFound = false;
    int sign, changeAmount;

    if(!file.is_open() || !tempfile.is_open()){
        cout << "Error: Updating Book!\n" << endl;
        return;
    }

    cout << "Enter the ISBN of the Book to update quantity: ";
    cin.ignore();
    getline(cin, searchTerm);

    transform(searchTerm.begin(), searchTerm.end(), searchTerm.begin(), ::tolower);

    cout << "1. Increase Book Quantity\n2. Decrease Book Quantity\nEnter your choice: ";
    cin >> sign;

    if(sign == 1)
        cout << "Enter the amount of Increment: ";
    else if(sign == 2)
        cout << "Enter the amount of Decrement: ";
    else{
        cout << "Invalid Input!\n" << endl;
        return;
    }
    cin >> changeAmount;

    while(getline(file, line)){
        if(line.find(',') == string::npos)
            continue;

        stringstream ss(line);
        string isbn, title, author, publication;
        int quantity;

        getline(ss, isbn, ',');
        getline(ss, title, ',');
        getline(ss, author, ',');
        getline(ss, publication, ',');
        ss >> quantity;

        transform(isbn.begin(), isbn.end(), isbn.begin(), ::tolower);
        transform(title.begin(), title.end(), title.begin(), ::tolower);
        transform(author.begin(), author.end(), author.begin(), ::tolower);
        transform(publication.begin(), publication.end(), publication.begin(), ::tolower);

        if((isbn.find(searchTerm) != string::npos) || (title.find(searchTerm) != string::npos) || (author.find(searchTerm) != string::npos) || (publication.find(searchTerm) != string::npos)){
            isFound = true;

            if(sign == 1)
                quantity += changeAmount;
            else if(sign == 2)
                quantity -= changeAmount;

            if(quantity < 0)
                quantity = 0;

            tempfile << isbn << "," << title << "," << author << "," << publication << "," << quantity << "\n";
            isUpdated = true;
        }
        else
            tempfile << isbn << "," << title << "," << author << "," << publication << "," << quantity << "\n";
    }

    file.close();
    tempfile.close();

    remove("bookList.csv");
    rename("temp.csv", "bookList.csv");

    if(isUpdated)
        cout << "Book List was updated just now with new Book Quantity!\n" << endl;
    else
        cout << "Book list was not updated!\n" << endl;

    if(!isFound)
        cout << "Book not available in the library!\n" << endl;

    cout << endl;
}

//deleting a book
void book::deleteBook(){
    ifstream file("bookList.csv");
    ofstream tempfile("temp.csv");
    ifstream issuedFile("issuedBookList.csv");

    string line, searchTerm;
    bool isDeleted = false, isFound = false, isIssued = false;

    if(!file.is_open() || !tempfile.is_open() || !issuedFile.is_open()){
        cout << "Error: Deleting Book!\n" << endl;
        return;
    }

    cout << "Enter the ISBN of the Book to delete: ";
    cin.ignore();
    getline(cin, searchTerm);

    transform(searchTerm.begin(), searchTerm.end(), searchTerm.begin(), ::tolower);

    while(getline(issuedFile, line)){
        stringstream ss(line);
        string studentId, isbn, title, author, publication, quantityIssued, issueDate;

        getline(ss, studentId, ',');
        getline(ss, isbn, ',');
        getline(ss, title, ',');
        getline(ss, author, ',');
        getline(ss, publication, ',');
        getline(ss, quantityIssued, ',');
        getline(ss, issueDate);

        transform(isbn.begin(), isbn.end(), isbn.begin(), ::tolower);
        transform(title.begin(), title.end(), title.begin(), ::tolower);
        transform(author.begin(), author.end(), author.begin(), ::tolower);
        transform(publication.begin(), publication.end(), publication.begin(), ::tolower);

        if((isbn.find(searchTerm) != string::npos) || (title.find(searchTerm) != string::npos) || (author.find(searchTerm) != string::npos) || (publication.find(searchTerm) != string::npos)){
            isIssued = true;
            break;
        }
    }

    issuedFile.close();

    if(isIssued){
        cout << "Book cannot be deleted as it is currently issued!\n" << endl;
        file.close();
        tempfile.close();
        remove("temp.csv");
        return;
    }

    while(getline(file, line)){
        stringstream ss(line);
        string isbn, title, author, publication;
        int quantity;

        getline(ss, isbn, ',');
        getline(ss, title, ',');
        getline(ss, author, ',');
        getline(ss, publication, ',');
        ss >> quantity;

        transform(isbn.begin(), isbn.end(), isbn.begin(), ::tolower);
        transform(title.begin(), title.end(), title.begin(), ::tolower);
        transform(author.begin(), author.end(), author.begin(), ::tolower);
        transform(publication.begin(), publication.end(), publication.begin(), ::tolower);

        if((isbn.find(searchTerm) != string::npos) || (title.find(searchTerm) != string::npos) || (author.find(searchTerm) != string::npos) || (publication.find(searchTerm) != string::npos)){
            isFound = true;
            isDeleted = true;
            continue;
        }

        tempfile << isbn << "," << title << "," << author << "," << publication << "," << quantity << "\n";
    }

    file.close();
    tempfile.close();

    if(isDeleted){
        remove("bookList.csv");
        rename("temp.csv", "bookList.csv");
        cout << "Book Deleted Successfully!\n" << endl;
    }
    else
        cout << "No Book was Deleted!\n" << endl;

    if(!isFound)
        cout << "Book not available in the library!\n" << endl;

    cout << endl;
}

//checking validity of student id
bool book::isValidStudentID(const string& studentID){
    ifstream file("studentsInfo.csv");
    string line;

    if(!file.is_open()){
        cout << "Error: Checking Validity of the Student!\n" << endl;
        return false;
    }

    while(getline(file, line)){
        stringstream ss(line);
        string username;

        getline(ss, username, ',');

        if(username == studentID){
            file.close();
            return true;
        }
    }

    file.close();
    return false;
}

//issuing a book
void book::issueBook(){
    ifstream file("bookList.csv");
    ofstream tempfile("temp.csv");
    ofstream issuedFile("issuedBookList.csv", ios::app);
    ifstream reservedFile("reservedBookList.csv");
    ofstream reservedFileTemp("reservedBookListTemp.csv");

    string line, searchTerm, studentID;
    bool isIssued = false, isFound = false, isReserved = false;

    if(!file.is_open() || !tempfile.is_open() || !issuedFile.is_open() || !reservedFile.is_open() || !reservedFileTemp.is_open()){
        cout << "Error: Issueing Book!\n" << endl;
        return;
    }

    cout << "Enter the StudentID: ";
    cin.ignore();
    cin >> studentID;

    if(!isValidStudentID(studentID)){
        cout << "Error: Invalid Student ID! Please check and try again!\n" << endl;
        file.close();
        tempfile.close();
        issuedFile.close();
        reservedFile.close();
        reservedFileTemp.close();

        remove("temp.csv");
        remove("reservedBookListTemp.csv");

        return;
    }

    cout << "Enter the ISBN of the Book to Issue: ";
    cin.ignore();
    getline(cin, searchTerm);

    transform(searchTerm.begin(), searchTerm.end(), searchTerm.begin(), ::tolower);

    auto now = chrono::system_clock::now();
    time_t issueDate = chrono::system_clock::to_time_t(now);

    while(getline(file, line)){
        stringstream ss(line);
        string isbn, title, author, publication;
        int quantity;

        getline(ss, isbn, ',');
        getline(ss, title, ',');
        getline(ss, author, ',');
        getline(ss, publication, ',');
        ss >> quantity;

        transform(isbn.begin(), isbn.end(), isbn.begin(), ::tolower);
        transform(title.begin(), title.end(), title.begin(), ::tolower);
        transform(author.begin(), author.end(), author.begin(), ::tolower);
        transform(publication.begin(), publication.end(), publication.begin(), ::tolower);

        if((isbn.find(searchTerm) != string::npos)){
            isFound = true;
            if(quantity > 0){
                isIssued = true;

                string tempLine;

                while(getline(reservedFile, tempLine)){
                    stringstream tempSS(tempLine);
                    string tempStudentID, tempISBN;

                    getline(tempSS, tempStudentID, ',');
                    getline(tempSS, tempISBN, ',');

                    if((studentID == tempStudentID) && (isbn == tempISBN)){
                        isReserved = true;
                        continue;
                    }

                    reservedFileTemp << tempLine << "\n";
                }

                if(!isReserved)
                    quantity--;

                issuedFile << studentID << "," << isbn << "," << title << "," << author << "," << publication << "," << "1" << "," << issueDate << "\n";
            }
            else
                cout << "Book out of stock!\n" << endl;
        }

        tempfile << isbn << "," << title << "," << author << "," << publication << "," << quantity << "\n";
    }

    file.close();
    tempfile.close();
    issuedFile.close();
    reservedFile.close();
    reservedFileTemp.close();

    remove("bookList.csv");
    rename("temp.csv", "bookList.csv");

    remove("reservedBookList.csv");
    rename("reservedBookListTemp.csv", "reservedBookList.csv");

    if(isIssued && isReserved)
        cout << "Book was Reserved and Issued Successfully!\n" << endl;
    else if(isIssued && !isReserved)
        cout << "Book was Issued Successfully!\n" << endl;
    else
        cout << "Book was not issued!\n" << endl;

    if(!isFound)
        cout << "Book not available in the library!\n" << endl;

    cout << endl;
}

//displaying all issued book
void book::displayAllIssuedBook(){
    ifstream issuedFile("issuedBookList.csv");
    ifstream studentFile("studentsInfo.csv");

    string line, studentLine;

    if(!issuedFile.is_open() || !studentFile.is_open()){
        cout << "Error: Displaying Issued Book!\n" << endl;
        return;
    }

    cout << "List of the Books that are Issued:" << endl;

    while(getline(issuedFile, line)){
        if(line.find(',') == string::npos)
            continue;

        stringstream ss(line);
        string studentID, isbn, title, author, publication, quantity, issueDate;

        getline(ss, studentID, ',');
        getline(ss, isbn, ',');
        getline(ss, title, ',');
        getline(ss, author, ',');
        getline(ss, publication, ',');
        getline(ss, quantity, ',');
        getline(ss, issueDate, ',');

        string username, password, studentFullName, studentDepartment, programme, studentContact;
        bool studentFound = false;

        studentFile.clear();
        studentFile.seekg(0, ios::beg);

        while(getline(studentFile, studentLine)){
            if(studentLine.find(',') == string::npos)
                continue;

            stringstream studentSS(studentLine);

            getline(studentSS, username, ',');
            getline(studentSS, password, ',');
            getline(studentSS, studentFullName, ',');
            getline(studentSS, studentDepartment, ',');
            getline(studentSS, programme, ',');
            getline(studentSS, studentContact, ',');

            if(username == studentID){
                studentFound = true;
                break;
            }
        }

        time_t timestamp = stoll(issueDate);
        char date[80];
        tm* local_tm = localtime(&timestamp);
        strftime(date, sizeof(date), "%Y-%m-%d %H:%M:%S", local_tm);

        cout << "\nisbn: " << isbn << "\ntitle: " << title << "\nauthor: " << author << "\npublication name: " << publication << "\nquantity issued: " << quantity << "\nissued time and Date: " << date << "\nissued to: " << studentID << endl;

        if(studentFound)
            cout << "Full Name: " << studentFullName << "\nDepartment: " << studentDepartment << "\nContact: " << studentContact << endl;
        else
            cout << "Student information not found!\n" << endl;
    }

    issuedFile.close();
    studentFile.close();

    cout << endl;
}

//reserving a book; student can reserve a book
void book::reserveBook(){
    ifstream file("bookList.csv");
    ofstream tempFile("temp.csv");
    ofstream reservedFile("reservedBookList.csv", ios::app);

    string line, searchTerm, studentID;
    bool isFound = false;

    if(!file.is_open() || !tempFile.is_open() || !reservedFile.is_open()){
        cout << "Error: Reserving Book!\n" << endl;
        return;
    }

    cout << "Enter your Student ID: ";
    cin.ignore();
    cin >> studentID;

    cout << "Enter the ISBN to search the Book that you want to reserve: ";
    cin.ignore();
    getline(cin, searchTerm);

    transform(searchTerm.begin(), searchTerm.end(), searchTerm.begin(), ::tolower);

    while(getline(file, line)){
        stringstream ss(line);
        string isbn, title, author, publication;
        int quantity;

        getline(ss, isbn, ',');
        getline(ss, title, ',');
        getline(ss, author, ',');
        getline(ss, publication, ',');
        ss >> quantity;

        transform(isbn.begin(), isbn.end(), isbn.begin(), ::tolower);
        transform(title.begin(), title.end(), title.begin(), ::tolower);
        transform(author.begin(), author.end(), author.begin(), ::tolower);
        transform(publication.begin(), publication.end(), publication.begin(), ::tolower);

        if(isbn.find(searchTerm) != string::npos) {
            isFound = true;
            if(quantity > 0){
                quantity--;

                reservedFile << studentID << ',' << isbn << ',' << title << ',' << author << ',' << publication << '\n';

                cout << "Book is Available and Reserved Successfully to Student: " << studentID << "!\nUpdated Quantity: " << quantity << endl;
                cout << endl;
            }
            else
                cout << "Book is currently unavailable for reservation!\n" << endl;
        }

        tempFile << isbn << ',' << title << ',' << author << ',' << publication << ',' << quantity << '\n';
    }

    file.close();
    tempFile.close();
    reservedFile.close();

    remove("bookList.csv");
    rename("temp.csv", "bookList.csv");

    if(!isFound)
        cout << "Book not available in the library!\n" << endl;

    cout << endl;
}

//returning a book
void book::returnBook(){
    ifstream bookFile("bookList.csv");
    ofstream tempBookFile("tempBookList.csv");
    ifstream issuedFile("issuedBookList.csv");
    ofstream tempIssuedFile("tempIssuedBookList.csv");

    string line, searchTerm, studentUsername;
    bool isBookFound = false;
    bool isIssuedEntryFound = false;
    bool isStudentFound = false;

    if(!bookFile.is_open() || !tempBookFile.is_open() || !issuedFile.is_open() || !tempIssuedFile.is_open()){
        cout << "Error: Returning Book!\n" << endl;
        return;
    }

    cout << "Enter the student ID of the student returning the book: ";
    cin.ignore();
    getline(cin, studentUsername);

    cout << "Enter the ISBN to search the Book that you want to return: ";
    getline(cin, searchTerm);

    while(getline(issuedFile, line)){
        stringstream ss(line);
        string studentId, isbn, title, author, publication, issueDateStr;
        int quantityIssued;

        getline(ss, studentId, ',');
        getline(ss, isbn, ',');
        getline(ss, title, ',');
        getline(ss, author, ',');
        getline(ss, publication, ',');
        ss >> quantityIssued;
        ss.ignore();
        getline(ss, issueDateStr);

        if(studentId == studentUsername){
            isStudentFound = true;
            if(isbn.find(searchTerm) != string::npos){
                isIssuedEntryFound = true;

                time_t issueDate = stoll(issueDateStr);
                auto now = chrono::system_clock::now();
                time_t returnDate = chrono::system_clock::to_time_t(now);
                double daysElapsed = difftime(returnDate, issueDate) / (60 * 60 * 24);

                if(daysElapsed > 28.0){
                    double fine = floor(daysElapsed - 28.0) * 10.0;
                    cout << "Book returned " << floor(daysElapsed - 28) << " days late! Pay fine of BDT " << fine << " !\n" << endl;
                }
                else
                    cout << "Book returned in time\n" << endl;

                continue;
            }
            else
                tempIssuedFile << line << '\n';
        }
        else
            tempIssuedFile << line << '\n';
    }

    if(!isStudentFound){
        cout << "Error: Student ID does not match with any issued instances!\n" << endl;
        cout << endl;

        bookFile.close();
        tempBookFile.close();
        issuedFile.close();
        tempIssuedFile.close();

        remove("tempBookList.csv");
        remove("tempIssuedBookList.csv");
        return;
    }

    if(!isIssuedEntryFound){
        cout << "No matching entry found in the issued books list for the given student ID!\n" << endl;
        cout << endl;

        bookFile.close();
        tempBookFile.close();
        issuedFile.close();
        tempIssuedFile.close();

        remove("tempBookList.csv");
        remove("tempIssuedBookList.csv");
        return;
    }

    while(getline(bookFile, line)){
        stringstream ss(line);
        string isbn, title, author, publication;
        int quantity;

        getline(ss, isbn, ',');
        getline(ss, title, ',');
        getline(ss, author, ',');
        getline(ss, publication, ',');
        ss >> quantity;

        if(isbn.find(searchTerm) != string::npos) {
            isBookFound = true;
            quantity++;
            cout << "Book Returned Successfully!\n"<< endl;
            cout << endl;
        }

        tempBookFile << isbn << ',' << title << ',' << author << ',' << publication << ',' << quantity << '\n';
    }

    if(!isBookFound){
        cout << "Book not available in the library!\n" << endl;
        cout << endl;

        bookFile.close();
        tempBookFile.close();
        issuedFile.close();
        tempIssuedFile.close();

        remove("tempBookList.csv");
        remove("tempIssuedBookList.csv");
        return;
    }

    bookFile.close();
    tempBookFile.close();
    issuedFile.close();
    tempIssuedFile.close();

    remove("bookList.csv");
    rename("tempBookList.csv", "bookList.csv");
    remove("issuedBookList.csv");
    rename("tempIssuedBookList.csv", "issuedBookList.csv");
}

//requesting a book; student can request a book
void book::requestBook(){
    ofstream file("requestedBookList.csv", ios::app);

    if(file.is_open()){
        string isbn, title, author, publication;

        cout << "Enter ISBN: ";
        cin.ignore();
        getline(cin, isbn);

        cout << "Enter Title of the Book: ";
        getline(cin, title);

        cout << "Enter Author Name: ";
        getline(cin, author);

        cout << "Enter Publication Name: ";
        getline(cin, publication);

        file << isbn << "," << title << "," << author << "," << publication << "\n";
        cout << "Book requested successfully!\n" << endl;

        file.close();
    }
    else{
        cout << "Error: Could not request the Book!\n" << endl;
        return;
    }
    cout << endl;;
}

//displaying reservation status of a book
void book::displayReservationStatus(){
    ifstream issuedBookFile("issuedBookList.csv");
    ifstream studentFile("studentsInfo.csv");

    string line, searchTerm, studentLine;
    bool isFound = false;

    if(!issuedBookFile.is_open() || !studentFile.is_open()){
        cout << "Error: Displaying Reservation Status of a Book!\n" << endl;
        return;
    }

    cout << "Enter the ISBN to search the Book that you want to check: ";
    cin.ignore();
    getline(cin, searchTerm);

    transform(searchTerm.begin(), searchTerm.end(), searchTerm.begin(), ::tolower);

    while(getline(issuedBookFile, line)){
        if(line.find(',') == string::npos)
            continue;
        stringstream ss(line);
        string studentID, isbn, title, author, publication, quantity, issueDate;

        getline(ss, studentID, ',');
        getline(ss, isbn, ',');
        getline(ss, title, ',');
        getline(ss, author, ',');
        getline(ss, publication, ',');
        getline(ss, quantity, ',');
        getline(ss, issueDate, ',');

        transform(isbn.begin(), isbn.end(), isbn.begin(), ::tolower);
        transform(title.begin(), title.end(), title.begin(), ::tolower);
        transform(author.begin(), author.end(), author.begin(), ::tolower);
        transform(publication.begin(), publication.end(), publication.begin(), ::tolower);

        if((isbn.find(searchTerm) != string::npos)){
            isFound = true;

            time_t timestamp = stoll(issueDate);
            char date[80];
            tm* local_tm = localtime(&timestamp);
            strftime(date, sizeof(date), "%Y-%m-%d %H:%M:%S", local_tm);

            cout << "\nMatch Found:\nisbn: " << isbn << "\ntitle: " << title << "\nauthor: " << author << "\npublication name: " << publication << "\nIssue Date: " << date << "\nHeld by Student ID: " << studentID << endl;

            string username, password, studentFullName, studentDepartment, programme, studentContact;
            bool studentFound = false;

            studentFile.clear();
            studentFile.seekg(0, ios::beg);

            while(getline(studentFile, studentLine)){
                stringstream studentSS(studentLine);

                getline(studentSS, username, ',');
                getline(studentSS, password, ',');
                getline(studentSS, studentFullName, ',');
                getline(studentSS, studentDepartment, ',');
                getline(studentSS, programme, ',');
                getline(studentSS, studentContact, ',');

                if(username == studentID){
                    studentFound = true;
                    break;
                }
            }

            if(studentFound)
                cout << "Full Name: " << studentFullName << "\nDepartment: " << studentDepartment << "\nContact: " << studentContact << endl;
            else
                cout << "Student information not found!\n" << endl;
        }
    }

    if(!isFound)
        cout << "No matching reservation found for the given keyword!\n" << endl;

    issuedBookFile.close();
    studentFile.close();

    cout << endl;
}

//track due date function for student
void book::trackDueDate(){
    ifstream file("issuedBookList.csv");
    string line, userid;
    bool isFound = false;

    if(!file.is_open()){
        cout << "Error: Tracking Due date" << endl;
        return;
    }

    cout << "Enter the Student ID: ";
    cin >> userid;

    if(!isValidStudentID(userid)){
        cout << "Error: Invalid Student ID! Please check and try again!\n" << endl;
        file.close();
        return;
    }

    cout << "Report For Student: " << userid << endl;

    while(getline(file, line)){
        stringstream ss(line);
        string studentID, isbn, title, author, publication, quantity, issueDate;

        getline(ss, studentID, ',');

        if(userid == studentID){
            isFound = true;
            getline(ss, isbn, ',');
            getline(ss, title, ',');
            getline(ss, author, ',');
            getline(ss, publication, ',');
            getline(ss, quantity, ',');
            getline(ss, issueDate, ',');

            time_t date = stoll(issueDate);
            auto now = chrono::system_clock::now();
            time_t currentDate = chrono::system_clock::to_time_t(now);

            double daysElapsed = difftime(currentDate, date) / (60 * 60 * 24);
            int daysRemaining = 28 - static_cast<int>(daysElapsed);

            cout << "\nBook: " << title << "\nISBN: " << isbn << "\nAuthor Name: " << author << "\nPublication: " << publication << "\nStatus: ";

            if(daysRemaining > 0)
                cout << daysRemaining << " days remaining" << endl;
            else
                cout << "Limit Over!" << endl;
            cout << endl;
        }
    }

    file.close();

    if(!isFound)
        cout << "No history for Student: " << userid << endl;
}

//generating fine report
void book::generateFineReport(){
    ifstream file("issuedBookList.csv");
    string line, userid;
    bool isFound = false;
    double totalFine = 0;
    int totalBooktaken = 0;

    if(!file.is_open()){
        cout << "Error: Calculating Fine!\n" << endl;
        return;
    }

    cout << "Enter the Student ID: ";
    cin >> userid;

    if(!isValidStudentID(userid)){
        cout << "Error: Invalid Student ID! Please check and try again!\n" << endl;
        file.close();
        return;
    }

    cout << "Fine Report For Student: " << userid << endl;

    while(getline(file, line) && !isFound){
        if(line.find(',') == string::npos)
            continue;
        stringstream ss(line);
        string studentID, isbn, title, author, publication, quantity, issueDate;

        getline(ss, studentID, ',');

        if(userid == studentID){
            totalBooktaken++;
            isFound = true;
            getline(ss, isbn, ',');
            getline(ss, title, ',');
            getline(ss, author, ',');
            getline(ss, publication, ',');
            getline(ss, quantity, ',');
            getline(ss, issueDate, ',');

            time_t date = stoll(issueDate);
            auto now = chrono::system_clock::now();
            time_t currentDate = chrono::system_clock::to_time_t(now);

            double daysElapsed = difftime(currentDate, date) / (60 * 60 * 24);
            int daysOverdue = static_cast<int>(daysElapsed) - 28;

            double fine = 0;

            if(daysOverdue > 0){
                fine = daysOverdue * 10;
                totalFine += fine;
            }

            cout << "\nbook: " << title << "\nisbn: " << isbn << "\nauthor: " << author << "\npublication name: " << publication << "\nfine amount: " << fine << " BDT\n" << endl;
        }
    }

    file.close();

    cout << "\nTotal Books Issued to " << userid << " is: " << totalBooktaken << endl;
    cout << endl;

    if(totalFine > 0)
        cout << "\nTotal Fine Amount: " << totalFine << " BDT\n" << endl;
    else
        cout << "\nStudent " << userid << " has no due amount to be paid!\n" << endl;

    if(!isFound)
        cout << "\nNo history for Student: " << userid << endl;
    cout << endl;

    cout << endl;
}