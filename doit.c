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

void saveToFile(char *event ){
    FILE *pFile;
    pFile = fopen("Test", "w");

    //checking for file
    if(pFile == NULL){
        printf("Error\n");
    }else{

        //Writing to the file
        if(strlen(event) > 0){
            fputs(event, pFile);

            //adding , to seprate 
            fputs(",", pFile);

            //Adding a newline
            fputs("\n", pFile);
        }
        //Closing the file
        fclose(pFile);
    }
    
}

int main(int argc, char *argv[]){
    if(argv[1]!=NULL){

        //Checking for args

        //checking for appending
        if(strcmp("-a", argv[1])==0 || strcmp("--action", argv[1])==0){

            //Checking for the second arg
            if(strlen(argv[2]) > 0){
                //Writing to the file
                saveToFile(argv[2]);
            }
        }
    }else{
        helpMenu();
        char * d; 
        d = getTodayDate();
       printf("%s", d);
    }

    return 0;
}
