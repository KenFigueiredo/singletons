/* Kenneth Figueiredo
 * Assignment 1 - mysh.c
 * COP4600 - Bölöni 
 * 2/1/2014
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>


// Declaration of primary functions
void empty(int finish, char** args, int* PIDS);
void run(int PID, int usrKey, int error, int i, char **args, char path[100]);
void background(int PID, int *PIDS, int *PIDCount, int i, int usrKey, int error, char **args, char path[100]);
void murder(int kPID, int *PIDS, int *PIDCount, int error);

//Declaration of extra credit functions
void repeat(int PID, int *PIDS, int *PIDCount, int usrKey, int error, int i, int repeats, char ncommand[11], char **args, char path[100]); 
void murderall(int *PIDS, int *PIDCount, int error);

int main(){

    int PID, usrKey, error;
    int i, kPID;
    int looper = 0;

    int *PIDS;
    int *PIDCount;

    char **args;
    char path[100];
    char command[11];

    system("clear");
    
    PIDS = (int*)malloc(sizeof(int) * 500);
    args = (char**)malloc(sizeof(char*)*100);
    PIDCount = (int*)malloc(sizeof(int));

// While loop that will keep the program running until the user enters quit.
    while(looper == 0){
        
	printf("# ");
        scanf("%s", command);
	
	//Case 1) If the command entered is "run":
	    if(strcmp(command, "run") == 0){
	    
	    //Read in the run path.	
		i = 1;
		scanf("%s", path);	
		
		args[0] = (char*)malloc(sizeof(char)*100);
		strcpy(args[0], path);	
	    
	   //Special Case: running mysh.				
		if(strcmp(path, "./mysh") == 0){
		  args[2] = (char*)malloc(sizeof(char)*100);
		  strcpy(args[2], path);

		  args[1] = (char*)malloc(sizeof(char)*11);
		  strcpy(args[1], "-e");

		  strcpy(path, "xterm");
		  i = 3;	
		}

	    usrKey = getc(stdin);

           //Read in until the user is done entering arguments for the path.	   
		while(usrKey != '\n'){			
		      args[i] = (char*)malloc(sizeof(char)*11);
		      scanf("%s", args[i]);
		
		      usrKey = getc(stdin);
		      i++;
		}

    	   //call to the run function		
		run(PID, usrKey, error, i, args, path);

           //Reset the variables used to avoid future conflicts.
		i = 1; error = 0; usrKey = 'a'; 
		empty(0, args, PIDS);
	    }

       //Case 2) If the command entered is "background":
	    else if(strcmp(command, "background") == 0){
	
	    //Read in the run path.	
		i = 1;
		scanf("%s", path);	
		
		args[0] = (char*)malloc(sizeof(char)*100);
		strcpy(args[0], path);	
	    
	   //Special Case: running mysh.				
		if(strcmp(path, "./mysh") == 0){
		  args[2] = (char*)malloc(sizeof(char)*100);
		  strcpy(args[2], path);

		  args[1] = (char*)malloc(sizeof(char)*11);
		  strcpy(args[1], "-e");

		  strcpy(path, "xterm");
		  i = 3;		
		}

	    usrKey = getc(stdin);		

           //Read in until the user is done entering arguments for the path.			   
		while(usrKey != '\n'){			
		      args[i] = (char*)malloc(sizeof(char)*11);
		      scanf("%s", args[i]);
		
		      usrKey = getc(stdin);
		      i++;
		}

    	   //call to the background function
	    	background(PID, PIDS, PIDCount, i, usrKey, error, args, path);

           //Reset the variables used to avoid future conflicts.
		i = 1; error = 0;
		usrKey = 'a'; empty(0, args, PIDS);
	    }

       //Case 3) If the command entered is "murder", call the murder function     
	    else if(strcmp(command, "murder") == 0)
		murder(kPID, PIDS, PIDCount, error);

       //Extra Case 1) If the command entered is "murderall", call the murderall function  
	    else if(strcmp(command, "murderall") == 0)
		murderall(PIDS, PIDCount, error);	    

       //Extra Case 2) If the command entered is "repeat", call the repeat function 
	    else if(strcmp(command, "repeat") == 0){
	
		int repeats;
		scanf("%d", &repeats);	
	
		char ncommand[11];
		scanf("%s", ncommand);

	    //If the new command entered is "run" or "background" run until user is done entering arguments
	    //Same code as above for both functions.
		if(strcmp(ncommand, "run") == 0 || strcmp(ncommand, "background") == 0){

	   		 //Read in the run path.	
				i = 1;
				scanf("%s", path);	
		
				args[0] = (char*)malloc(sizeof(char)*100);
				strcpy(args[0], path);	
	    
			 //Special Case: running mysh.				
				if(strcmp(path, "./mysh") == 0){
				  args[2] = (char*)malloc(sizeof(char)*100);
				  strcpy(args[2], path);

				  args[1] = (char*)malloc(sizeof(char)*11);
				  strcpy(args[1], "-e");

				  strcpy(path, "xterm");
				  i = 3;		
				}

			    usrKey = getc(stdin);			
		
	           //Read in until the user is done entering arguments for the path.	   
			while(usrKey != '\n'){			
			      args[i] = (char*)malloc(sizeof(char)*11);
			      scanf("%s", args[i]);
		
			      usrKey = getc(stdin);
			      i++;
			}
		 }

             //Call to repeat function
	       repeat(PID, PIDS, PIDCount, usrKey, error, i, repeats, ncommand, args, path);
	    }   

	  //Extra Command 1) "clear" - clears the console
	    else if(strcmp(command, "clear") == 0)
	    	system("clear");
	  
       //Case 3) If the command entered is "quit", clear the screen, free all used data and return.     
 	    else if(strcmp(command, "quit") == 0){
		system("clear");
		empty(1, args, PIDS);
		looper = 1;
		return(0);
	    }
	
	//Else invalid command    	    
	    else
		printf("# ERROR: Invalid command (%s)\n", command);
    }
}

/* Function: Empty(int finish, char** args, int* PIDS)
 * Depending on what finish is (0 for soft reset, 1 for final reset) the function will
 * free all malloc'd data.
 */
