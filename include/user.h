#ifndef USER_H
#define USER_H

#include <iostream>
#include <string>

using namespace std;

class user{
protected:
    string username, password, fullName, department, programme, contact;

public:
    user();
    user(string username, string password, string fullName, string department, string programme, string contact);

    virtual void registerUser() = 0;
    virtual bool loginUser() = 0;
    virtual void updatePassword() = 0;

    virtual ~user();
};

#endif
