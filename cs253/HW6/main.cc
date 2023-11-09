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
#include <iostream>
#include <fstream>
#include <stdbool.h>

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

int  main(int argc , char *argv[]) {

	vector <string> command;
	string input;
	string word;
	if (argc == 1){
		string progName = argv[0];
		while( getline(cin, input)){
		bool oParen = false;
			for (size_t i = 0; i < input.size(); i++){
				if (!isspace(input[i])){
					if (input[i] == '('){
						oParen = true;
						if (!word.empty()){
							command.push_back(word);
							word = "";
						}
					}
					else if (input[i] == '\\' && (input[i+1] == '(' || input[i+1] == ')' || input[i] == '&' || input[i+1] == ' ')){
						word.push_back(input[i+1]);
					}
					else if (input[i] == '\\' && input[i+1] == '\\' && input[i+2] == 't'){
						command.push_back(word);
						word = "";
						for (size_t j = 0; j < 8; j++){
							word.push_back(' ');
						}
						command.push_back(word);
						word = "";
					}
 					else if (input[i] == '\t' || input[i] == '\n'){
						if (!word.empty()){
							command.push_back(word);
							word = "";
						}
					}
					else if (input[i] == '\\' && input[i+1] == '\\' && input[i+2] == 'n'){
						command.push_back(word);
						word = "";
					}
					else if  (input[i] == ')' && i == input.size() - 1){
						if (!word.empty()){
							command.push_back(word);
							word = "";
						}

						if (execute(command)){

							for (size_t k = 1; k < command.size(); k++){
								if (command[k]  != "-e" && command[k] == "\n"){
									cout << "\n";
								}
								else if (command[k] == "\t"){ 

									cout << command[k] << "\n";
								}
							}
							command.clear();
						}
						else {
							cerr << progName + ": can't run: " + input << "\n";
							return 1;
						}
					}
					else if (input[i] ){
						word.push_back(input[i]);
					}
				}
				else{
					if (input[i+1] == '('){
						command.push_back(word);
						word = "";
					}
					else if (oParen){
						if (input[i+1] != ' ' && (input[i+2] != ' ' || input[i+2] != ')')){
							word.push_back(input[i]);
						}
					}
				}
			}
		}
	}
	else if  (argc == 2){
		string progName = argv[0];
		string file = argv[1];
		ifstream file1 (file);
		while( getline(file1, input)){
		bool oParen = false;
			for (size_t i = 0; i < input.size(); i++){
				if (!isspace(input[i])){
					if (input[i] == '('){
						oParen = true;
						if (!word.empty()){
							command.push_back(word);
							word = "";
						}
					}
					else if (input[i] == '\\' && (input[i+1] == '(' || input[i+1] == ')' || input[i] == '&' || input[i+1] == ' ')){
						word.push_back(input[i+1]);
					}
					else if (input[i] == '\\' && input[i+1] == '\\' && input[i+2] == 't'){
						command.push_back(word);
						word = "";
						for (size_t j = 0; j < 8; j++){
							word.push_back(' ');
						}
						command.push_back(word);
						word = "" ;
					}
					else if (input[i] == '\t' || input[i] == '\n'){
						if (!word.empty()){
							command.push_back(word);
							word = "";
						}
					}
					else if (input[i] == '\\' && input[i+1] == '\\' && input[i+2] == 'n'){
						command.push_back(word);
						word = "";
					}
					else if  (input[i] == ')' && i == input.size() - 1){
						if (!word.empty()){
							command.push_back(word);
							word = "";
						}
						if (execute(command)){
							for (size_t k = 1; k < command.size(); k++){
								if (command[k]  != "-e" && command[k] == "\n"){
									cout << "\n";
								}
								else if (command[k] == "\t"){
									cout << command[k] << "\n";
								}
							}
							command.clear();
						}
						else {
							cerr <<  progName + ":can't run: " + input << "\n";
							return 1;
						}
					}
					else if (input[i] ){
						word.push_back(input[i]);
					}
				}
				else{
					if (input[i+1] == '('){
						command.push_back(word);
						word = "";
					}
					else if (oParen){
						if (input[i+1] != ' ' && (input[i+2] != ' ' || input[i+2] != ')')){
							word.push_back(input[i]);
						}
					}
				}
			}
		}
	}
	else if (argc == 3){
		string progName = argv[0];
                string file = argv[1];
		string file2 = argv[2];
                ifstream file1 (file);
		ifstream file3 (file2);
		while( getline(file1, input)){
		bool oParen = false;
			for (size_t i = 0; i < input.size(); i++){
				if (!isspace(input[i])){
					if (input[i] == '('){
						oParen = true;
						if (!word.empty()){
							command.push_back(word);
							word = "";
						}
					}
					else if (input[i] == '\\' && (input[i+1] == '(' || input[i+1] == ')' || input[i] == '&' || input[i+1] == ' ')){
						word.push_back(input[i+1]);
					}
					else if (input[i] == '\\' && input[i+1] == '\\' && input[i+2] == 't'){
						command.push_back(word);
						word = "";
						for (size_t j = 0; j < 8; j++){
							word.push_back(' ');
						}
						command.push_back(word);
						word = "";
					}
					else if (input[i] == '\t' || input[i] == '\n'){
						if (!word.empty()){
							command.push_back(word);
							word = "";
						}
					}
					else if (input[i] == '\\' && input[i+1] == '\\' && input[i+2] == 'n'){
						command.push_back(word);
						word = "";
					}
					else if  (input[i] == ')' && i == input.size() - 1){
						if (!word.empty()){
							command.push_back(word);
							word = "";
						}
						if (execute(command)){
							for (size_t k = 1; k < command.size(); k++){
								if (command[k]  != "-e" && command[k] == "\n"){
									cout << "\n";
								}
								else if (command[k] == "\t"){
									cout << command[k] << "\n";
								}
							}
							command.clear();
						}
						else {
							cerr <<  progName + ":can't run: " + input << "\n";
							return 1;
						}
					}
					else if (input[i] ){
						word.push_back(input[i]);
					}
				}
				else{
					if (input[i+1] == '('){
						command.push_back(word);
						word = "";
					}
					else if (oParen){
						if (input[i+1] != ' ' && (input[i+2] != ' ' || input[i+2] != ')')){
							word.push_back(input[i]);
						}
					}
				}
			}
		}
		while( getline(file3, input)){
		bool oParen = false;
			for (size_t i = 0; i < input.size(); i++){
				if (!isspace(input[i])){
					if (input[i] == '('){
						oParen = true;
						if(!word.empty()){
							command.push_back(word);
							word = "";
						}
					}
					else if (input[i] == '\\' && (input[i+1] == '(' || input[i+1] == ')' || input[i] == '&' || input[i+1] == ' ')){
						word.push_back(input[i+1]);
					}
					else if (input[i] == '\\' && input[i+1] == '\\' && input[i+2] == 't'){
						command.push_back(word);
						word = "";
						for (size_t j = 0; j < 8; j++){
							word.push_back(' ');
						}
						command.push_back(word);
						word = "";
					}
					else if (input[i] == '\t' || input[i] == '\n'){
						if (!word.empty()){
							command.push_back(word);
							word = "";
						}
					}
					else if (input[i] == '\\' && input[i+1] == '\\' && input[i+2] == 'n'){
						command.push_back(word);
						word = "";
					}
					else if  (input[i] == ')' && i == input.size() - 1){
						if (!word.empty()){
							command.push_back(word);
							word = "";
						}
						if (execute(command)){
							for (size_t k = 1; k < command.size(); k++){
								if (command[k]  != "-e" && command[k] == "\n"){
									cout << "\n";
								}
								else if (command[k] == "\t"){
									cout << command[k] << "\n";
								}
							}
							command.clear();
						}
						else {
							cerr <<  progName + ":can't run: " + input << "\n";
							return 1;
						}
					}
					else if (input[i] ){
						word.push_back(input[i]);
					}
				}
				else{
					if (input[i+1] == '('){
						command.push_back(word);
						word = "";
					}
					else if (oParen){
						if (input[i+1] != ' ' && (input[i+2] != ' ' || input[i+2] != ')')){
							word.push_back(input[i]);
						}
					}
				}
			}
		}
	}
	else {
		cerr << "Too Many Arguements" << "\n";
		return 1;
	}
	return 0;
}
