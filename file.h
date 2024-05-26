#pragma once


#define CLOSE_RETURN_0(fp) {fclose(fp); return 0;}
#define FREE_CLOSE_RETURN_0(ptr , fp) {free(ptr); fclose(fp); return 0;}
#define PUTS_RETURN_0(msg) {puts(msg); return 0;}
typedef unsigned char BYTE;

int	readIntFromFile(int* val, FILE* fp, const char* msg);
int	writeIntToFile(int val, FILE* fp, const char* msg);
int	writeCharsToFile(const char* arr, int size, FILE* fp, const char* msg);
int	readCharsFromFile(char* arr, int length, FILE* fp, const char* msg);
char* readStringFromFile(FILE* fp, const char* msg);
int	 writeStringToFile(const char* str, FILE* fp, const char* msg);



