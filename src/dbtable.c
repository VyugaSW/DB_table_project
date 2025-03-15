#include "dbtable.h"

Table * table_init(){
    Table *table = (Table*)malloc(sizeof(Table));
    if(!table){
        LOG_ERROR("Memory was not allocated for the table.\n");
        return NULL;
    }
    
    table->size = TABLE_INITIAL_SIZE;
    table->books_arr = (Book **)calloc(table->size, sizeof(Book*));
    table->count = 0;
    if(!table->books_arr){
        LOG_ERROR("Memory was not allocated for books_arr.\n");
        return NULL;
    }

    return table;
}

void table_addElement(Table *table, Book *book){
    if(!table || !book){
        LOG_ERROR("Adding failed: table or book is NULL.\n");
        return;
    }

    if (table->count >= table->size) {
        size_t new_size = table->size * 2;
        if (new_size <= TABLE_SIZE_MAX) {  
            table_resize(table, new_size);
        } 
        else {
            LOG_ERROR("Resizing failed: size would overflow.\n");
            return;
        }
    }
    
    book->id = table->count;
    table->books_arr[table->count++] = book_copy(book);
}

void table_resize(Table *table, size_t new_size) {
    if (!table) {
        LOG_ERROR("Resizing failed: table is NULL.\n");
        return;
    }

    Book **temp = realloc(table->books_arr, new_size * sizeof(Book*));
    if (!temp) {
        LOG_ERROR("Memory allocation failed for resizing. Current data is preserved.\n");
        return;  
    }

    table->books_arr = temp;
    table->size = new_size;
}

void table_delElement(Table *table, size_t id){
    if(!table || table->count < id){
        LOG_ERROR("Deleting failed: invalid table or ID.\n");
        return;
    }

    for(size_t i = id; i < table->count-1; ++i){
        table->books_arr[i] = table->books_arr[i+1];
        --table->books_arr[i]->id;
    }

    --table->count;

    if (table->count < table->size / 4 && table->size > TABLE_INITIAL_SIZE) {
        size_t new_size = table->size / 2;
        table_resize(table, new_size);
    }
}

void table_free(Table *table){
    if(!table){
        LOG_ERROR("Freeing of table is false.\n");
        return;
    }

    for(size_t i = 0; i < table->count; ++i)
        book_free(table->books_arr[i]);

    free(table->books_arr);
    free(table);
}

void table_print(const Book ** books_arr, size_t count){
    if(!books_arr){
        LOG_ERROR("Books array is null. Wrong printing.\n");
        return;
    }
    
    printf("----Table is:\n");
    for(size_t i = 0; i < count; ++i){
        const Book *book = books_arr[i];
        printf("Id: %zu | Name: \"%s\" | price: %lf\n",book->id, book->name, book->price);
    }
}

void table_sort(Table *table, bool flag, ECmp_by compare_by){
    for (size_t i = 0; i < table->count-1; i++) {
        size_t min_index = i;
        for (size_t j = i + 1; j < table->count; j++) {
            if (flag ? !book_compare(table->books_arr[j], table->books_arr[min_index], compare_by) : book_compare(table->books_arr[j], table->books_arr[min_index], compare_by)) 
                min_index = j;
        }

        if (min_index != i) {
            Book *temp = table->books_arr[i];
            table->books_arr[i] = table->books_arr[min_index];
            table->books_arr[min_index] = temp;
        }
    }
}