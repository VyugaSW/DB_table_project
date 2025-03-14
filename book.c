#include "book.h"
#include <string.h>

Book * init_book(char* name, Date *date, double price){
    if(!name || !date){
        LOG_ERROR("Creating element is false\n");
        return NULL;
    }

    Book *book = (Book *)malloc(sizeof(Book));
    if(!book){
        LOG_ERROR("Memory was not allocated for the element.\n");
        return NULL;
    }

    book->name = (char *)malloc((strlen(name)+1)*sizeof(char));
    strcpy(book->name,name);
    book->date = date;
    book->price = price;
    book->id = 0;

    return book;
}

bool compare_books(Book *book1, Book *book2, ECmp_by compare_by){
    if(!book1 || !book2){
        LOG_ERROR("Comparing books is false.\n");
    }
    
    switch (compare_by)
    {
    case ID:
        return book1->id > book2->id;

    case NAME:
        return strcmp(book1->name, book2->name);

    case BOOK_DATE:
        return datecmp(book1->date, book2->date);

    case PRICE:
        return book1->price > book2->price;

    default:
        break;
    }

    return false;
}

Book *copy_book(Book *book){
    if(!book){
        LOG_ERROR("Copy book is false.\n");
    }
    Book *new_book = init_book(book->name,copy_date(book->date),book->price);
    new_book->id = book->id;
    return new_book;
}

void free_book(Book *book){
    if(!book){
        LOG_ERROR("Freeing book is false.\n");
    }

    free(book->name);
    free(book->date);
    free(book);
}