# Project 1: Triplex Algebraic Expansion / Max-Pivot Scaling
# Kenneth Figueiredo - Ken.Figueiredo@knights.ucf.edu
# Final Submission: 9/19/2014

# Part A Registers and Info: ***********************************
#  f = [ a + ( a * b ) + ( a * b * c )]
#	$t0 -> sumFtotal
#	$t2 -> val of (a * b)
#	$t3 -> val of (a * b * c)
#	$t4 -> variable 'a'
#	$t5 -> variable 'b'
#	$t6 -> variable 'c'

# Part B Registers and Info: ***********************************
#  g = {[ a + ( a * b ) + ( a * b * c )] / max(a, b, c) } = sumFtotal / max(a, b, c)
#	$t0 -> sumFtotal
#	$t1 -> sumGtotal
#	$t2 -> max(a,b,c)
#	$t4 -> variable 'a'
#	$t5 -> variable 'b'
#	$t6 -> variable 'c'
#	$t7 -> Quotient

# Shared Registers and Info: ***********************************
#	$v0 -> syscall param and return val
#	$a0 -> syscall param
#	$t7 -> register for loop counter

# DO NOT USE THESE FUNCTIONS: mul, mul.d, mul.s, mulo, mulou, mult, multu, mulu, div, divu, 
#	rem, sll, sllv, sra, srav, srl, srlv


.data				 # keyword for declaring variables
inputText:    .asciiz "Enter 3 integers for a,b,c respectively:  \n" # Declare text user is shown before they input numbers
partAdecimal: .asciiz "f_ten = " 				  # Declare pretext for printout of partA decimal output
partAbinary:  .asciiz "f_two = " 				  # Declare pretext for printout of partA binary output
partBquot:    .asciiz "g_quotient = "				  # Declare pretext for printout of partB quotient output
partBremain:  .asciiz "g_remainder = "				  # Declare pretext for printout of partB remainder output
partBdiv:     .asciiz " / "					  # Declare text for division symbol
space: 	      .asciiz "\n"					  # Declare text for newline

.globl main			 #pointer to program start
.text				 #keyword to declare program text

main:
# PART A ********************************************************************************************************************************

  # Printout instruction statement to user
  	li $v0, 4			# set v0 to print string
	la $a0, inputText		# a0 set to string to be printed
	syscall				# call to syscall to print text to screen

  # Read In Values:
	li $v0, 5		 #set v0 to 5 to read integer
	syscall			 #syscall to start the read in
	move $t4, $v0		 #move the user entered int to register t4

	li $v0, 5		 #set v0 to 5 to read integer
	syscall			 #syscall to start the read in	
	move $t5, $v0		 #move the user entered int to register t5

	li $v0, 5		 #set v0 to 5 to read integer
	syscall			 #syscall to start the read in	
	move $t6, $v0		 #move the user entered int to register t6
 
 #Begin first loop to determine sum1 or ( a * b )
 	
 	li $t7, 0		# initialize of t7 (loop counter, i)
 	
 	multAB: bge $t7, $t5, multABend	 #loop exit condition, if(i > b) GOTO: multABend
 		addi $t7, $t7, 1	 # increment i by 1 ( i++ )
 		
 		add $t2, $t2, $t4	 # increment sum1 by 'a' ( sum1 = ai + ai+1 + ai+2 + ... + ab )
	j multAB			 # Jump back to loop if end condition is not met.
	
    multABend:				#break condition f1

 #Begin second loop to determine sum1 or ( a * b * c) or (sum1 * c)
 	
	li $t7, 0			#set the loop counter back to zero
	
	multABC: bge $t7, $t6, multABCend	# loop exit condition, if(i > c) GOTO: multABCend
		addi $t7, $t7, 1		# increment i by 1 ( i++ )	
		
		add $t3, $t3, $t2		# increment sum2 by 'c' ( sum2 = sumi + sumi+1 + sumi+2 + ... + sumc )
	j multABC				# Jump back to loop if end condition is not met.
	
    multABCend:					#break condition f2
    
  # Compute F
  	add $t0, $t2, $t3			# sumf: add sum1 (a * b)  + sum2 (a * b * c)
  	add $t0, $t0, $t4			# finish sumf: add a + sumf;
  
