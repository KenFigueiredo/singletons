# Project 2: Hexadecimal Sleuth / String Digit Score
# Kenneth Figueiredo - Ken.Figueiredo@knights.ucf.edu
# Final Submission: 10/24/2014

#  Registers **************************************************************************
#	$t0 -> address of sentence / j
#	$t1 -> value of current byte in address
#	$t2 -> i
#	$t3 -> validity -> 0 = valid hex, 1 = invalid hex
#	$t4 -> word length
#	$t5 -> k
#	$t6 -> wordSum
# 	$t7 -> tempWord
#	$t8 -> Used to hold multiplying factor for hex to decimal conversion
#	$t9 -> outer loop variable
#	$s0 -> exponential constant 4 to use for left shifts of 16
#	$s1 -> max sum for part b
#	$a0 -> Used to read in / output various values
#	$a1 -> Used to hold maximum string length of the user inputted string
#	$v0 -> Used for various syscalls


# Test Cases **************************************************************************
# 	"I ACED THE EXAM AND EARNED AN A PLUS."
# 	"BEEF BRISKET ON BED OF LETTUCE FOR 99 CENTS."
# 	"FADED OUT AND FAD3D IN."

# DO NOT USE jal / jr functions

.data				 # keyword for declaring variables

sentence: .space 200	  	         # Reserve 200bytes (1 char = 1 byte) for sentence
prompt: .asciiz "\nInput a string: "     # user prompt to begin program
sparce: .asciiz "\nSparse"	  	 # word 1 for part b
interm: .asciiz "\nIntermediate" 	 # word 2 for part b
plenty: .asciiz "\nPlentiful"      	 # word 3 for part b
newline: .asciiz "\n"		 	 # declare text for newline
space:.asciiz " "	         	 # Declare text for space

.globl main			 #pointer to program start
.text				 #keyword to declare program text

main:

 # Read in sentence from user
  	li $v0, 4			# set v0 to print string
	la $a0, prompt		# a0 set to string to be printed
	syscall				# call to syscall to print text to screen 
 
  	li $v0, 8
	la $a0, sentence	        # a0 set to string to be readin
	li $a1, 200			# a1 set to string length (max)
	syscall				#syscall to readin user data
	
 # Begin loop
 	
 	la $t0, sentence	# set address of sentence to t0
 	li $s0, 4		# storage for left shifts later on.
 	
 	outerWhile: beq $t9, 1, outerWhileEnd	#infinitely loop outer until break condition
 		add $t2, $t0, $zero		# j = i
 			
 		innerWhile: 
 			lb $t1, ($t2)		 # t1 = sentence[j]			
 			bne $t1, 10, skp  	 # if sentence[j] != \n GOTO skip;
 			    li $t9, 1            # looper = 1
 		 	    bne $t2, $t0, skipJ  # if word no started and is spacer
 			    li $t3, 1	         # set validity to zero so no excess zeros at end
 			skipJ: j innerWhileEnd	 # break;    
 			skp: bne $t1, 32, skpP   # if sentence[j] != ' ' GOTO skipP
 			    j innerWhileEnd	 # break;
 			skpP: bne $t1, 46, skp2   # if sentence[j] != '.' GOTO skip2
 			    j innerWhileEnd	 # break;			     			    
 			skp2: blt $t1, 48, setV	 # if sentence[j] < 48 GOTO setV (current char is not valid)
 			      bgt $t1, 57, chk1  # if sentence[j] > 57 GOTO chk1 (current char may possibly be in the A - F range)
 			    j skp3		 # current char is a valid hex range 0 - 9
			
			chk1: blt $t1, 65, setV	 # if sentence[j] < 65 GOTO setV (current char is not valid)
 			      bgt $t1, 70, setV  # if sentence[j] > 70 GOTO setV (current char is not valid)
			   j skp3		 # current char is a valid hex range A - F
			
			setV: li $t3, 1	 	 # if conditions above are met, current char is a valid hex digit 
 			skp3: addi $t2, $t2, 1	 # j++
 			j innerWhile
 		innerWhileEnd:
 		
 		
 		beq $t3, 1, invalidHex			# if(validity == 1) goto: invalidHex operations
						
 			sub $t4, $t2, $t0	 	# wordLength = end - start (t0 - t2) length of word
 			li $t5, 0			# k = 0
 			li $t6, 0			# sum = 0
 			DecToHex: beq $t5, $t4, DecToHexEnd  # for k = 0; k != wordLength; k++
 				  sub  $t7, $t2, $t5 	 # &tempWord = end - k			  
 				  subi $t7, $t7, 1	 # &tempWord -= 1
 				  lb $t1, ($t7)		 # tempChar = tempWord[t7]	
 				  blt $t1, 58, low	 # if sentence[j] < 58 GOTO low (current char is digit 0 - 9)
 				  subi $t1, $t1, 55	 # hex[end-k-1] - 55
 				  j skp4	
 				  low: subi $t1, $t1, 48 # hex[end-k-1] - 48 				  
 				  skp4: multu $t5, $s0
 				  mflo $t8				  
 				  sllv $t1, $t1, $t8     # shift value left 4 bits (eq of * 16^k)
 				  add  $t6, $t6, $t1	 # sum += (hex[end-k-1] - ascii) * 16^k
 				  addi $t5, $t5, 1	 # k++
 				 j DecToHex	
 			DecToHexEnd:
 				
 				blt $t6, $s1, skp5
 				    add $s1, $t6, $zero
 			
 			   skp5:
 			   	li $v0, 1			# set v0 to print integer
				add $a0, $t6, $zero		# print current 'hex' word in decimal
				syscall				# system call prints the decimal 				
 			j finish
 		
 		invalidHex: add $t5, $t0, $zero			# k = i | k = start of word	
 		  loop: beq $t5, $t2, finish			# k != end of word j
 			add $t7, $t5, $zero			# &sentence[k] = t7			
 			li $v0, 11				# set v0 to print character
			lb $a0, ($t7)				# set a0 to sentence[k]
			syscall					# system call prints the character			
			addi $t5, $t5, 1			# k++
			j loop					# GOTO loop
			
 		finish:
 		
  		li $v0, 4			# set v0 to print string
		la $a0, space			# print new line string to keep data or
		syscall				# system call prints the previous two lines	
 				
 		li $t3, 0					# valid = 0	
 		add $t0, $t2, 1					# i += j - i + 1 || i = j + 1
 		j outerWhile
 	outerWhileEnd: 
 
 	bgt $s1, 255, elseif	# if maxWordScore <= 255 - sparce
 	    la $a0, sparce
 	j done	
 	
 	elseif: bgt $s1, 65535, else    # if maxWordScore <= 65535 - interim
   	    la $a0, interm
   	j done	
   	    
   	else: la $a0, plenty   		# if maxWordScore <= infinity - plentiful
   	
   	done: li $v0, 4			# set v0 to print string
	syscall				# system call prints the previous two lines	


# exit program		
li $v0, 10			
syscall
