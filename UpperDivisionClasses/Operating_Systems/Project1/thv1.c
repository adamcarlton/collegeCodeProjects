//Adam Carlton, acarlton, CIS 415 PROJECT 1
//This is my own work except for assistance with formatting the
//time by Edward Szczepanski and parsing the full command by
//Allen Roush
#include "p1fxns.h"
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <signal.h>


int main(int argc, char *argv[]){
    if(argc > 4 || argc < 2 ){
        p1putstr(2, "Program requires a command to run\n");
        _exit(0);}
    char *command;
    char *nprocess;
    char *nprocessor;
	int nprocesses;
	int nprocessors;
    char comChk[5] = {"--com"};
    char numChk[5] = {"--num"};
    char procChk[5] = {"--pro"};
    int comTrue = 0;    
    int numArg = 0;
    int procArg = 0;
    char *arg1 = argv[1];
    char *arg2;
    char *arg3;
	char arg1Word[256] = {'\0'};
    char arg2Word[256] = {'\0'};
	char arg3Word[256] = {'\0'};
    
    int arg1_loc = 0;
    arg1_loc = p1getword(arg1, arg1_loc, arg1Word);
   
    if(argv[2] != NULL){
	    arg2 = argv[2];
        int arg2_loc = 0;
        arg2_loc = p1getword(arg2, arg2_loc, arg2Word);}
    if(argv[3] != NULL){
        arg3 = argv[3];
        int arg3_loc = 0;
        arg3_loc = p1getword(arg3, arg3_loc, arg3Word);}
    
    if(p1strneq(arg1Word, numChk, 5) == 1){
        numArg = 1;
        nprocesses = p1atoi(&arg1[9]);}
    if(p1strneq(arg2Word, numChk, 5) == 1){
        numArg = 1;
        nprocesses = p1atoi(&arg2[9]);}
    if(p1strneq(arg3Word, numChk, 5) == 1){
        numArg = 1;
        nprocesses = p1atoi(&arg3[9]);}
    
    if(p1strneq(arg1Word, procChk, 5) == 1){
        procArg = 1;
        nprocessors = p1atoi(&arg1[13]);}
    if(p1strneq(arg2Word, procChk, 5) == 1){
        procArg = 1;
        nprocessors = p1atoi(&arg2[13]);}
    if(p1strneq(arg3Word, procChk, 5) == 1){
        procArg = 1;
        nprocessors = p1atoi(&arg3[13]);}
    
    if(p1strneq(arg1Word, comChk, 5) == 1 ){
        comTrue = 1;
        char *comm = &arg1[10]; 
        command = comm;}
    if(p1strneq(arg2Word, comChk, 5) == 1){
        comTrue = 1;
        char *comm = &arg2[10]; 
        command = comm;}
    if(p1strneq(arg3Word, comChk, 5) == 1){    
        comTrue = 1;
        char *comm = &arg3[10]; 
        command = comm;}
    
    if(procArg == 0){
	    if((nprocessor = getenv("TH_NPROCESSORS")) != NULL){
		    nprocessors = p1atoi(nprocessor);}
        else{
            p1putstr(2, "There is no argument or environment variable that specifies # of processors\n");
            _exit(0);}
    }
    if(numArg == 0){
	    if((nprocess = getenv("TH_NPROCESSES"))!= NULL){
		    nprocesses = p1atoi(nprocess);}	
        else{
            p1putstr(2, "There is no argument or env variable that specifies # of processes\n");
            _exit(0);}
    }
    if(comTrue == 0){
        p1putstr(2, "You need a command to run\n");
        _exit(0);}
    struct timeval tvS, tvE;
    pid_t pid[nprocesses];
	int i;
    
    int iterator = 0;
    
    char **args = malloc(sizeof(char*) * (p1strlen(command)+1));
    for(i = 0; i < p1strlen(command) + 1; i++){
        args[i] = malloc(sizeof(char) * 100);}
    int arg_loc = 0;
    
    arg_loc = p1getword(command, arg_loc, args[iterator]);
    
    while(arg_loc != -1){
        iterator++;
        arg_loc = p1getword(command, arg_loc, args[iterator]);}
    free(args[iterator]);
    args[iterator] = NULL;
    
    gettimeofday(&tvS, NULL);
    
    for(i = 0; i<nprocesses; i++){
        pid[i] = fork();
        if(pid[i] < 0){
            p1perror(2, "Fork failed");
            _exit(errno);}
        if(pid[i] == 0){
            char *err = "\0";
            p1putstr(2, err);
            if(execvp(args[0], args)< 0){
                p1perror(2, "Execvp failed\n");
                _exit(errno);}
        }
        else if(pid[i] > 0){
            wait(pid + i);
        }
    }        
    gettimeofday(&tvE, NULL);
    float elapseTime = (((tvE.tv_sec - tvS.tv_sec)*1000000L + tvE.tv_usec)-tvS.tv_usec)/1000000.0;
    int leftPer = (int)elapseTime;
    int rightPer = (int)((elapseTime-leftPer)*1000);
    char *message = "The elapsed time to execute ";
    p1putstr(1, message);
    p1putint(1, nprocesses);
    p1putstr(1, " copies of \"");
    p1putstr(1, command);
    p1putstr(1, "\" on ");
    p1putint(1, nprocessors);
    p1putstr(1, " processors is ");
    p1putint(1, leftPer);
    p1putstr(1, ".");
    p1putint(1, rightPer);
    p1putstr(1, " seconds\n");
    for(i = 0; i < p1strlen(command)+1; i++){
        free(args[i]);}
    free(args);
    return 0;}

        
