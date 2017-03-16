/* Kenneth Figueiredo
   COP3330 - 0001
   FizzBuzz.java
  */
  
 import java.util.*;

public class FizzBuzz{

	public static void main(String args[]){
	
		Scanner parameters = new Scanner(System.in);
		int [] a = new int [20];
		int [] b = new int [20];
		int i = 0;
		int x, j;

//Scan of all values between a and b 
	do{
		  a[i] = parameters.nextInt();
		  b[i] = parameters.nextInt();
		  i++; 		  
	}while((a[i - 1] != 0)&& (b[i - 1] != 0));
		
		
			for(j = 0;j < i - 1 ; j++){
				for(x = a[j]; x < b[j] + 1; x++){
				
				//If the a value is divisible by 3 or 5 FizzBuzz gets printed.
					if(a[j] % 3 == 0 && a[j] % 5 == 0)
						System.out.println("FizzBuzz");
				
				//If the a value is divisible by 3 Fizz gets printed.	
					else if(a[j] % 3 == 0)
						System.out.println("Fizz");
				
				//If the a value is divisible by 5 FizzBuzz gets printed.				
					else if(a[j] % 5 == 0)
						System.out.println("Buzz");
				
				//else the program will print out the value of a[j]
					else
						System.out.printf("%d \n",a[j]);
					a[j] ++;

				}
			
			}

	
	}
}
		
	
		