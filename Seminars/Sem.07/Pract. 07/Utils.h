#pragma once
#include <ostream>

void myStrCpy(char *, const char *, size_t = 0);
int myStrLen(const char *);
void resizeUtil(char *&, int, bool = false);
int myStrCmp(const char *, const char *);
int strToInt(const char *);
void printStr(const char *);