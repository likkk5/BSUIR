# Program: Task 2
# Lab Number: 3
# Program Version: 1.3
# Developer: Lishyk Ksenia
# Date: 27.03.2024

import input as inp
import operation as op

numbers_sum=0
count=0
while True:
        print("Choose how do you want to input numbers' sequence:\n"         
          "G. Generated automatically.\n"
          "U. User input.\n")
    
        while True:
            print("Enter G or U:")
            choice=inp.input_abc()
            if choice!='U' and choice!='G':
                print("Incorrect input!Try again.")
            else:
                break
            
        if choice=='U':
            while True:
                a=inp.input_int()
                count = op.perform_operation(a,count)
                # if a>12:
                #     count+=1
                numbers_sum+=a
                print("Count of numbers greater than 12:",count)
                if a == 0:  
                    break
            
        elif choice=='G':
            for num in inp.generate_random_sequence():
                print(num)
                numbers_sum+=num
                #count = op.perform_operation(num,count)
                if num>12:
                    count+=1
                print("Count of numbers greater than 12:",count)
                if num == 0:  
                    break
        
        print("Sum of numbers is",numbers_sum);
        numbers_sum=0
        count=0
      
        if not inp.continue_or_exit(): #Ask user if he wants to finish the program or continue.  
            break