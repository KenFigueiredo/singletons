#include <stdio.h>
#include <string.h>

struct table{

    char word[7];
    int value;
    struct table *next;
};

struct table **dictionary;
struct table *helper;

int hash(int tablesize, char string[]){

       int key = 0, i;
       int strlength = (sizeof(string)/sizeof(char));

       for(i = 0; i < strlength ; i++)
                key += string[i] * 3;

        return key % tablesize;
}

void AddToHashTable(int key, char string[]){

        struct table *node = (struct table*)malloc(sizeof(struct table));
                    strcpy(node ->word,string);
                    node -> value = CalculateValue(string);
                    node -> next = NULL;

            if(dictionary[key] == NULL)
                dictionary[key] = node;

            else{
                    helper = dictionary[key];

                    while(helper -> next != NULL)
                        helper = helper -> next;

                        helper -> next = node;
                        helper = node;
            }
}

int CalculateValue(char string[]){

        int pointvalue[26] = {1,3,3,2,1,4,2,4,1,8,5,1,3,1,1,3,10,1,1,1,1,4,4,8,4,10};
        int length = strlen(string);
        int i,points = 0;

        for(i = 0; i < length; i ++)
            points += pointvalue[string[i]-65];

        return points;

}

char* GenerateLetters(){

    int distribution[26] = {9,2,2,4,12,2,3,2,9,1,1,4,2,6,8,2,1,6,4,6,4,2,2,1,2,1};
    char letters[7];
    int i = 0, k;

        while(i < 7){
            k = rand() % (26);

            if(distribution[k] != 0){
                distribution[k]--;
                letters[i] = k +65;
                i++;
            }
        }

    return letters;
}

void FreeAll(int tablesize){
    int i;

        for(i = 0; i < tablesize; i++){

                if(dictionary[i] == NULL){
                    free(dictionary[i]);
                }

                else if(dictionary[i] != NULL && dictionary[i] -> next == NULL){
                    free(dictionary[i]);
                }

                else{
                    helper = dictionary[i] -> next;

                        while(helper -> next != NULL){
                                dictionary[i] -> next = helper ->next;
                                helper -> next = NULL;
                                free(helper);
                                helper = dictionary[i] ->next;
                        }
                }
        }

    free(dictionary);
}

int SearchBucket(int key, char string[]){

        if(dictionary[key] == NULL)
            return -1;

        if(strcmp(dictionary[key]->word,string)==0)
            return dictionary[key]->value;

        helper = dictionary[key];

            while(helper -> next != NULL){

                    if(strcmp(helper->next->word,string) == 0)
                            return helper->next->value;

                    helper = helper -> next;
            }

    return -1;
}

int ValidWord(char input[], char letters[]){

    int i,j;
    int counter = 0;

        for(i = 0; i < strlen(input); i++){
            for(j =0; j < strlen(letters); j++){
                    if(input[i] == letters[j])
                        counter++;
            }
        }

        if(counter >= strlen(input))
            return 1;

        else
            return 0;

}

int main(){

        FILE *ifp = fopen("dictionary.txt","r");

        int n,i,key,choice,val;
          fscanf(ifp,"%d",&n);

        char temp[7], input[7];
         srand(time(0));

        dictionary = (struct table**)malloc(n * sizeof(struct table*));
            for(i = 0; i < n; i ++){
                dictionary[i] = (struct table*)malloc(sizeof(struct table));
                dictionary[i] = NULL;
            }

            for(i = 0; i < n; i++){
                fscanf(ifp,"%s",&temp);
                key = hash(n,temp);
                AddToHashTable(key,temp);
            }
    strcpy(temp,GenerateLetters());

    printf("Welcome to the Scrabble Practice Program!\n");
            while(choice != 4){

                    printf("Your letters are : %s \n \n",temp);
                    printf("What would you like to do? \n");
                    printf("    1 - Enter Word \n");
                    printf("    2 - Reroll Letters \n");
                    printf("    3 - Functionality Test \n");
                    printf("    4 - Quit\n");

                        scanf("%d",&choice);

                                    if(choice == 1){
                                        printf("Word: ");
                                        scanf("%s", &input);

                                            if(ValidWord(input,temp) == 1){

                                                    key = hash(n,input);
                                                    val = SearchBucket(key,input);

                                                        if(val != -1)
                                                            printf("%s is a valid word worth %d points. \n",input,val);

                                                        else
                                                            printf("%s is not a valid word. \n",input);
                                            }

                                            else
                                                printf("You do not have the letters to make the word %s. \n",input);
                                    }

                                    if(choice == 2){
                                        strcpy(temp,GenerateLetters());
                                    }

                                    if(choice == 3){
                                        strcpy(temp, "SHABCTC");
                                    }

                                    if(choice == 4){
                                        break;
                                    }

                printf("\n");
            }

    FreeAll(n);
    fclose(ifp);

    return 0;
}
