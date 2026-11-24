
/*
 * Name: Emanuel Hernandez
 * Assignment: Lab 11 Multiprocessing
 * Section: 111
 *
 * Description:
 * Generate 50 Mandelbrot images using
 * multiple child processes.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <math.h>

#define FRAMES 50

int main(int argc, char *argv[])
{
    int processes = 1;
    int opt;

    // Read command line arguments
    while ((opt = getopt(argc, argv, "p:")) != -1)
    {
        switch (opt)
        {
            case 'p':
                processes = atoi(optarg);
                break;

            default:
                fprintf(stderr,
                        "Usage: %s -p processes\n",
                        argv[0]);
                return 1;
        }
    }

    // Validate number of processes
    if (processes < 1 || processes > FRAMES)
    {
        printf("Processes must be between 1 and 50\n");
        return 1;
    }

    int active = 0;
    int failed = 0;

    for (int i = 0; i < FRAMES; i++)
    {
        // Limit simultaneously running children
        if (active >= processes)
        {
            int status;
            if (waitpid(-1, &status, 0) == -1)
            {
                perror("waitpid");
                return 1;
            }

            if (!WIFEXITED(status) ||
                WEXITSTATUS(status) != 0)
            {
                failed = 1;
            }

            active--;
        }

        pid_t pid = fork();

        if (pid == 0)
        {
            // Child process

            char filename[50];
            char scale_str[50];

            // Unique filename for each image
            snprintf(filename, sizeof(filename),
                     "mandel%d.jpg", i);

            // Zoom in gradually for each frame
            double scale = 0.2 * pow(0.95, i);

            snprintf(scale_str, sizeof(scale_str),
                     "%.12f", scale);

            // Run the original Mandelbrot program
            execl("./mandel", "mandel",
                  "-x", "-0.5",
                  "-y", "-0.5",
                  "-s", scale_str,
                  "-W", "1000",
                  "-H", "1000",
                  "-m", "1000",
                  "-o", filename,
                  (char *)NULL);

            // Only reached if execl fails
            perror("execl");
            _exit(1);
        }
        else if (pid > 0)
        {
            // Parent process
            active++;
        }
        else
        {
            perror("fork");
            failed = 1;
            break;
        }
    }

    // Wait for all remaining children
    while (active > 0)
    {
        int status;

        if (waitpid(-1, &status, 0) == -1)
        {
            perror("waitpid");
            return 1;
        }

        if (!WIFEXITED(status) ||
            WEXITSTATUS(status) != 0)
        {
            failed = 1;
        }

        active--;
    }

    if (failed)
    {
        fprintf(stderr,
                "One or more frames failed\n");
        return 1;
    }

    printf("All 50 frames completed!\n");

    return 0;
}
