# CS-211-Computer-Architecture
These are some of the projects I did while taking Computer Architecture (CS 211) during my spring semester of sophomore year of college. All projects are completed in C. Third project is an Assembly debugger project.

Description of each project:
  1. 6 Introcutory C Programs
      - Roman
        - Program **roman** which converts numbers from decimal notation into Roman numerals. **Roman** takes a single argument, a string                   containing a non-negative integer, and prints its Roman numeral equivalent to standard output.
      - Palindrome
        - Program **palindrome** that tests whether a string is a palindrome, meaning that the sequence of letters is symmetric and is not               changed by reversal. **Palindrome** takes a single argument, which is a string containing any combination of upper- and lower-case             letters, digits, and punctuation marks.
      - Run-length Encoding
        - Program **rle** that uses a simple method to compress strings. **Rle** takes a single argument and looks for repeated characters. Each             repeated sequence of a letter or punctuation mark is reduced to a single character plus an integer indicating the number of               times it occurs. Thus, “aaa” becomes “a3” and “ab” becomes “a1b1”. 
        - If the compressed string is longer than the original string, **rle** must print the original string instead. 
      - Linked Lists
        - Program **list** that maintains and manipulates a sorted linked list according to instructions received from standard input.
        - The linked list is maintained in order, meaning that the items in the list are stored in increasing numeric order after every           operation.
      - Matrix Manipulation
        - Program **mexp** that multiplies a square matrix by itself a speciﬁed number of times. mexp takes a single argument, which is the           path to a ﬁle containing a square **(k×k)** matrix **M** and a non-negative exponent **n**. It computes M^n and prints the               result. 
      - Binary Search Trees
        - Program **bst** that manipulates binary search trees. It will receive commands from standard input, and print resposes to those             commands to standard output.
       

  2. One-shot Learning
        - Program **estimate** that uses a training data set to learn weights for a set of house
         attributes, and then applies those weights to a set of input data to calculate prices for those houses.
         **Estimate** takes two arguments, which are the paths to files containing the training data and input
         data.
       - Once those weights have been found, they can be used to estimate prices for additional houses.
       - The program implements various matrix manipulation algorithms such as:
         - Gauss-Jordan Elimination
         - Matrix Inversion
         - Matrix Multiplication
         - Matrix Transpose
         
  3. Bomb Lab (X86 Assembly)
        - Linux executable C program that consists of 9 phases. Each phase expects a particular string on standard input.  If the                 correct string is entered, then that phase is defused, otherwise the bomb explodes.
        - In order to defuse the bomb, a debugger is necessary to disassemble the binary and single-step through the machine code in               each phase. The idea is to understand what each assembly statement does, and then use this knowledge to infer the defusing               string.
        
  4. Digital Logic Design
        - Program **truthtable** that prints a given circuit's truth table. **Truthtable** takes a single argument, a file containing             the description of a logic circuit, which specifies the number and names of each input to the circuit, the number and names of           each output from the circuit, and the logic gates that make up the circuit.
        - Once the program runs through the file, it then prints the truth table for every possible combination of the inputs.
      
