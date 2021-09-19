#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0
#define BAD_NUMBER_ARGS 1

/**
 * Parses the command line.
 *
 * argc: the number of items on the command line (and length of the
 *       argv array) including the executable
 * argv: the array of arguments as strings (char* array)
 * bits: the integer value is set to TRUE if bits output indicated
 *       outherwise FALSE for hex output
 *
 * returns the input file pointer (FILE*)
 **/
FILE *parseCommandLine(int argc, char **argv, int *bits) {
  if (argc > 2) {
    printf("Usage: %s [-b|-bits]\n", argv[0]);
    exit(BAD_NUMBER_ARGS);
  }

  if (argc == 2 &&
      (strcmp(argv[1], "-b") == 0 || strcmp(argv[1], "-bits") == 0)) {
    *bits = TRUE;
  } else {
    *bits = FALSE;
  }

  return stdin;
}

/**
 * Writes data to stdout in hexadecimal.
 *
 * See myxxd.md for details.
 *
 * data: an array of no more than 16 characters
 * size: the size of the array
 **/
void printDataAsHex(unsigned char *data, size_t size) {
  int counter = 0;
  for (int i = 0; i < 16; ++i) { //for every letter in the array
    ++counter;
    if (counter % 2 != 0){ //this prints out a space every 4 characters as needed
      printf (" ");
    }
    if (i < size) { //if we are within the size
      printf("%02x", data[i]);
    }
    else {
       printf("  ");
    }
  }
  //printf("TODO 1: printDataAsHex (2)");
}

/**
 * Writes data to stdout as characters.
 *
 * See myxxd.md for details.
 *
 * data: an array of no more than 16 characters
 * size: the size of the array
 **/
void printDataAsChars(unsigned char *data, size_t size) {
  int i = 0;
  while(i < size) {
      int c = data[i];
      if (c == '\n') {
        printf(".");
        ++i;
      } else 
      if(c >= ' ' || c <= '~') {
        printf("%c", c);
        ++i;
      }
      else {
        printf(".");
        ++i;
      }
  }
}

void readAndPrintInputAsHex(FILE *input) {
  unsigned char data[16];
  int numBytesRead = fread(data, 1, 16, input);
  unsigned int offset = 0;
  while (numBytesRead != 0) {
    printf("%08x:", offset);
    offset += numBytesRead;
    printDataAsHex(data, numBytesRead);
    printf("  ");
    printDataAsChars(data, numBytesRead);
    printf("\n");
    numBytesRead = fread(data, 1, 16, input);
  }
}


void printDataAsBits (unsigned char *data, size_t size) {


  printf("TODO 3: printDataAsBits");


    int counter = 0;
    for (int i = 0; i < 16; ++i) { //for every letter in the array
      ++counter;
      if (counter % 2 != 0){ //this prints out a space every 4 characters as needed
        printf (" ");
      }
      if (i < size) { //if we are within the size
        int byte = data[i]; //get the number
        int eightBit [8]; //make an array of ints (the 8-bit part)
        //printf("%d", data[i]); 
        for (int j = 0; j < 8; ++j) { //for each of the 8 bits
          if (byte % 2 == 1) {
            printf("1");
            //eightBit[j] = 1;
            /* store a 1 for the bit */
          } else {
            printf("0");
            //eightBit[j] = 0;
            /* store a 0 for the bit */
          }
          byte = byte / 2;
        }
        //printf("%s", eightBit);
        //printf("%04x", data[i]);
      }
      else {
        printf("    ");
      }
    }
}

/**
 * Bits output for xxd.
 *
 * See myxxd.md for details.
 *
 * input: input stream
 **/
void readAndPrintInputAsBits(FILE *input) {
  


  unsigned char data[6];
    int numBytesRead = fread(data, 1, 6, input);
    unsigned int offset = 0;
    while (numBytesRead != 0) {
      printf("%08x:", offset);
      offset += numBytesRead;
      printDataAsBits(data, numBytesRead);
      printf("  ");
      printDataAsChars(data, numBytesRead);
      printf("\n");
      numBytesRead = fread(data, 1, 6, input);
    }

}

int main(int argc, char **argv) {
  int bits = FALSE;
  FILE *input = parseCommandLine(argc, argv, &bits);

  if (bits == FALSE) {
    readAndPrintInputAsHex(input);
  } else {
    readAndPrintInputAsBits(input);
  }
  return 0;
}
