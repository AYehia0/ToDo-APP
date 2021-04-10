#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <unistd.h>  // access() to check for the exitstance of a file 

#define PATH "~/"
#define FILENAME "Test"

void helpMenu(){

    /*Main Menu, which contains help arguments*/        
    
    printf("ToDo app to orginize you time\n");
    printf("Usage: doit [OPTION] \n");
    printf("Options:\n");
    printf("\t-a, --action\t\tAdd Event in the list\n");
    printf("\t-d, --delete-action\tDeletes an event from the list\n");
    printf("\t-s, --start-time\tStarting of the event in 12H format\n");
    printf("\t-e, --end-time\tEnding of the event in 12H format\n");
    printf("\t-l, --show-list\tShowing the todo list and exit\n");
    
    //example
    printf("\n\nExample: doit -a \"Something\" -s 10:23 -e 12:24\n");
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
int getNumLines(char *filename){
    /*Counting the the lines in a file*/

    FILE *fp = fopen(filename,"r");

    int ch=0;

    // counter for lines 
    int lineCounter = 0;

    if (fp == NULL){
        return 0;
    }

    lineCounter++;

    while ((ch = fgetc(fp)) != EOF){
        if (ch == '\n'){
            lineCounter++;
        }
    }

    fclose(fp);
    return lineCounter;
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

void deleteLine(int lineNumber){
    /*Using sed (linux specific)to delete a line by its number*/
    char lineStr[20];

    //check if file exits
    if(access(FILENAME, F_OK) == 0){

        sprintf(lineStr, "sed -i '%dd' %s", lineNumber + 1, FILENAME);

        //executing
        system(lineStr);
    }else{
        //file doesn't exist
        printf("You didn't create list \n");
        exit(0);
    }
}
void showList(){

    //checking if file exists or not
    if(access(FILENAME, F_OK) == 0){
        system("cat Test");
    }else{
        //file doesn't exist
        printf("You didn't create list \n");
        exit(0);
    }
}

int main(int argc, char *argv[]){
    
    //Temp to save the line to be added to the file
    char prefix[100] = "";

    int lines = abs(getNumLines("Test") - 1); 

    //Probably Switch-Case is a better way to do this, idk 

    if(argv[1]!=NULL){
        if(strcmp("-l", argv[1]) == 0){
            showList();
            exit(0);
        }
        if(argv[2]!=NULL){
            if(strcmp("-d",argv[1]) == 0){
                //delete a line and exit
                int lineNum = atoi(argv[2]);
                deleteLine(lineNum);
                exit(0);
            }
        }
        //checking for appending
        if( (!strcmp("-a", argv[1]) == 0 || !strcmp("--action", argv[1]) == 0) ) {
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
                                    sprintf(prefix,"%d;%s;%s;%s\n",lines,argv[2],tmpStart,tmpEnd);
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
