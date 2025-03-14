#include "dbfile.h"
#include "string.h"

void fwrite_table(Table *table, const char* path){
    if(!table){
        LOG_ERROR("Table pointer is null. Wrong writing.\n");
        return;
    }

    FILE *fptr = fopen(path,"w");
    if(!fptr){
        LOG_ERROR("File pointer is null. Wrong writing/path.\n");
        return;
    }

    for(size_t i = 0; i < table->count; ++i){
        Book *book = table->books_arr[i];
        fprintf(fptr,"{%zu|\"%s\"|%u.%u.%u|%.2lf}",
                book->id,book->name,book->date->day,book->date->month,book->date->year,book->price);
        fputc('\n',fptr);
    }

    fclose(fptr);
}


void fread_table(Table *table, const char *path){
    if(!table){
        LOG_ERROR("Table pointer in null. Wrong writing.\n");
        return;
    }
    
    FILE *fptr = fopen(path,"r");
    if(!fptr){
        LOG_ERROR("File pointer is null. Wrong writing/path.\n");
        return;
    }
    
    char str[255]; 
    double price = 0.0;
    unsigned long id = 0; 
    unsigned int day = 0, month = 0, year = 0;

    int res = 0;

    while((res = fscanf(fptr,"{%lu|\"%[^\"]\"|%u.%u.%u|%lf}",&id,str,&day,&month,&year,&price)) == 6){
        Book *book = init_book(str, init_date(year,month,day),price);
        addElement_table(table,book);

        while (fgetc(fptr) != '\n' && !feof(fptr));
    }

    fclose(fptr);
}