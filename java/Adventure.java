/* Kenneth Figueiredo
   COP3330 - 0001
   Cipher.java
  */

import java.util.*;
import java.util.Random;

public class Adventure{

	public static void main(String args[]){ 
	
		Scanner input = new Scanner(System.in);
		int inputmovement;
		int rows = 0, columns = 0;
		boolean playeralive = true;
		char gameboard[][] = new char[10][10];

		gameboard = Boardcreator(10);
		Boardprintout(gameboard);
	
	//While loop that keeps the board and plaer going until the game reaches the treasure or  a trap
		while(playeralive == true){
			System.out.printf("\n");
			System.out.printf("Please enter your move! (1 - Up, 2 - Down, 3 - Left, 4 - Right):");
			inputmovement = input.nextInt();
			
			Playermover(inputmovement, gameboard);
			Boardprintout(gameboard);
			

		}
		
}		

public static char[][] Playermover(int move, char[][] gameboard){
	
	// This function moves the player around the cave using nested for loops and various if statements.
	
		char temp;
		boolean playeralive = true;
		int row, col;
		
	for(row = 0; row < 10; row ++){
		for(col = 0; col < 10; col ++){
		
	// Nested Forloops run until the hit the cell which the player resides in.
		
		if(gameboard[row][col] == 'P'){
		
		//Based on the entered move, the player will shift through the array using a variety of if statements.
		
		//Runs if player moves up
			if(move == 1){
				if(row != 0 && gameboard[row-1][col] != 'X'){
								
					if(gameboard[row-1][col] == '*'){
							System.out.println("Game Over! Tallahassee Smith's Family hates you for killing him");
							System.exit(0);
						}
				
					else if(gameboard[row+1][col] == 'T'){
						System.out.println("You found the Treasure! Congratulations! You Win!");
						System.exit(0);
					}	
					
					else{	
						temp = gameboard[row-1][col];
						gameboard[row-1][col] = gameboard[row][col];
						gameboard[row][col] = temp;
						row -= 1;
					
					}
		
				}
				
				else{
					System.out.println("That way is blocked please try again");
				}
			}
		
	//Runs if player moves down	
			else if(move == 2){
				if(row != 9 && gameboard[row+1][col] != 'X'){

					if(gameboard[row+1][col] == '*'){
						System.out.println("Game Over! Tallahassee Smith's Family hates you for killing him");
						System.exit(0);
					}
					
					else if(gameboard[row+1][col] == 'T'){
						System.out.println("You found the Treasure! Congratulations! You Win!");
						System.exit(0);
					}	
						
					else{	
						temp = gameboard[row+1][col];
						gameboard[row+1][col] = gameboard[row][col];
						gameboard[row][col] = temp;
						row += 1;
					}
				}
		
				else{
					System.out.println("That way is blocked please try again");
				}
		
			}
			
	//Runs if player moves left
			else if(move == 3){
				if(col != 0 && gameboard[row][col-1] != 'X'){
					if(gameboard[row][col - 1] == '*'){
						System.out.println("Game Over! Tallahassee Smith's Family hates you for killing him");
						System.exit(0);
					}
					
					else if(gameboard[row][col - 1] == 'T'){
						System.out.println("You found the Treasure! Congratulations! You Win!");
						System.exit(0);
					}
					
					else{
						temp = gameboard[row][col-1];
						gameboard[row][col-1] = gameboard[row][col];
						gameboard[row][col] = temp;
						col -= 1;
					}
				}
		
				else{
					System.out.println("That way is blocked please try again");
				}
		
			}
	
	//Runs if player moves right
			else if(move == 4){
				if(col != 9 && gameboard[row][col+1] != 'X'){
					
					if(gameboard[row][col + 1] == '*'){
						System.out.println("Game Over! Tallahassee Smith's Family hates you for killing him");
						System.exit(0);
					}
					
					else if(gameboard[row][col + 1] == 'T'){
						System.out.println("You found the Treasure! Congratulations! You Win!");
						System.exit(0);
					}
					
					else{
						temp = gameboard[row][col+1];
						gameboard[row][col+1] = gameboard[row][col];
						gameboard[row][col] = temp;
						col += 1;
					}
				}

		
				else{
					System.out.println("That way is blocked please try again");
				}
		
			}
		}
		}
	}
		return gameboard;
	}

	public static char[][] Boardcreator(int boardsize){
	
		char gameboard[][] = new char[boardsize][boardsize];
		int randomnumber;	
		Random randomGenerator = new Random();
		int rows, columns;
	
	//Nested for loop runs through the array and randomly generates the values using randomGenerator.nextInt.
	
			for(rows = 0; rows < 10; rows ++){
				for(columns = 0; columns < 10; columns++){
			
					randomnumber = randomGenerator.nextInt(100); // goes from 0 - 99

					// Player's starting position is always 0,0
						if(rows == 0 && columns == 0){
							gameboard[rows][columns] = 'P';
						}
					
					// Treasure's starting position is always 0,0
						else if(rows == 9 && columns == 9){
							gameboard[rows][columns] = 'T';
						}
					
					// 10 % chance that a barrier spawns					
						else if(randomnumber >= 89){
							gameboard[rows][columns] = 'X';
						}
					
					// 85 % chance that a blank spawns
						else if(randomnumber <= 88 && randomnumber >= 5){
							gameboard[rows][columns] = '.';
						}
					
					// 5% chance that gameboard spawns a pit
						else{ //(randomnumber <= 4)
							gameboard[rows][columns] = '*';
								
						}
				}
								
			}
			
			return gameboard;
	}

	public static void Boardprintout(char[][] gameboard){
		int rows, columns;

		System.out.println("This Round's GameBoard");
			System.out.println("----------------------");	
			
		//Nested for loop that runs through all the rows and columns of the gameboard and prints out the board again.	
			for(rows = 0; rows < 10; rows ++){
					for(columns = 0; columns < 10; columns++)
						System.out.print(gameboard[rows][columns]);
					
				System.out.printf("\n");
			}
					
	}
	
}
				