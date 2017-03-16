/* Kenneth Figueiredo
   COP3330 - 0001
   KthElement.java
  */

import java.util.*;

public class KthElement{

	public static void main(String[] args){
	
		int[][] array = new int[100][100];
		int[] k = new int[100];
		int[] numcount = new int[100];
		int[] temparray = new int[100];
		
		Scanner input = new Scanner(System.in);
		int x = 1;
		int cnt;
		int j = 1;
		int a = 1;
		
	
		do{
		
		//Scan of the number count.
			numcount[x] = input.nextInt();
		
		// Loop that scans every interger group and the groups k value		
			if(numcount[x] != 0){
				for(cnt = 1; cnt <= numcount[x]; cnt ++)
					array[x][cnt] = input.nextInt();
						
				k[x] = input.nextInt();
			}
			x++;
			
		}while(numcount[x-1] != 0);
		
		
		
		for(cnt = 1; cnt <= x; cnt++){
		
		//Declaration of temparray to equal k so we have a constant value to increment by.
			temparray[cnt] = k[cnt];
		
			while(k[cnt] < numcount[cnt]){
			
			//Loop that prints ever K value then places a , after every value except the new.
				for(j = 1 ;j <= numcount[cnt] / temparray[cnt]; j++){
					System.out.printf("%d", array[cnt][k[cnt]]);
						k[cnt] = k[cnt] + temparray[cnt];
						
						if(k[cnt] <= numcount[cnt])
							System.out.printf(", ");
				}

				System.out.printf("\n");
				a++;
			}
		}
	}
}	
			

		
				
			
		
	
		

	