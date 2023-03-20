#ifndef STRUCT_H
#define STRUCT_H
#include <iostream>
#include <string.h>
#endif // STRUCT_H

struct info{
    int num;
    std::string text[5];
    int timetable[35];
    int location;
    std::string want_time[3];
    std::string question;
};

extern info _save[100];
