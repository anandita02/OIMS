#include<iostream>
#include<stdio.h>
#include<string>
#include<string.h>
#include<vector>
#include<algorithm>
#include<unistd.h>
#include<stdlib.h>
#include <sys/types.h>
#include <errno.h>
#include <stdio.h>
#include <sys/wait.h>
#include<signal.h>
#include<queue>
#include<list>
#include<fstream>
#include<sys/stat.h>
#include<fcntl.h>

using namespace std;
void intTostring(int count,char c[]);
int stringToint(string str);
void execvmodule(vector<string>& arglist,int flag,int nw);
void load_history(list<string>& histlist,int flag,char cmd[],int *count);
void builtinmodule(char promptstr[],vector<string>& arglist,int nw); 
void pipemodule(vector< vector<string> >& pc,int pipe_count,int fin,int fout);
void handle_quotes(vector<string>& arglist);
void prompt_and_parse();
void  sighandle1(int sig);
