# CS 3503 Assignment 2- Data Representation and Mapping
 
## Author
Darren
 
## Description
Advanced data representation functions for Owl Tech’s CPU design team.

## What’s New
- Direct mapping functions (oct/hex/bin)
- Signed number representations
- Reused test framework from A1
 
## Build Instructions
‘‘‘bash
gcc-o convert convert.c main.c
./convert
‘‘‘
 
## Test Results
51/51 Tests passed.
All implemented algorithms function correctly, giving the right outputs.
Correct binary representations (32 bit) of the number for one's and two's complement.

## Notes
- Updated the way to get input from the text file, used strtok(NULL, " ") instead of hardcoding the length of the string that the pointer has to be at. By placing NULL as the first parameter, it continues tokenizing the same string from where it left off.
- New methods learned: memmove(), memcpy(), and atoi().