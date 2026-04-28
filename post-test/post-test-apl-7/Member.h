#ifndef MEMBER_H
#define MEMBER_H

#include <string>

struct Billing {
    int jam;
    int masaAktif;
};

struct User {
    std::string nama;
    std::string nim;
    Billing billing;
};

#endif