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
    printf("\t-s, --start-time\tStarting of the event in 12H format\n");
    printf("\t-e, --end-time\tEnding of the event in 12H format\n");
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
    
    //int timeContainer[2];

    //Spliting on :
    char *token = strtok(timeStr, ":");
   
    //Counter just in case
    int coStrLen = 0; 
    
    while(token != NULL){ 
        //atoi converts string to int
        timeContainer[coStrLen++] = atoi(token);
    
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
    /*Saving event+startingTime+endingTime to a file, later would be used to send notificatio connected to crontab*/
    char * date;
    
    FILE *pFile;
    pFile = fopen("Test", "a");
    //For counting lines    
    int ctr = 0;    

    char c; 

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
            fputs(event, pFile);
        }
        //Closing the file
        fclose(pFile);
    }
}

int main(int argc, char *argv[]){
    char prefix[100] = "";
    //Probably Switch-Case is a better way to do this, idk 

    if(argv[1]!=NULL){
        
        //checking for appending
        if( (!strcmp("-a", argv[1])==0 || !strcmp("--action", argv[1])==0) ) {
            if(argv[2] != NULL && argv[3] != NULL){
                if (!strcmp("-s", argv[3]) == 0 || !strcmp("--start-time", argv[3]) == 0 ){
                    if(argv[4] != NULL && argv[5] != NULL){
                        if(!strcmp("-e", argv[5]) == 0 || !strcmp("-end-time", argv[5]) == 0){
                            if(argv[6] != NULL){
                                //temp var from args
                                char tmpStart[20];
                                char tmpEnd[20]; 
                                //copying the arg to a temp, as it changes for some reasons
                                memset(tmpStart, '\0', sizeof(tmpStart));
                                strcpy(tmpStart, argv[4]);

                                memset(tmpEnd, '\0', sizeof(tmpEnd));
                                strcpy(tmpEnd, argv[6]);
                
                                if (checkValidTime(getTimeInput(argv[4])) && checkValidTime(getTimeInput(argv[6])) ){

                                    //Writing the data , better way to do it
                                    sprintf(prefix,"%s;%s;%s\n",argv[2],tmpStart,tmpEnd);
                                    saveToFile(prefix);
                                

                                    printf("ToDo List Has Been Updated !!\n");
                                }else{
                                    printf("Invalid Time !! \n\n");
                                    helpMenu();
                                    exit(0);
                                }
   
                            }else{
                                printf("Some missing args !!\n\n");
                                helpMenu();
                            }
                        }else{
                            printf("Some missing args !!\n\n");
                            helpMenu();
                        } 
                    }
                    else{
                        printf("Some missing args !!\n\n");
                        helpMenu();
                    }
                }
                else{
                    printf("Some missing args !!\n\n");
                    helpMenu();
                }
            }
            else{
                printf("Some missing args !!\n\n");
                helpMenu();
            }

        }else{
            printf("Some missing args !!\n\n");
            helpMenu();
        }
    }else{
        helpMenu();
    }
}
