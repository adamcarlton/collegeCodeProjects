//Adam Carlton, acarlton, CIS 415 PROJECT 1
//This is my own work
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
#define INTERVAL 250
typedef struct process{
    pid_t pid;
    struct process *next;
    int status;
}proc;
typedef struct pQueue{
    proc *head;
    proc *tail;
}pQ;
int nprocesses;
int nprocessors;
int usr1_received;
int deadChildren = 0;
//int *deadProc;
pQ runQ;
pQ waitQ;
char *ioBuf;
char *ioInfo;
char *statusBuf;
char *infoBuf;
proc* deq(pQ*);
void enq(pQ*, proc*);
void printInfo(pid_t);
void printIO(pid_t);
void sig_handler(int);
void sig_alrm(int);
void sig_chld(int);


int main(int argc, char *argv[]){
    if(signal(SIGUSR1, sig_handler)==SIG_IGN){
        signal(SIGUSR1, SIG_IGN);}
    
    if(argc > 4 || argc < 2 ){
        p1putstr(2, "Program requires a command to run\n");
        _exit(0);}
    ioBuf = malloc(sizeof(char) * 512);
    statusBuf = malloc(sizeof(char) * 512);
    infoBuf = malloc(sizeof(char) * 2056);
    ioInfo = malloc(sizeof(char) * 2056);
    runQ.head = NULL;
    runQ.tail = NULL;
    waitQ.head = NULL;
    waitQ.tail = NULL;
    char *command;
    char *nprocess;
    char *nprocessor;
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
        command = &arg1[10];}
    if(p1strneq(arg2Word, comChk, 5) == 1){
        comTrue = 1;
        command = &arg2[10];}
    if(p1strneq(arg3Word, comChk, 5) == 1){    
        comTrue = 1;
        command = &arg3[10];}
    
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
    struct timeval tvS, tvE;
    pid_t pid[nprocesses];
    struct itimerval timer;
    signal(SIGUSR1, sig_handler);
    signal(SIGALRM, sig_alrm);
    signal(SIGCHLD, sig_chld);
    proc *pidTemp = malloc(sizeof(proc)*nprocesses);
    gettimeofday(&tvS, NULL);
    for(i = 0; i<nprocesses; i++){
        if((pid[i] = fork()) < 0){
            p1perror(2, "Fork failed\n");
            _exit(errno);
        }
        if(pid[i] == 0){
            while(!usr1_received){
                pause();
            }
            char *err = "\0";
            p1putstr(2, err);
            if(execvp(args[0], args)< 0){
                p1perror(2, "Execvp failed\n");
                _exit(errno);
                }
            }
        pidTemp[i].pid = pid[i];
        pidTemp[i].next = NULL;
        pidTemp[i].status = 0;
        enq(&waitQ, &pidTemp[i]);
    }
    timer.it_value.tv_sec = INTERVAL/1000;
    timer.it_value.tv_usec = (INTERVAL*1000) % 1000000;
    timer.it_interval = timer.it_value;
    if(setitimer(ITIMER_REAL, &timer, NULL)!=0){
        p1perror(2, "setitimer fail\n");
        _exit(errno);
    }
    while(deadChildren < nprocesses){
        pause();
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
    free(pidTemp);
    free(ioBuf);
    free(ioInfo);
    free(infoBuf);
    free(statusBuf);
    return 0;
}

void sig_handler(int signum){
    if(signum == SIGUSR1){
        usr1_received++;
    }
    else{
        p1putstr(2, "Expected SIGUSR1\n");
        _exit(errno);
    }
}

