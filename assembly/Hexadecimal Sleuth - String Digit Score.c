#include <stdio.h>
#include <string.h>
#include <math.h>

// Kenneth Figueiredo - Project 2 : prototype.c
// Functional lines (without functions): 13
// Functional lines (with functions): 20

// Test Sentences *******************************************************************************
//   "I ACED THE EXAM AND EARNED AN A PLUS."
//   "BEEF BRISKET ON BED OF LETTUCE FOR 99 CENTS."
//   "FADED OUT AND FAD3D IN."
//***********************************************************************************************

// Function explantation ************************************************************************
//    int decToHex - Takes in a word, and its start and end points in the sentence. Converts
//                   "Hex" string to decimal
//    int getScore - Takes in a converted hex string and scores it based on the given parameters 
//                   in the task description.
// **********************************************************************************************

// variable explanations ************************************************************************
//    char sentence - Holds the string which is being tested
//    int i - holds the current position of where the loop is in sentence variable
//    int j - iterates from the current posistion(i) until end of word.
//    int valid - holds whether or not the current word can be converted to hex. 1 for valid, 0 for invalid
//    int deciWord - holds the value of the current word's hex value in decimal
//    int score - temporary score storage for a current word
//    int maxScore - holds max score for the current sentence | 0 - sparse , 1 - intermediate, 2- plentiful
//    int k - iterates from i to j to print out an invalid word.
//    int loop - keeps the programming running until the '\0' character has been reached
//***********************************************************************************************

main(){
    
   char sentence[200] = "I ACED THE EXAM AND EARNED AN A PLUS.";   
   int score = 0, maxScore = 0, i = 0, deciWord = 0, valid = 1, loop = 0, j, k;
        while(loop == 0){           
            j = i;
            while(1){
                if(sentence[j] == '\0') loop = 1;
                if(sentence[j] == ' ' || sentence[j] == '\0') break;
                if((sentence[j] < 65 || sentence[j] > 70) && (sentence[j] < 48 || sentence[j] > 57)) valid = 0;
                j++;
            }if(valid == 1){
                deciWord = decToHex(sentence, i, j);
                score = getScore(deciWord);    
                if(score > maxScore) maxScore = score;
                printf("%d ", deciWord);
            }else for(k = i; k <= j; k++) printf("%c", sentence[k]);
            valid = 1; i+=(j-i+1);
        }           
    if(maxScore == 0) printf("\nSparse\n");      
    else if(maxScore == 1) printf("\nIntermediate\n");   
    else printf("\nPlentiful\n");
    
    getc(stdin);
    
}

int decToHex(char* hex, int start, int end){  
    int k, sum = 0;
    for(k = 0; k < (end - start); k++){      
        if(hex[end-k-1] > 64 && hex[end-k-1] < 71) sum += (hex[end-k-1] - 55) * pow(16,k);                           
        else sum += (hex[end-k-1] - 48) * pow(16,k);      
    } return sum;
}

int getScore(int hexword){
    if(hexword >= 0 && hexword <= 255) return 0;    
    else if(hexword >= 256 && hexword <= 65535) return 1;  
    else return 2;     
}


