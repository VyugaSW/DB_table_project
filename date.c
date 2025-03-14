#include "date.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Date * init_date(unsigned year, unsigned month, unsigned day){
    Date *date = (Date *)malloc(sizeof(Date));
    if(!date){
        LOG_ERROR("Memory was not allocated for the date.\n");
        return NULL;
    }

    date->year = year;
    date->day = day;
    date-> month = month;

    return date;
}

bool datecmp(Date *date1, Date *date2){
    if(date1->year > date2->year) return true;
    else if(date1->year == date2->year){
        if(date1->month > date2->month) return true;
        else if(date1->month == date2->month){
            if(date1->day > date2->day) return true;
            return false;
        }

        return false;
    }
    
    return false;
}

Date *copy_date(Date *date){
    if(!date){
        LOG_ERROR("Copying date is false.\n");
        return NULL;
    }

    return init_date(date->day,date->month,date->year);
}

Date *stringToDate(const char* dateStr){
    char dayStr[3] = {0};
    char monthStr[3] = {0};
    char yearStr[5] = {0};

    strncpy(dayStr, dateStr, 2);       
    strncpy(monthStr, dateStr + 3, 2); 
    strncpy(yearStr, dateStr + 6, 4);  


    Date *date = init_date((unsigned int)atoi(dayStr), (unsigned int)atoi(monthStr), (unsigned int)atoi(yearStr));

    return date;
}