void sig_alrm(int sign){
    if(sign == SIGALRM){
        int i;
        int n;
        proc *waitDeq;
        proc *runDeq;
        if(deadChildren == nprocesses){
            return;
        }
        if(runQ.head == NULL){
            for(i = 0; i < nprocessors; i++){
                waitDeq = deq(&waitQ);
                if(waitDeq->status == 0){
                    if(kill(waitDeq->pid, SIGUSR1) != 0){
                        p1perror(2, "Failed to pass sigusr1\n");
                        _exit(errno);
                    }
                    printIO(waitDeq->pid);
                    printInfo(waitDeq->pid);
                    waitDeq->status = 1;
                }
                else if(waitDeq->status == 2){
                    if(kill(waitDeq->pid, SIGCONT) != 0){
                        p1perror(2, "Failed to continue\n");
                        _exit(errno);
                    }
                    waitDeq->status = 1;
                    printInfo(waitDeq->pid);
                    printIO(waitDeq->pid);
                }
                enq(&waitQ, waitDeq);
            }
        }
        else if(runQ.head != NULL){
            runDeq = deq(&runQ);
            if(runDeq->status == 1){
                if(kill(runDeq->pid, SIGSTOP) != 0){
                    p1perror(2, "Failed to stop\n");
                    _exit(errno);
                }
                fprintf(stderr, "%d\n", runDeq->pid);
                runDeq->status = 2;
            }
            enq(&waitQ, runDeq);
            while(n < nprocessors){
                waitDeq = deq(&waitQ);
                if(waitDeq->status == 0){
                    if(kill(waitDeq->pid, SIGUSR1) != 0){
                        p1perror(2, "Failed to pass sigusr1\n");
                        _exit(errno);
                    }
                    waitDeq->status = 1;
                    printIO(waitDeq->pid);
                    printInfo(waitDeq->pid);
                }
                else if(waitDeq->status == 2){
                    printInfo(waitDeq->pid);
                    if(kill(waitDeq->pid, SIGCONT) != 0){
                        p1perror(2, "Failed to continue\n");
                        _exit(errno);
                    }
                    waitDeq->status = 1;
                    printIO(waitDeq->pid);
                    printInfo(waitDeq->pid);
                }
                enq(&runQ, waitDeq);
                n++;
            }
        }
    }
    else{
        p1perror(2, "Expected SIGALRM\n");
        _exit(errno);
    }
}
void sig_chld(int sign){
if(sign == SIGCHLD){
        pid_t pid;
        int status;
        while((pid = waitpid(-1, &status, WNOHANG)) > 0){
            if(WIFEXITED(status)){
                deadChildren++;
            }
        }
    }
    else{
        p1perror(2, "Expected a SIGCHLD signal\n");
        _exit(errno);
    }
}

proc* deq(pQ* queue){
    if(queue->head == NULL){
        return NULL;
    }
    else if(queue->head == queue->tail){
        proc *temp = queue->head;
        queue->head = NULL;
        queue->tail = NULL;
        return temp;
    }
    proc *temp;
    temp = queue->head;
    queue->head = temp->next;
    return temp; 
}

void enq(pQ *queue, proc *process){
    proc *temp = process;
    if(queue->head == NULL){
        queue->head = temp;
        queue->tail = temp;
        return;
    }
    queue->tail->next = temp;
    queue->tail = temp;
}

void printInfo(pid_t queuedPid){
   char *pidWord = malloc(sizeof(char) * 6);
   int newPid = queuedPid;
   p1itoa(newPid, pidWord);
   p1strcat(statusBuf, "/proc/");
   p1strcat(statusBuf, pidWord);
   p1strcat(statusBuf, "/status");
   p1putstr(1, "\n");
   p1putstr(1, "------------\n");
   p1putstr(1, "status\n");
   p1putstr(1, "------------\n");
   p1putstr(1, "\n");
   int statusFd = open(statusBuf, O_RDONLY);
   read(statusFd, infoBuf, 2056);
   p1putstr(1, "\n");
   p1putstr(1, infoBuf);
   p1putstr(1, "\n");
   free(pidWord);
}

void printIO(pid_t queuedPid){

   char *pidWord = malloc(sizeof(char) * 6);
   int newPid = queuedPid;
   p1itoa(newPid, pidWord);
   p1strcat(ioBuf, "/proc/");
   p1strcat(ioBuf, pidWord);
   p1strcat(ioBuf, "/io");
   p1putstr(1, "\n");
   p1putstr(1, "------------\n");
   p1putstr(1, "INPUT/OUTPUT\n");
   p1putstr(1, "------------\n");
   int ioFd = open(ioBuf, O_RDONLY);
   read(ioFd, ioInfo, 2056);
   p1putstr(1, "\n");
   p1putstr(1, ioInfo);
   p1putstr(1, "\n");
   free(pidWord);
}
