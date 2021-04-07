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

char *getTodayDate(char whichTime[1]){

    /*Get Today's Date*/
 
    char * date;
    date = malloc(sizeof(char)*50);
    time_t rawTime;

    struct tm *timeInfo;

    time(&rawTime);
    timeInfo = localtime(&rawTime);

   
    // Day Calender
    if(strcmp("d", whichTime) == 0){
        
        strftime(date, strlen("DD-MMM-YYYY")+1, "%d-%b-%Y", timeInfo);
        
    }else{
        //must be Time in hours

        strftime(date, strlen("HH:MM")+1, "%H:%M", timeInfo);
    }

    return date;

}

void saveToFile(char *event ){
    char * date;
    
    FILE *pFile;
    pFile = fopen("Test", "a");

    //Getting the date
    date = getTodayDate("d");
    

    //checking for file
    if(pFile == NULL){
        printf("Error\n");
    }else{

        //checking if File is empty 
        fseek(pFile, 0, SEEK_END);

        if(ftell(pFile) == 0){

            //Adding toDay's date
            fputs("########## ", pFile);
            fputs(date, pFile);
            fputs(" ##########\n", pFile);  


        }

        //Writing to the file
        if(strlen(event) > 0){
            fputs(event, pFile);

            //adding , to seprate 
            fputs(",", pFile);

            //Adding a newline
            fputs(" ", pFile);
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
            if(argv[2] != NULL){
                //Writing to the file

                //Writing the date
                saveToFile(argv[2]);

            }else{
                printf("Invalid Input, What do you want to do?\n");
                helpMenu();
            }
        }
    }else{
        helpMenu();
    }

    return 0;
}
