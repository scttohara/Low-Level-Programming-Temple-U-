/* 
 * File:   LabAssignment1.c
 * Author: scttohara
 *
 * Created on August 31, 2017, 8:16 PM
 */

#include <stdio.h> 

void get_string(char *str);
int strlen1(char *str);
int checkCase(char str);
int CaseChange(char *str);
int capitalize(char *str);
void reverse(char *str);
void print(char *str);

int main(int argc, char *argv[]) {

    //Declare variables
    char str[30];
    char *str_ptr = &str[0];
    int strlength = 1;
    int count;

    //prompt user to enter string.    
    get_string(str_ptr);

    //setting strlength to the function strlen1 to get string length of str_ptr.
    strlength = strlen1(str_ptr);

    //passes str_ptr to capitalize function.
    count = capitalize(str_ptr);

    //passes str_ptr to have it reversed in memory. 
    reverse(str_ptr);

    //prints the string.
    print(str_ptr);
    
    //prints the strlength and count for the number of chars in the string and 
    //the number of chars that were capitalized.
    printf("The string is %d chars and %i chars were capitalized.", strlength, count);

    return (0);
}

//prints the str from memory.
void print(char *str) {

    int i = 0;
    while (str[i] != '\0') {
        printf("%c \n", str[i]);
        i++;
    }
}

//prompts user to enter a string saves that string in str. 30 spaces allocated 
//for the string.
void get_string(char *str) {
    printf("Enter a String: ");
    fgets(str, 30, stdin);
}

//passed a pointer, iterates through the pointer p until it finds a new line char
//then returns the length by subtracting str's length from the p.
int strlen1(char *str) {
    char *p = str;
    while (*p != '\n') {
        p++;
    }
    return p - str;
}

//Reverses string in memory by using a temp array to save string and then copies
//from temp array into the str through p.
void reverse(char *str) {
    char *p = &str[0];
    int i = 0;
    int j = (strlen1(str) - 1);
    char temp;
    
    while (i < j) {
        temp = p[i];
        p[i] = p[j];
        p[j] = temp;
        i++;
        j--;
    }
}

//checks the character it's passed to see if it's a capital letter.
int checkCase(char str) {

    char p = str;
    int i = 0;

    while (p != '\0') {
        if ((p >= 'a') || (p <= 'z')) {
            return 0;
        }
    }
    return 1;
}

//passed a pointer and sets pointer p equal to str and moves through the array
//checking each char at p[i] to see if its a lower case number.
//counts each time a char is changed and returns that value into capitalize function.
int CaseChange(char *str) {

    char *p = str;
    int i = 0;
    int count;

    while (p[i] != '\0') {
        if (p[i] >= 'a') {
            p[i] = (p[i] - 32);
            count++;
        }
        i++;
    }
    return count;
}

//passed a pointer str, uses the checkCase and CaseChange to check for and then
//if needed change the case of lower case alpha chars in the array.
//returns the count for the number of times a alpha char is capitalize 
//to the main function.
int capitalize(char *str) {

    char *p = &str[0];
    int count = 0;
    int i = 0;

    while (p[i] != '\0') {
        while (checkCase(p[i]) == 0) {
            count = CaseChange(p);
            i++;
        }
    }
    return count;
}







