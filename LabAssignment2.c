#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char *write(int len, char *file_name, char *output);
char *read(int len, char *file_name);
void make_rand_key(int len, char *key);
void encrypt(char *original_file, char *key_file, char *cipher_file);
void decrypt(char *key_file, char *cipher_file, char *original_file);

//global variables
char randomKey[40];
char *randkey = &randomKey[0];

int main(int argc, char* argv[]) {

    //Declare Variables 
    int userInput;
    int i = 0;
    
    //declares a pointer to the memory location where read stores message_file.txt. 
    char *clear_file = read(0, "message_file.txt");

    //prompts user to enter a number to perform and operation.
    printf("\nEncrypt a file: 1\nDecrypt a file: 2\nExit:           3\nEnter a "
            "choice: ");
    
    //scans user input into userInput.
    scanf("%d", &userInput);
    while (userInput != 3) {

        switch (userInput) {

            case 1: // Encrypt file 
                encrypt("message_file.txt", "randomkey_file.txt", "cipher_file.txt");
                break;
            case 2: //Decrypt file
                decrypt("randomkey_file.txt", "cipher_file.txt", "message_file.txt");
                printf("hello");
                break;
            case 3: //exits switch and loop with return
                return 0;
            default: //breaks switch statement to return to loop.

                break;
        }

        //prints after first input and each time after until input equals 3.
        printf("\nEncrypt a file: 1\nDecrypt a file: 2\nExit:           3\n"
                "Enter a choice: ");
        scanf("%u", &userInput);

    }

    return 0;
    
}

//decrypt message using the cipher_file and randomkey_file. Doesn't work 
//correctly after first read statement.
void decrypt(char *key_file, char *cipher_file, char *original_file) {

    int len = 40;
    
    char *random_file = read(40, key_file);
    //exits code inside read method can't figure out why.
    char randomTextArray[len + 1];
    
    int i = 0;
    for(i = 0; i < len; i++){
        randomTextArray[i] = random_file[i];
        
    }
    randomTextArray[i] = '\0';
    
    fgets(cipher_file, 40, stdin);

    //decrypt
    char decipherkey[len + 1];
    char *decipherkey_ptr = &decipherkey[0];
    char *cipherkey_ptr = &cipher_file[0];
    
    int h = 0;
    for (h = 0; h < len; h++) {
        decipherkey[h] = (randomTextArray[h] ^ cipherkey_ptr[h]);
    }

    char *dk = write(0, "decipher_file.txt", decipherkey);

    printf("\ndecipher text: \n%s", dk);

}

//encrypts message using clearTextArray and randomKey file. also writes randomkey
//to randomkey_file. Does work correctly. Can decipher using commented decipher
//section at the bottom of the method.
void encrypt(char *original_file, char *key_file, char *cipher_file) {

    int len = 40;

    //reads the message_file.txt into clear_file pointer.
    char *clear_file = read(0, "message_file.txt");
    //scanf("%u", &len);
    
    //declares clearTextArray.
    char clearTextArray[len + 1];

    //places each char in clear_file into clearTextArray/
    int i = 0;
    for (i = 0; i < len; i++) {
        clearTextArray[i] = clear_file[i];

    }
    clearTextArray[i] = '\0';

    //generates a random key of characters
    make_rand_key(40, randkey);
    
    //write that random key of characters to randomkey_file.txt
    write(0, "randomkey_file.txt", randkey);

    //declares char array cipherkey 
    char cipherkey[len + 1];
    //declares char array pointer that points at the first character in cipherkey.
    char *cipherkey_ptr = &cipherkey[0];

    
    int j = 0;
    //loops through each array and XOR's the bits into the cipherkey array.
    for (j = 0; j < len; j++) {
        cipherkey[j] = (clearTextArray[j] ^ randomKey[j]);
    }

    //writes cipherkey into cipher_file.txt
    char *ck = write(0, "cipher_file.txt", cipherkey);

    printf("\ncipher text: \n%s", ck);
    
    //below code deciphers message to show that the message is encrypted correctly.
/*
    char decipherkey[len + 1];
    char *decipherkey_ptr = &decipherkey[0];
    
    int h = 0;
    for (h = 0; h < len; h++) {
        decipherkey[h] = (randomKey[h] ^ cipherkey_ptr[h]);
    }

    char *dk = write(0, "decipher_file.txt", decipherkey);

    printf("\ndecipher text: \n%s", dk);
*/
}

//reads file from 0 and counts length or given length just reads file.
char *read(int len, char *file_name) {


    FILE *fp = fopen(file_name, "r");

    if (fp == NULL) {
        printf("ERROR: File not opened.\n");
        exit(1);
    }
    
    //passed this point you now have an open file.    
    if (len == 0) {
        while (getc(fp) != EOF)
            len++;

        //printf("len = %d\n", len);
        rewind(fp);
    }
    //allocates memory for input
    char *input = (char*) malloc(len + 1);

    if (input == NULL) {
        printf("ERROR: Memory didn't allocate.\n");
        exit(2);
    }
    
    int j = 0;
    for (j = 0; j < len; j++)
        input[j] = getc(fp);
    input[j] = '\0';

    fclose(fp);
    //file closed.
    
    return input;

}

//passed a length 0 (or length to be read), A file to write to and an output.
char *write(int len, char *file_name, char *output) {

    FILE *fp = fopen(file_name, "w");

    if (fp == NULL) {
        printf("ERROR: File not opened.\n");
        exit(3);
    }

    int j = 0;
    if (len == 0) {
        while (output[j] != '\0')
            putc(output[j++], fp);
    } else {
        for (j = 0; j < len; j++) {
            putc(output[j], fp);
        }
    }

    fclose(fp);

    return output;
}

//passed a length and a char array pointer the method generates a random key.
void make_rand_key(int len, char *key) {

    int i, n;
    //time_t t;
    int random;

    srand(time(NULL));

    n = len;
    for (i = 0; i < n; i++) {
        random = 'A' + (rand() % 26);
        key[i] = random;
    }


}
