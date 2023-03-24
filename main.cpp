#include "temp.h"

//using namespace std;

int main(int argc, char* argv[]){
    int way, max_size, quantity_of_notes, new_quantity, pick;
    string name_of_file, new_name_of_file;
    char name[30], new_name[35];

    if(check_mode("FilePointer", argc, argv)){
        cout<<"\t---You are working in FilePointer mode---"<<endl;
        max_size = 0; quantity_of_notes = 0; new_quantity = 0;
        memset(name, '\0', strlen(name));
        memset(new_name, '\0', strlen(new_name));
        fflush(stdin);

        do{pick = menu();
        
        if(pick == 1){
        create_file(name);
        for(int i = 0; i < strlen(name); i++) printf("%c", name[i]);//перевіряю ім'я файлу
        printf("\n\n");

        quantity_of_notes = fill_file(name, max_size);
        printf("\nMax Size = %d", max_size);
        new_quantity = encrypt_notes(max_size, name, new_name, quantity_of_notes);
        //printf("\nNew quan = %d", new_quantity);
        printf("\n\n");

        quan_of_odd_words(new_name, new_quantity, max_size);
        read_file(name, max_size, quantity_of_notes);
        read_file(new_name, max_size, new_quantity);


        }
        else if(pick == 2) file_append_pointer();
        cout<<"Do you want to try again --> Enter to continue, any other key to finish: ";
    }while(getchar() == '\n');
    }
    else if (check_mode("FileStream", argc, argv)) {
        cout<<"\t---You are working in FileStream mode---"<<endl;
        quantity_of_notes = 0; new_quantity = 0;
        name_of_file = "";
        new_name_of_file = "";
        cin.ignore();

        do{pick = menu();
        if(pick == 1){
        fill_the_file(name_of_file, quantity_of_notes);
        cout<<name_of_file<<" "<<quantity_of_notes;
        cout<<"\n\n\n\n\n";
        new_quantity = recreate_notes(name_of_file, quantity_of_notes, new_name_of_file);
        add_coma_and_quan(new_name_of_file,  new_quantity);
        read_file(name_of_file);
        read_file(new_name_of_file);
        }
        else if(pick == 2) file_append_stream();
        cout<<"Do you want to try again --> Enter to continue, any other key to finish: ";
    }while(getchar() == '\n');
    }
    else cout<<"\nHmmm, error"<<endl;

    return 0;

}