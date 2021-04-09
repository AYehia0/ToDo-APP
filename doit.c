#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

#define PATH "~/"

void helpMenu(){
    /*Main Menu, which contains help arguments*/        
    printf("ToDo app to orginize you time\n");
    printf("Usage: doit [OPTION] \n");
    printf("Options:\n");
    printf("\t-a, --action\t\tAdd Event in the list\n");
    printf("\t-d, --delete-action\tDeletes an event from the list\n");
}

bool checkValidTime(int *timeArr){
    /*Check if the time is in a valid form*/
 
    int hours = timeArr[0];
    int mins = timeArr[1];
    
    if(hours <= 12 && hours >= 1 && mins > -1 && mins <= 59){
        return true;    
    }

    return false;

}

int *getTimeInput(char *timeStr){
    /*Process the time given from the user*/
    
    //Array to save the given Time
    int *timeContainer = malloc(sizeof(int)*4); 
    
    char temp[20];
    //int timeContainer[2];

    //Spliting on :
    char *token = strtok(timeStr, ":");
   
    //Counter just in case
    int coStrLen = 0; 
    
    while(token != NULL){
        strcpy(temp, token);
        timeContainer[coStrLen++] = atoi(temp);
    
        //pointer to the next index for the token
        token = strtok(NULL, ":");

    }
    return timeContainer;

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

        strftime(date, strlen("HH:MM TT")+1, "%I:%M %p", timeInfo);
    }

    return date;

}

void saveToFile(char *event ){
    char * date;
    
    FILE *pFile;
    pFile = fopen("Test", "a");


    //checking for file
    if(pFile == NULL){
        printf("Error\n");
    }else{

        //checking if File is empty 
        fseek(pFile, 0, SEEK_END);

        if(ftell(pFile) == 0){

            //Getting the date
            date = getTodayDate("d");
    
            //Adding toDay's date
            fputs("########## ", pFile);
            fputs(date, pFile);
            fputs(" ##########\n", pFile);  


        }

        //Writing to the file
        if(strlen(event) > 0){
            //getting time in HH:MM
            date = getTodayDate("h");

            fputs(date, pFile);

            //adding , to seprate 
            fputs(", ", pFile);

            fputs(event, pFile);

            //adding , to seprate 
            fputs(", ", pFile);

        }
        //Closing the file
        fclose(pFile);
    }
    
}

int main(int argc, char *argv[]){
    if(argv[1]!=NULL){
        
        //temp var from args

        char *tempArg = argv[1];
        //Checking for args
        
        printf("You give : %s\n", argv[1]);
        if (checkValidTime(getTimeInput(tempArg))){
            printf("Valid Time: %s\n", argv[1]);
        }else{
            printf("Invalid Time: %s\n", argv[1]);
        }

        printf("You give : %s\n", tempArg);


        //checking for appending
        if(!strcmp("-a", argv[1])==0 || !strcmp("--action", argv[1])==0){

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