# PART B ********************************************************************************************************************************************
  
  # Max Function ******************************************************************************
	maxSt: bgt $t4, $t5 max1	# if(a > b) = true, branch right -> max1
		j max0			# if(a > b) = false, branch left -> max0
	
	max0: bgt $t4, $t6 maxB		# if(a > c) = true, branch right -> maxB
		j max00			# if(a > c) = false, branch left -> max00
	
	max1: bgt $t5, $t6 maxA		# if(b > c) = true, branch right -> maxA
		j max10			# if(b > c) = false, branch left -> max10
	
	max00: bgt $t5, $t6 maxB	# if(b > c) = true, branch right -> maxB
		j maxC			# if(b > c) = false, branch left -> maxC

	max10: bgt $t4, $t6, maxA	# if(a > c) = true, branch right -> maxA
		j maxC			# if(a > c) = true, branch right -> maxC

	maxA: add $t2, $t4, $zero	# A is found to be the max value
		j endMax		# exit maxfunction
		
	maxB: add $t2, $t5, $zero	# B is found to be the max value
		j endMax		# exit maxfunction		

	maxC: add $t2, $t6, $zero	# C is found to be the max value
		j endMax		# exit maxfunction
		
	endMax:

  # Division ***************************************************************************************************************************************
		li $t7, 0			 	# initialize of t7 (loop counter, i)
		add $t1, $t0, $zero		 	# load t1 with the dividend F
 	
 		divFmax: ble $t1, $zero, divFmaxEnd     #loop exit condition, if(F < zero) GOTO: divFmaxEnd
 			addi $t7, $t7, 1	  	# increment i by 1 ( i++ )
 			sub $t1, $t1, $t2		# subtract F by max val 
		j divFmax		 	 	# Jump back to loop if end condition is not met.
	
   		divFmaxEnd:				#break condition g1

	  # Check for Remainder *******************************************************************************************************************	
		  getRemain: beqz $t1, noRemainder		# if statement if(altered F == zero) skip solving for remainder b/c there is not one.
		  	add $t1, $t1, $t2			# add the value of max to altered F to reverse the last loop calculation
		  	subi $t7, $t7, 1			# subtract 1 from i to lower the number of 'divisions' made 
		  noRemainder: 
		
 #Print statements ********************************************************************************************************************************
 	
 	#Print out F result from part A in Decimal
 		li $v0, 4			# set v0 to print string
		la $a0, partAdecimal		# print label for part A decimal value
		syscall				# system call prints the previous two lines
	
		li $v0, 1			# set v0 to print integer
		add $a0, $t0, $zero		# print value of t0 or F
		syscall				# system call prints the previous two lines
   
 		li $v0, 4			# set v0 to print string
		la $a0, space			# print new line string to keep data organized
		syscall				# system call prints the previous two lines
		
 	#Print out F result from part A in Binary
 		li $v0, 4			# set v0 to print string
		la $a0, partAbinary		# print label for part A binary value
		syscall				# system call prints the previous two lines
	
		li $v0, 35			# set v0 to print binary
		add $a0, $t0, $zero		# print value of t0 or F in binary
		syscall				# system call prints the previous two lines
   
 		li $v0, 4			# set v0 to print string
		la $a0, space			# print new line string to keep data organized
		syscall				# system call prints the previous two lines		

 	#Print out g result from part B
 		li $v0, 4			# set v0 to print string
		la $a0, partBquot		# print label for part A binary va
		syscall				# system call prints the previous two lines
	
		li $v0, 1			# set v0 to print integer
		add $a0, $t7, $zero		# print value of t7
		syscall				# system call prints the previous two lines
   
 		li $v0, 4			# set v0 to print string
		la $a0, space			# print new line string to keep data or
		syscall				# system call prints the previous two lines	

 	#Print out g remainder from part B
 		li $v0, 4			# set v0 to print string
		la $a0, partBremain		# print label for part B remainder
		syscall				# system call prints the previous two lines
	
		li $v0, 1			# set v0 to print integer
		add $a0, $t1, $zero		# print value of t1 or quotient 
		syscall				# system call prints the previous two lines
   	
   		getRemain2: beqz $t1, noRemainder2		# check for no remainder again so if there is not one it will just print zero.
 			li $v0, 4				# set v0 to print string
			la $a0, partBdiv			# print label for part B division symbol
			syscall					# system call prints the previous two lines	
		
			li $v0, 1				# set v0 to print integer
			add $a0, $t2, $zero			# print value of t2 or max
			syscall					# system call prints the previous two lines
		noRemainder2:

li $v0, 10			#exit program
syscall
