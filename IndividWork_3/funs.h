#pragma once

#include <fstream>
#include <iostream>
#include <cctype>
#include <string>
#include <cstdio>
#include <iomanip>
#include <cstring>

using namespace std;

struct Student {
	char Name[50];
	char number[10]{ "AA0000" };
	bool attestation[5] = { 0, 0, 0, 0, 0 };
};

void print_cstring(char*);
void change_cstring(char*);
void create_students_list(string);
void read_students_list(string);
void print_students_without_attestation(string);
void change_attestation(string);