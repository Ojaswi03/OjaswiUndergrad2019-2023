// Use g++ -std=c++17 -Wall to compile this code.
//
// This code demonstrates spawning a process using fork() & exec().
//
// There are three steps:
//
// 1) Create a duplicate of the current process (this program)
//    using fork().  When fork() returns, there will be TWO
//    processes running: the original (called the parent)
//    and the new process (called the child).  They use the value
//    returned by fork() to tell which is which.
//
// 2) The child process uses execvp() to replace itself with
//    another program.  The newly-created child process is now
//    running a completely different program.
//
// 3) The parent process uses wait() to wait for the child
//    process to finish.  The return value from wait() contains
//    the 8-bit exit code of the child process in its UPPER
//    eight bits, and the signal that terminated the process
//    (usually 0, if the process ended normally) in its LOWER
//    eight bits.  Return -1 upon fork or exec error.

#include <sys/types.h>	// fork() & wait()
#include <unistd.h>	// fork(), execvp()
#include <cstdlib>	// exit()
#include <wait.h>	// wait()
#include <vector>	// vector<>
#include <string>	// string

using namespace std;

bool execute(vector<string> command) {
    // Convert vector of C++ strings to an array of C strings for exectp():
    vector<char *> argv;		// vector of C string pointers
    for (auto &v : command)		// for each C++ string:
	argv.push_back(v.data());	//    add address of C-string inside it
    argv.push_back(nullptr);		// argv ends with a null pointer

    // Duplicate ourself: -1:error, 0:child, >0:parent
    const auto pid = fork();		// step #1: copy ourself
    if (pid < 0)
	return false;			// fork failure?
    if (pid == 0) {			// child?
	execvp(argv[0], argv.data());	// step #2: replace child with new prog
	exit(0xff);			// only got here if execvp() failed.
    }
    int status;
    wait(&status);			// step #3: wait for child to finish
    return status != 0xff00;		// true iff we succeeded
}

int main() {
    execute({"echo", "Hello there", "friend!"});
    vector<string> command = {"date", "+%A"};
    execute(command);
    command.push_back("-d tomorrow");
    execute(command);
    return 0;
}
