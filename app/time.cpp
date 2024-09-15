#include <iostream>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <cstring>

using namespace std;

int main(int argc, char *argv[]) {
    if (argc < 2) {
        cout << "command to run not found" << endl;
        return 1;
    }

    struct timeval startTiming, endTiming;

    // Get the start time of the program
    gettimeofday(&startTiming, nullptr);

    // Fork a child process
    pid_t pid = fork();

    if (pid < 0) {
        // Fork failed
        perror("fork");
        return 1;

    } else if (pid == 0) {
        // Child process
        
        extern char **environ; // Environment variables
        
        // Execute the command using execve
        execve(argv[1], &argv[1], environ);

        // If execve returns, there was an error
        perror("execve");
        return 1;

    } else {
        // Parent process

        int status;
        waitpid(pid, &status, 0); // Wait for the child process to finish

        // Get the end time of the program
        gettimeofday(&endTiming, nullptr);

        // Calculate the time taken in seconds
        double timeTaken = (endTiming.tv_sec - startTiming.tv_sec) + (endTiming.tv_usec - startTiming.tv_usec) / 1000000.0;

        // Output the time taken for the command to execute
        cout << "time taken for normal method: " << timeTaken << " seconds" << endl;
    }

    return 0;
}
