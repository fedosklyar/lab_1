#include "temp.h"

//using namespace std;

void fill_the_file(string &file_name, int &quantity){
    ofstream outFile;
    string line, name;
    
    cin.ignore();
    cout<<"Enter the name of file: ";
    getline(cin, name);
    cout<<"Enter the quantity of strings: ";
    cin>>quantity;
    file_name = name + ".txt";
    outFile.open(file_name);

    cin.ignore();
    int i = quantity;
    while(i > 0){
        cout<<"Enter the string: ";
        getline(cin, line);
        outFile<<line<<'\n';
        i--;
    }
    outFile.close();    
}

int recreate_notes(string name, int quantity, string &new_name){
    ifstream inFile;
    ofstream newFile;
    string line, new_line;
    int flag {}, new_quan {};
    inFile.open(name);
    new_name = "NEW_" + name;
    newFile.open(new_name);
    for(int i = 0; i < quantity; i++){
        getline(inFile, line);
        cout<<"\n\n====================================="<<endl;
        cout<<"The "<<i + 1<<" string --> ";
        cout<<line<<'\n';
        new_line = "";
        for(int j = 0; j < line.length(); j++) if(j % 2 == 0) new_line.push_back(line.at(j));
        for(int j = 0; j < line.length(); j++) if(j % 2 != 0) new_line.push_back(line.at(j));
        cout<<i + 1<<" Encrypted line --> "<<new_line<<endl;
        flag++;
        newFile<<new_line<<'\n';
    }
    inFile.close(); newFile.close(); 

    remove(name.c_str()); //видаляю спочатку заповнений файл
    rename(new_name.c_str(), name.c_str()); //перейменовую новозаповнений файл на початковий
    
    
    inFile.open(name);
    newFile.open(new_name);
    for(int i = 0; i < quantity; i++){
        getline(inFile, line);
        if((i + 1) % 2 == 0){
            newFile<<line<<'\n';
            new_quan++;
        }
    }
    inFile.close(); newFile.close();


    cout<<'\n'<<name;
    cout<<"\n"<<new_quan<<'\n';
    return new_quan;
}

void add_coma_and_quan(string name, int quantity){
    ifstream inFile;
    ofstream outFile;
    string line = "", word = "", new_line = "";
    inFile.open(name);
    outFile.open("temp" + name);
    int odd {} ,space {};

    for(int i = 0; i < quantity; i++){
        getline(inFile, line);
        odd = 0; space = 0;
        for(int j = 0; j < line.length(); j++) {
            if(isspace (line.at(j)) || j + 1 == line.length()) { 
            if(isspace (line.at(j))) space++;
            if((j + space + odd) % 2 == 0) odd++;
        }
        }
        cout<<"Spaces = "<<space<<'\n';
        cout<<"Odd = "<<odd<<'\n';
        new_line = line + "," + to_string(odd);
        outFile<<new_line<<'\n';
    }
    inFile.close();
    outFile.close();
    remove(name.c_str());
    rename(("temp"+ name).c_str(), name.c_str());
}

void create_file(char *filename){
    FILE *file;
    char res[] = ".txt";
    cin.ignore();
    printf("Enter the name of file: ");
    fgets(filename, 30, stdin);
    filename[strlen(filename) - 1] = '\0';
    strcat(filename, res);

    file = fopen(filename, "w");
    fclose(file);
    cout<<"\nname of file: "<<filename<<endl;
}


int fill_file(char *filename, int &max_size){
    FILE *file;
    file = fopen(filename, "w");
    int quantity;
    char symb;
    int size = 0;
    printf("Enter the quantity of notes: ");
    scanf("%d", &quantity);

    fflush(stdin);
    for(int i = 0; i < quantity; i++){
        size = 0;
        cout<<"Enter the string: ";
        while(true){
            symb = (char) getchar();
            putc(symb, file);
            size++;
            if(symb == '\n')  break;
        }
        if(size > max_size) max_size = size;
    }
    fclose(file);
    cout<<"\nMax_Size = "<<max_size<<endl;
    cout<<"\nQuantity = "<<quantity<<endl;

    return quantity;
}

int encrypt_notes(int max, char *filename, char *new_name, int quantity){
    FILE *file, *newfile;
    strcpy(new_name, "NEW");
    file = fopen(filename, "r");
    strcat(new_name, filename);

    char *str = (char*) calloc(max + 2, sizeof(char));
    char *encrypt_str = (char*) calloc(max + 2, sizeof(char));
    int k, new_quantity = 0;

    newfile = fopen(new_name, "w");
    for(int i = 0; i < quantity; i++){
        cout<<"\n\n====================="<<endl;
        memset(str, '\0', strlen(str));
        memset(encrypt_str, '\0', strlen(encrypt_str));
        k = 0;
        fgets(str , max + 1, file);
        cout<<""<< i + 1<<" length of str = "<<strlen(str)<<endl;
        str[strlen(str) - 1] = '\0'; 
        cout<<i + 1<<" String --> "<<str<<endl;
        for(int j = 0; j < strlen(str); j++){
            if(j % 2 == 0){
                 encrypt_str[k] =  str[j];
                 k++;
            }
        } 
        for(int j = 0; j < strlen(str); j++){
            if(j % 2 != 0){
                 encrypt_str[k] = str[j];
                 k++;
            }
        } 
        encrypt_str[k] = '\n';
        cout<< i + 1<<" Encrypted str --> "<<encrypt_str<<endl;
        fputs(encrypt_str, newfile);
    }
    fclose(file); fclose(newfile);
    free(encrypt_str);

    remove(filename);
    rename(new_name, filename);

    newfile = fopen(new_name, "w");
    file = fopen(filename, "r");

    for(int i = 0; i < quantity; i++){
        memset(str, '\0', strlen(str));
        fgets(str, max + 1, file);
        if(i % 2 != 0){
            fputs(str, newfile);
            new_quantity++;
        }
    }
    fclose(file); fclose(newfile);
    free(str);

    cout<<"\nNew quantity = "<<new_quantity<<endl;

    return new_quantity;
    }


