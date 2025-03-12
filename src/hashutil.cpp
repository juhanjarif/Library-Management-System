#include "../include/hashutil.h"

using namespace std;

string customHash(const string &password){
    unsigned long hash = 9973;
    for(char c : password)
        hash = ((hash << 5) + hash) + c;

    string hashedPassword;
    while(hash > 0){
        int remainder = hash % 16;
        if(remainder < 10)
            hashedPassword += ('0' + remainder);
        else
            hashedPassword += ('a' + remainder - 10);
        hash /= 16;
    }

    return hashedPassword;
}
