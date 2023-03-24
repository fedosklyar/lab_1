#include<iostream>
#include<fstream>
#include<string>
#include<cstring>
#include<cstdio>


using namespace std;
void create_file(char *filename);
int fill_file(char *filename, int &max_size);
int encrypt_notes(int max, char *filename, char *new_name, int quantity);
void quan_of_odd_words(char *new_name, int new_quantity, int max_size);
void fill_the_file(string &file_name, int &quantity);
int recreate_notes(string name, int quantity, string &new_name);
void add_coma_and_quan(string name, int quantity);
bool check_mode(char *modevalue, int argc, char* argv[]);
int menu();
void file_append_stream();
void file_append_pointer();
void read_file(string name);
void read_file(char* name, int max, int quantity);