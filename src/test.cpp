#include <iostream>
#include <cstring>
int main(){
    const char* tset = "abcd";
    char tt[strlen(tset) + 1];
    strcpy(tt,tset);
    tt[3] = 'e';
    tset = tt;
    std::cout << tset;
    return 0;
}