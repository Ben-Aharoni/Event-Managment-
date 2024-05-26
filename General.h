#pragma once

#define SIZE 255

char* myGets1(char* buffer, int size, FILE* source);
char* myGets2(char* buffer, int size);
char* getDynStr(char* str);
void generalArrayFunction(void* arr, int size, int typeSize, void(*func)(void* element));