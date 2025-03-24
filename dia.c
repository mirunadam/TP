// Write a program to parse the ".srt" text file, remove the text
// formatting tags and shift the timings with a number of seconds
// given as command line arguments.
// Use fscanf () in order to parse the time.

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <errno.h>


void adjust_timestamp(int *hour, int *min, int *sec, int *millis, int millis_adjust)
{
    // convert to seconds and adjust
    int total_millis = (*hour) * 3600000 + (*min) * 60000 + (*sec) * 1000 + (*millis) + millis_adjust;

    // avoid negative times
    if (total_millis < 0) total_millis = 0;

    // covert back to hours/minutes/seconds/milliseconds
    *millis = total_millis % 1000;
    *sec = (total_millis / 1000) % 60;
    *min = (total_millis / 60000) % 60;
    *hour = total_millis / 3600000;
}


int main(int argc, char *argv[])
{
    FILE *fp;
    double seconds_arg;
    int millis_adjust;
    int num_values_read;

    // validate the arguments
    if (argc != 3)
    {
        printf("Wrong number of arguments. Use:\n");
        printf("%s filename.srt seconds-to-adjust\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // parse the seconds to adjust
    num_values_read = sscanf(argv[2], "%lf", &seconds_arg);
    if (num_values_read != 1)
    {
        perror("Error! Invalid number of seconds to adjust!");
        exit(EXIT_FAILURE);
    }
    millis_adjust = (int) (seconds_arg * 1000);

    // open the subtitle file
    fp = fopen(argv[1], "rt");
    if (fp == NULL)
    {
        perror("fopen()");
        exit(EXIT_FAILURE);
    }

    // keep reading, adjusting and printing subtitle lines
    unsigned num;
    int hour1, min1, sec1, millis1, hour2, min2, sec2, millis2;
    while (fscanf(fp, "%u", &num) != EOF)
    {
        // just read the subtitle number => print it as is
        printf("%u\n", num);

        // read the times
        num_values_read = fscanf(fp, "%d:%d:%d,%d --> %d:%d:%d,%d",
            &hour1, &min1, &sec1, &millis1, &hour2, &min2, &sec2, &millis2);
        if (num_values_read != 8)
        {
            perror("Invalid subtitle timestamp");
            exit(EXIT_FAILURE);
        }
        adjust_timestamp(&hour1, &min1, &sec1, &millis1, millis_adjust);
        adjust_timestamp(&hour2, &min2, &sec2, &millis2, millis_adjust);
        printf("%02d:%02d:%02d,%03d --> %02d:%02d:%02d,%03d",
            hour1, min1, sec1, millis1, hour2, min2, sec2, millis2);

        // read and adjust the text lines
        int num_eol = 0;
        int ch = 0;
        bool inside_tag = false;
        while (ch != EOF && num_eol < 2)
        {
            ch = fgetc(fp);
            switch (ch)
            {
                case '\n':
                    num_eol++;
                    putchar('\n');
                    break;
                case '\r':
                    // ignore \r characters
                    break;
                case '<':
                    inside_tag = true;
                    num_eol = 0;
                    break;
                case '>':
                    inside_tag = false;
                    num_eol = 0;
                    break;
                default:
                    num_eol = 0;
                    if (!inside_tag && ch >= 32)
                    {
                        putchar(ch);
                    }
            }
        }
    }

    // done
    if (fclose(fp) != 0)
    {
        perror("fclose()");
        exit(EXIT_FAILURE);
    }

    return 0;
}