void quan_of_odd_words(char *new_name, int new_quantity, int max){
    
    FILE  *newfile, *finalfile;
    newfile = fopen(new_name, "r");
    finalfile = fopen("temp.txt", "w");
    char *str = (char*) calloc(max + 2, sizeof(char));
    int space, odd, j;


    for(int i = 0; i < new_quantity; i++){
        memset(str, '\0', strlen(str));
        fgets(str, max + 2, newfile);
        space = 0, odd = 0, j = 0;
        for(j; j < strlen(str); j++){
            if(isspace(str[j]) || j + 1 == strlen(str)){
                if(isspace(str[j])) space++;
                if((j + space + odd) % 2 == 0) odd++;
            }
        }
        str[j - 1] = ','; //да, додаю кому, найс
        printf("\nSpaces = %d\nOdd words = %d\n", space, odd);
        fputs(str, finalfile);
        fprintf(finalfile, "%d", odd);
        putc('\n', finalfile);
    }
    fclose(newfile); fclose(finalfile);
    remove(new_name);
    rename("temp.txt", new_name);
    free(str);
}

bool check_mode(char *modevalue, int argc, char* argv[]){
    for(int i = 1; i < argc; i++){
        if((strcmp(argv[i], "-mode") == 0) && (i + 1) < argc) return (strcmp(argv[i + 1], modevalue) == 0);
    }
    return false;
}


void file_append_pointer(){
    FILE *fileappend;
    char symb;
    char* append_file = (char*) calloc (30, sizeof(char));
    int i = 0;
    fflush(stdin);
    printf("Enter the name of file: ");
    fgets(append_file, 30, stdin);


    append_file[strlen(append_file) - 1] = '\0';
    printf("\n%s\n", append_file);
    strcat(append_file, ".txt");
    printf("\n%s\n", append_file);

    fileappend = fopen(append_file, "r");
    if (fileappend == NULL) printf("Can`t open a file(((");
    else{
        fclose(fileappend);
        fileappend = fopen(append_file, "a");
        free(append_file);
        printf("Enter the string: ");
        while(true){
            symb = (char) getchar();
            putc(symb, fileappend);
            if(symb == '\n') break;
        }
        fclose(fileappend);
    }

}

void file_append_stream(){
    ofstream appFile;
    ifstream checkapp;
    string name, fileapp;
    char ch;
    cout<<"Enter the name of file: ";
    cin.ignore();
    getline(cin, name);
    fileapp = name + ".txt";
    checkapp.open(fileapp);
    if(!checkapp) cout<<"Can`t open the file(("; //перевіряємо, чи створений вже файл
    else {
        checkapp.close();
        appFile.open(fileapp, ios::app);
        cout<<"Enter the string: ";
    
        while(true){
           ch = cin.get();
           appFile.put(ch);
           if(ch == '\n') break;
    }
    appFile.close();
    }

}

int menu(){

    int pick;


    cout<<"\n\n=========================================================="<<endl;
    cout<<"\n1. Create and fill the file\n2.Append file\nChoose the action: ";
    cin>>pick;
    return pick;

}

void read_file(string name){
    ifstream readFILE;
    string line;

    readFILE.open(name);
    cout<<"\t\n\n=== Name of file: "<<name<<" ==="<<endl;
    if(!readFILE) cout<<"\nHmmm, sometihng wrong...";
    else{
        while(!readFILE.eof()){
            getline(readFILE, line);
            if(line.length() == 0) break;
            cout<<"The line --> "<<line<<endl;
        }
    }
}

void read_file(char* name, int max, int quantity){
    FILE* readfile;
    char *line = (char*) calloc(max + 4, sizeof(char));
    char symb;
    int i = 0;

    readfile = fopen(name, "r");
    cout<<"\t\n\n=== Name of file: "<<name<<" ==="<<endl;

    if(readfile == NULL) cout<<"Hmm, something wrong"<<endl;
    else{
        while(fgets(line, max + 4, readfile) != NULL && i < quantity){ 
            line[strlen(line) - 1] = '\0';
            cout<<"The line --> "<<line<<endl;
            i++;
            memset(line, '\0', strlen(line));
    }
    }
free(line);
}