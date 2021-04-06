#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define PATH "~/"

void helpMenu(){
    /*Main Menu, which contains help arguments*/        
    printf("ToDo app to orginize you time\n");
    printf("Usage: doit [OPTION] \n");
    printf("Options:\n");
    printf("\t-a, --action\t\tAdd Event in the list\n");
    printf("\t-d, --delete-action\tDeletes an event from the list\n");
}

char *getTodayDate(){
    /*Get Today's Date*/

    char * date;
    date = malloc(sizeof(char)*50);
    time_t rawTime;

    struct tm *timeInfo;

    time(&rawTime);
    timeInfo = localtime(&rawTime);
    strftime(date, strlen("DD-MMM-YYYY")+1, "%d-%b-%Y", timeInfo);

    return date;

}

void saveToFile(){

}

int main(int argc, char *argv[]){
    if(argv[1]!=NULL){
        printf("not null");

    }else{
        helpMenu();
        char * d; 
        d = getTodayDate();
       printf("%s", d);
    }

    return 0;
}
