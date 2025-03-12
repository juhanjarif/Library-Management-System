#include "../include/user.h"

user::user() : username(""), password(""), fullName(""), department(""), programme(""), contact("") {}

user::user(string username, string password, string fullName, string department, string programme, string contact) : username(username), password(password), fullName(fullName), department(department), programme(programme), contact(contact) {}

user::~user() {}