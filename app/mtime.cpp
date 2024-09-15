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

    int pipeFD[2]; // File descriptors for the pipe
    if (pipe(pipeFD) == -1) {
        perror("pipe failed to create");
        return 1;
    }

    struct timeval startTiming, endTiming;
    pid_t pid = fork();

    if (pid < 0) {
        // Fork failed
        perror("fork failed to create child process");
        return 1;

    } else if (pid == 0) {
        // Child process
        gettimeofday(&startTiming, nullptr);
        close(pipeFD[0]); // Close the read end of the pipe
        write(pipeFD[1], &startTiming, sizeof(startTiming)); // Write startTiming to parent process through pipe
        close(pipeFD[1]); // Close the write end of the pipe after writing

        // Execute the command using execve
        extern char **environ;
        execve(argv[1], &argv[1], environ);
        // If execve returns, there was an error
        perror("execve failed to execute command");
        return 1;

    } else {
        // Parent process
        close(pipeFD[1]); // Close the write end of the pipe 

        int status;
        waitpid(pid, &status, 0); // Wait for the child process to finish

        read(pipeFD[0], &startTiming, sizeof(startTiming)); // Read startTiming from child process
        close(pipeFD[0]); // Close the read end of the pipe after reading

        gettimeofday(&endTiming, nullptr); // Record the end timing after child process finishes

        // Calculate the time taken in seconds
        double timeTaken = (endTiming.tv_sec - startTiming.tv_sec) + (endTiming.tv_usec - startTiming.tv_usec) / 1000000.0;

        // Output the time taken
        cout << "Time taken for message passing method: " << timeTaken << " seconds" << endl;
    }

    return 0;
}