void empty(int finish, char** args, int* PIDS){
	     
   int i;
     if(finish == 0){
	for(i = 0; i < 99; i++){
	   free(args[i]);
	   args[i] = NULL;
	}
     }

     else{		  
	free(args);
	free(PIDS);
     }     
}

/* Function: run(int PID, int usrKey, int error, int i, char **args)
 * Run function which will call fork to split the current to a parent and child.
 * The child denoted by PID == 0 will then call exec to run the program with the arguments
 * the user provided above. If the exec function returns a -1, the path of the designated program
 * was not found. The parent will hang until the child process is terminated.
 */
void run(int PID, int usrKey, int error, int i, char **args, char path[100]){

	args[i] = (char *) 0;
	PID = fork();

	if(PID == 0)
           error = execvp(path, args);
		
	if(error == -1)
	   printf("# ERROR: Path not found (%s) \n",path);		
				
	else
	   wait(NULL);

}

/* Function: background(int PID, int *PIDS, int *PIDCount, int i, int usrKey, int error, char **args)
 * background function which will call fork to split the current to a parent and child.
 * The child denoted by PID == 0 will then call exec to run the program with the arguments
 * the user provided above. If the exec function returns a -1, the path of the designated program
 * was not found. The parent will NOT hang, and will continue after the child is executed. The PID of the
 * child is saved in the PIDS array for future use in the murderall function.
 */
void background(int PID, int *PIDS, int *PIDCount, int i, int usrKey, int error, char **args, char path[100]){

	  args[i] = (char *) 0;
	  PID = fork();

	  if(PID == 0)
	     error = execvp(path, args);
		
	  if(error == -1)
	     printf("# ERROR: Path not found (%s) \n",path);		

	  if(PID != 0){
	     printf("# Process ID : %d \n", PID);
	     
	     int j;

	     for(j = 0; j < 500; j++){
	     
		if(PIDS[j] == 0){
		   PIDS[j] = PID;
		   PIDCount[0]++;
		   break;		
		}

	     }
	  }		
}

/* Function: murder(int kPID, int *PIDS, int *PIDCount, int error)
 * murder function which will wait for user input of a PID to kill. The process
 * that matches the entered PID will be killed and the system will prompt the user that
 * it has been successfully ended. If it cannot be kiled, an error will be displayed. The killed
 * PID will be removed from the PIDS array for future use in the murderall function.
 */
void murder(int kPID, int *PIDS, int *PIDCount, int error){
	
	scanf("%d", &kPID);	

	int j;
	for(j = 0; j < 500; j++){
	
	    if(PIDS[j] == kPID){

	        if(kill(PIDS[j], 0) == -1){
		    PIDS[j] = 0;
		    printf("# ERROR: Shell failed to murder process (%d) \n", kPID);
		    break;
	        }

		error = kill(kPID, SIGKILL);

		if(error == -1)
	  	   printf("# ERROR: Shell failed to murder process (%d) \n", kPID);

		else{
	   	   printf("# Process successfully ended \n");	    
		   PIDS[j] = 0;
		   PIDCount[0]--;
		}
		
		break;
	    }

	    if(PIDCount == 0)
		break;	
	}
}

/* Function: murderall(int *PIDS, int *PIDCount, int error)
 * murderall function which will kill all processes. The killed
 * PIDs will be removed from the PIDS array, and the user will be notified
 * which process PIDS have been terminated.
 */
void murderall(int *PIDS, int *PIDCount, int error){

	int j;

	printf("# Murdering %d processes: ", PIDCount[0]);
	
	for(j = 0; j < 500; j++){
	    
	    if(kill(PIDS[j], 0) == -1)
		PIDS[j] = 0;

	    if(PIDS[j] != 0){
		printf("%d ",PIDS[j]);
		kill(PIDS[j], SIGKILL);
		PIDS[j] = 0;
		PIDCount[0]--;
	    }

	    if(PIDCount == 0)
		break;	
	}
	
	printf("\n");
}

/* Function: repeat(int PID, int *PIDS, int *PIDCount, int usrKey, int error, int i, int repeats, char ncommand[11], char **args)
 * repeat function which will repeat a given command n times (based on count). Only run & background are acceptable commands for
 * the repeat function.
 */
void repeat(int PID, int *PIDS, int *PIDCount, int usrKey, int error, int i, int repeats, char ncommand[11], char **args, char path[100]){
	
	int count;		
	
	for(count = 0; count < repeats; count++){
		
		if(strcmp(ncommand,"murder") == 0){
		   printf("# ERROR: murder is not a valid command for repeat, aborting repeat \n");
		   break;
		}		
		
		else if(strcmp(ncommand, "run") == 0)
		   run(PID, usrKey, error, i, args, path);

		else if(strcmp(ncommand, "background") == 0)
		   background(PID, PIDS, PIDCount, i, usrKey, error, args, path);
		
		else{
		  printf("# ERROR: Invalid command (%s), aborting repeat \n", ncommand);
		  break;
		}
	}

	if(strcmp(ncommand, "run") == 0 || strcmp(ncommand, "background")){
	   i = 1; error = 0;
	   usrKey = 'a'; empty(0, args, PIDS);
	}
}
