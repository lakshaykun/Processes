#include <iostream>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <cstring>
#include <sys/mman.h>

using namespace std;

int main(int argc, char *argv[]) {
    if (argc < 2) {
        cout << "command to run not found" << endl;
        return 1;
    } 

    // Create shared memory for start time using mmap
    struct timeval* startTiming = static_cast<struct timeval*>(
        mmap(nullptr, sizeof(struct timeval), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0)
    );
    
    // Check if mmap failed
    if (startTiming == MAP_FAILED) {
        perror("mmap");
        return 1;
    }

    struct timeval endTiming;
    pid_t pid = fork(); // Fork a child process

    if (pid < 0) {
        // Fork failed to create child process
        perror("fork");
        return 1;

    } else if (pid == 0) {
        // Child process
        
        // Get the start time
        gettimeofday(startTiming, nullptr);

        // Execute the command
        extern char **environ;

        // Create the command path by concatenating "/bin/" with argv[1]
        string commandPath = string("/bin/") + argv[1];

        // Convert the string to a C-style string
        char *command = new char[commandPath.length() + 1];
        strcpy(command, commandPath.c_str());

        execve(command, &argv[1], environ);

        // If execvp returns, there was an error
        perror("execve");
        return 1;

    } else {
        // Parent process
        int status;
        waitpid(pid, &status, 0); // Wait for the child process to finish

        // Get the end time
        gettimeofday(&endTiming, nullptr);

        // Calculate the elapsed time
        double timeTaken = (endTiming.tv_sec - startTiming->tv_sec) + (endTiming.tv_usec - startTiming->tv_usec) / 1000000.0;

        // Output the time taken for the command to execute
        cout << "time taken for shared memory method: " << timeTaken << " seconds" << endl;

        // Unmap the shared memory after use
        munmap(startTiming, sizeof(struct timeval));
    }

    return 0;
}
