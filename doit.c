#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void helpMenu(){
    /*Main Menu, which contains help arguments*/        
    printf("ToDo app to orginize you time\n");
    printf("Usage: doit [OPTION] \n");
    printf("Options:\n");
    printf("\t-a, --action\t\tAdd Event in the list\n");
    printf("\t-d, --delete-action\tDeletes an event from the list\n");
}

int main(int argc, char *argv[]){
    if(argv[1]!=NULL){
        printf("not null");

    }else{
        helpMenu();
    }

    return 0;
}
