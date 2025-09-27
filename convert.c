#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>

// convert octal to binary
void oct_to_bin(const char *oct, char *out) {
    out[0] = '\0';
    // grabs 1st to ... character in octal, converts to binary & appends to output
    for(int i = 0; i < strlen(oct); i++) { 
        switch(oct[i]) {
            case '0': 
                strcat(out, "000"); break;
            case '1': 
                strcat(out, "001"); break;
            case '2': 
                strcat(out, "010"); break;
            case '3': 
                strcat(out, "011"); break;
            case '4': 
                strcat(out, "100"); break;
            case '5': 
                strcat(out, "101"); break;
            case '6': 
                strcat(out, "110"); break;
            case '7': 
                strcat(out, "111"); break;
            default: 
                printf("Invalid octal: %c\n", oct[i]); break;
        }
    }
}

// convert octal to hexa
void oct_to_hex(const char *oct, char *out) {
    char bin_temp[100] = {'\0'}; // stores octal --> binary
    char hex_temp[100] = {'\0'}; // stores binary (with 0 fillers for hex)
    // converts octal to binary
    oct_to_bin(oct, bin_temp);
    int fillers = (4 - (strlen(bin_temp) % 4)) % 4; // finds the number of 0's needed to pad the binary
    for(int i = 0; i < fillers; i++) { 
        strcat(hex_temp, "0"); // puts 0 for infront if the binary isn't divisible by 4
    }
    strcat(hex_temp, bin_temp); // concatenates the buffer 0's and the binary 
    int index = 0;
    for(int i = 0; i < strlen(hex_temp); i+=4) {  // converts binary to hexa
        char group[5];
        memcpy(group, &hex_temp[i], 4);
        group[4] = '\0';
        int n = strtol(group, NULL, 2); // converts string to base 2 (binary)
        if(n >= 10) { 
            out[index++] = 'A' + (n-10);
        }
        else {
            out[index++] = '0' + n;
        }
    }
    // terminates string
    out[index] = '\0';
    // removes the unnecessary leading zeroes for hex unless the hex is 0.
    int hexIndex = 0;
    while (out[hexIndex] == '0' && out[hexIndex + 1] != '\0') {
        hexIndex++;
    }
    memmove(out, out + hexIndex, strlen(out + hexIndex) + 1);
}

// converts hexa to binary
void hex_to_bin(const char *hex, char *out) {
    out[0] = '\0';
    // table that contains 0-F of hex to binary
    const char *table[] = {
        "0000", "0001", "0010", "0011", 
        "0100", "0101", "0110", "0111",
        "1000", "1001", "1010", "1011",
        "1100", "1101", "1110", "1111"
    };
    // concatenates the corresponding binary from the table to the output
    for (int i = 0; hex[i] != '\0'; i++) {
        char bit = toupper(hex[i]); // sets all letters to uppercase to also handle lowercase
        if (bit >= '0' && bit <= '9') {
            strcat(out, table[bit - '0']); // concatenates the 0-9 in binary
        } 
        else if (bit >= 'A' && bit <= 'F') {
            strcat(out, table[bit - 'A' + 10]); // concatenates the 10-15 in binary
        } 
        else { // letter that is not A-F
            printf("Not a hexadecimal."); 
        }
    }
}

void to_sign_magnitude(int n, char* out) {
    int magnitude;
    // sets leading zeroes
    for (int i = 0; i < 32; i++) {
        out[i] = '0';
    }
    out[32] = '\0'; // terminating string
    // sets sign bit for positive and negative
    if (n >= 0) {
        magnitude = n;
        out[0] = '0'; // positive sign bit
    } 
    else {
        magnitude = n*-1;
        out[0] = '1'; // negative sign bit
    }

    // fill magnitude bits from right to left
    int index = 31;
    while (magnitude > 0 && index > 0) {
        out[index] = (magnitude % 2) + '0';
        magnitude /= 2;
        index--;
    }
}

void to_ones_complement(int32_t n, char* out) {
    // For positive : output as -is with leading zeros
    // For negative : flip ALL bits
    out[32] = '\0'; // terminating string
    if ( n >= 0) {
        // Regular binary with 32 bits
        to_sign_magnitude(n, out);
    } 
    else {
        int magnitude = -n; 
        to_sign_magnitude(magnitude, out); // grabs the positive representation
        int i = 0;
        while(out[i] != '\0') { // flips all bits
            if(out[i] == '0')
                out[i] = '1';
            else
                out[i] = '0';
            i++;
        }
    }
}

void to_twos_complement(int32_t n, char* out) {
    // For positive : output as -is
    // For negative : flip all bits and add 1
    // This is how modern CPUs actually store integers !
    out[32] = '\0'; // terminating string
    if(n >= 0) {
        to_sign_magnitude(n,out); // positive representation
    }
    else {
        to_ones_complement(n,out); // flips bits
        // add 1 to binary string
        int carry = 1;
        for (int i = 31; i >= 0; i--) { // right to left
            if (out[i] == '1' && carry == 1) {
                out[i] = '0';  // 1+1=0, 1 carries to next bit
            } 
            else if (out[i] == '0' && carry == 1) {
                out[i] = '1';  // 0+1=1, no carry
                carry = 0;
            }
        }
    }
}