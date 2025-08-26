#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage : ./recover FILE\n");
        return 1;
    }

    FILE *raw_file = fopen(argv[1], "r"); // open the memory card

    uint8_t buffer[512]; // assigning buffer space
    int found_jpeg = 1;  // incase of error or not found we assigned 1
    int counter_jpeg = 0;
    char filename[8];
    FILE *img = NULL;
    // while theres data to read for the memory
    while (fread(buffer, 1, 512, raw_file) == 512)
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0) // condition per founding jpeg files
        {
            found_jpeg = 0; // setting back to zero
        }
        if (found_jpeg == 0) // if found the jpeg
        {
            if (counter_jpeg != 0)
            {
                fclose(img); // still not found and condition not fulfilled via data then close
            }
            sprintf(filename, "%03i.jpg", counter_jpeg);
            counter_jpeg++;

            img = fopen(filename, "w");
            fwrite(buffer, 1, 512, img);

            found_jpeg = 1;
        }
        else if (counter_jpeg != 0)
        {
            fwrite(buffer, 1, 512, img); // this writes for otherwise of any data
        }
    }
    fclose(img); // closing any files
    fclose(raw_file);
}
