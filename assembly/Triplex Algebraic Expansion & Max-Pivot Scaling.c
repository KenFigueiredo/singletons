# Project 1: Triplex Algebraic Expansion / Max-Pivot Scaling
# Kenneth Figueiredo - Ken.Figueiredo@knights.ucf.edu
# EEL 3801C - Due: 9/19/2014
# Final Submission: 9/19/2014

int main(void){
 
	//Declaration of all integers to be used
		int a, b, c, f, g, max;
		int i, sum1, sum2, tempF;
	
	//Read in values of a , b, c
		printf("Enter 3 integers for a,b,c respectively: \n");
		scanf("%d %d %d" &a, &b, &c);

	// Part A: Find the value of F   
		sum1 = 0, sum2 = 0;

			for(i = 0; i < b; i++){
				sum1 += a;
			}

			for(i = 0; i < c; i++){
				sum2 += sum1;
			}

		f = a + sum1 + sum2;
		
	// Part B: Find the max, then find G
		//Find max of a , b, c
			if(a > b){
				if(b > c)
					max = a;
				
				else{
					if(a > c)
						max = a;
					else
						max = c;
				}
			}
			
			else{
				if(a > c)
					max = b;
				
				else{
					if(b > c)
						max = b;
					else
						max = c;			
				}
			}
		
		// divide F by max to find g
			tempF = f;
			for(i = 0; tempF < 0; i++){
				tempF -= max;
			}
			
		//Find the remainder, if any.
			if(tempF < 0){
				tempF += max;
				i--;
			}
				
	//Print out all required values:
	
		//Print F in decimal
			printf("f_ten: %d \n",f);
		
		//Print F in binary
			printf("f_two: ");	
				int d, k;
				  for (d = 31; d >= 0; d--){
					   k = f >> d;
						 
						 if (k & 1)
							printf("1");
						 else
							printf("0");
				  }
			 printf("\n");               
		
		//Print G
			printf("g_quotient =  \n", g);
			
		//print remainder (if any)
			printf("g_remainder = ", tempF);
			
				if(tempF != 0)
					printf(" / %d", max);
	
system ("pause");
return 0;
}
