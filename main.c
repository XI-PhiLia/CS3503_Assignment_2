#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "convert.c"

int main() {
    FILE * file = fopen ("a2_test.txt", "r") ; // read a2 test file
    if ( file == NULL ) {
        printf (" Error : Could not open file \n") ;
        return 1;
    }
    char line [100];
    char output [33] = {'\0'};
    int pass = 0;
    int t_count = 0;
    while( fgets ( line , sizeof ( line ) , file ) != NULL ) { // Process each line
        // removes new line
        line[strcspn(line, "\n")] = '\0';
        // skips line or comment
        if (line[0] == '#' || strlen(line) == 0) 
            continue;
        char *function = strtok(line, " "); // grabs the function name, input, and answer from text file
        char *input = strtok(NULL, " ");
        char *ans = strtok(NULL, " ");
        int n = atoi(input); // converts the input to integer for sign magnitude, ones & twos complement
        // test oct_to_bin
        if(strcmp(function, "oct_to_bin")==0) { 
            oct_to_bin(input, output);
            t_count++;
            printf("\nTest %d: oct_to_bin (\"%s\") -> Expected: \"%s\", Got: \"%s\"", t_count, input, ans, output);
            // check if the output is the same as conversion answer in txt file
            if(strcmp(output, ans)==0) {
               printf(" [PASS]");
               pass++;
            }
        }
        // test oct_to_hex
        else if(strcmp(function, "oct_to_hex")==0) { 
            oct_to_hex(input, output);
            t_count++;
            printf("\nTest %d: oct_to_hex (\"%s\") -> Expected: \"%s\", Got: \"%s\"", t_count, input, ans, output);
            // check if the output is the same as conversion answer in txt file
            if(strcmp(output, ans)==0) {
               printf(" [PASS]");
               pass++;
            }
        }
        // test hex_to_bin
        else if(strcmp(function, "hex_to_bin")==0) { 
            hex_to_bin(input, output);
            t_count++;
            printf("\nTest %d: hex_to_bin (\"%s\") -> Expected: \"%s\", Got: \"%s\"", t_count, input, ans, output);
            // check if the output is the same as conversion answer in txt file
            if(strcmp(output, ans)==0) {
               printf(" [PASS]");
               pass++;
            }
        }
        // test to_sign_magnitude
        else if(strcmp(function, "to_sign_magnitude")==0) { 
            to_sign_magnitude(n, output);
            t_count++;
            printf("\nTest %d: to_sign_magnitude (%d) -> Expected: \"%s\", Got: \"%s\"", t_count, n, ans, output);
            // check if the output is the same as conversion answer in txt file
            if(strcmp(output, ans)==0) {
               printf(" [PASS]");
               pass++;
            }
        }
        // test to_ones_complement
        else if(strcmp(function, "to_ones_complement")==0) { 
            to_ones_complement(n, output);
            t_count++;
            printf("\nTest %d: to_ones_complement (%d) -> Expected: \"%s\", Got: \"%s\"", t_count, n, ans, output);
            // check if the output is the same as conversion answer in txt file
            if(strcmp(output, ans)==0) {
               printf(" [PASS]");
               pass++;
            }
        }
        // test to_twos_complement
        else if(strcmp(function, "to_twos_complement")==0) { 
            to_twos_complement(n, output);
            t_count++;
            printf("\nTest %d: to_twos_complement (%d) -> Expected: \"%s\", Got: \"%s\"", t_count, n, ans, output);
            // check if the output is the same as conversion answer in txt file
            if(strcmp(output, ans)==0) {
               printf(" [PASS]");
               pass++;
            }
        }
        // invalid test input
        else {
            printf("Test input invalid.");
        }
    }
    fclose ( file ) ; 
    printf("\nSummary: %d/%d test passed", pass, t_count); // prints summary of passed/total tests
}