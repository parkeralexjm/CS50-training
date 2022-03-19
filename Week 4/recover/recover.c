#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

const int BLOCK_SIZE = 512; // assign 512 as the size of 1 "block" of memory
typedef uint8_t  BYTE; // create a type for byte
BYTE buffer[BLOCK_SIZE]; // create an array of bytes caled buffer of length 512
int jpeg_count = 0; // create a counter to increase the name of the file by 1 each time
char filename[8]; //create string called filename
int counter = 0; //counter is for keeping track of the first jpeg

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }

// open the memory card and assign the data from argv to the struct FILE
    FILE *raw_file = fopen(argv[1], "r");

// initialise img otherwise fclose doesnt work
    FILE *img = NULL;

// read block size bytes into the buffer
    while (fread(buffer, 1, BLOCK_SIZE, raw_file) == BLOCK_SIZE)
    {
        // if start of a new jpeg
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff)
        {
            if ((buffer[3] & 0xf0) == 0xe0)
            {
                // if first header
                if (jpeg_count == 0)
                {
                    // assign a xxx.jpg name to a new file called filename
                    sprintf(filename, "%03i.jpg", jpeg_count);
                    // open a new file called filename
                    img = fopen(filename, "w");
                    // write the block of data in buffer to the open file called img
                    fwrite(buffer, BLOCK_SIZE, 1, img);
                    // increase counter by 1
                    jpeg_count++;
                }
                else // if its not the first jpeg
                {
                    fclose(img);
                    sprintf(filename, "%03i.jpg", jpeg_count);
                    img = fopen(filename, "w");
                    fwrite(buffer, BLOCK_SIZE, 1, img);
                    jpeg_count++;
                }
            }
        }
        else // first 4 bytes are not a header
            if (jpeg_count != 0)
            {
                fwrite(buffer, BLOCK_SIZE, 1, img);
            }
    }
}
