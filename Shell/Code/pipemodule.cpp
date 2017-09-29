#include "headerfiles.h"
#include<signal.h>
#define w 1
#define r 0
void spawn_proc (int in, int out,char **cmd);
void pipemodule(vector< vector<string> >& pc,int pipe_count,int fin,int fout)
{
   int i,fd[2],status,in=0;
   char **argv;
   pid_t pid,pid2;
   string fname;
   /*pipe(pipe1);
   pipe(pipe2);
   pid=fork();*/
   vector<string>::iterator it3;
   argv=(char **)malloc(sizeof(char *)*10);
    // cout<<"fin="<<fin<<"fout="<<fout<<endl;
    for(vector< vector<string> >::iterator it=pc.begin();it!=pc.end();it++)
    {
      i=0; 
       for(vector<string>::iterator it2=(*it).begin();it2!=(*it).end();it2++)
       {
        argv[i]=(char *)malloc(sizeof(char)*100);        //ch=v[i].c_str();
        strcpy(argv[i],(*it2).c_str());
        i++;
        }
        argv[i]=NULL;
      /* cout<<"*****command****"<<endl;
        for(i=0;argv[i]!=NULL;i++)
        printf("<<%s>>",argv[i]);*/
         pipe (fd);
        if(fout==1)
         {  it++;
            it3=(*it).begin();
            fname=*it3;
           const char *filename=fname.c_str();
           int outd=open(filename,O_RDWR|O_CREAT,0744);
            in=0;
            //cout<<"argv="<<argv<<endl;
            spawn_proc(in,outd,argv);
            
             return;
           
         } 
        if(fin==1)
         {  it++;
            it3=(*it).begin();
            fname=*it3;
           const char *filename=fname.c_str();
           int outd=open(filename,O_RDWR|O_CREAT,0744);
            in=outd;
            //cout<<"argv="<<argv<<endl;
            spawn_proc(in,1,argv);
            
             return;
           
         } 
        
      if(fin!=1&&fout!=1)
       {    
         
        
       if(it+1==pc.end())
       break;
           
     
      spawn_proc(in, fd [1], argv);
      close (fd [1]);
      in = fd [0];
        }  
 
     }        
         if(fin!=1&&fout!=1)
         {
           pid2=fork();
           if(pid2==0)
           {
             if(in != 0)
             dup2(in, 0);
             pid=fork();
             if(pid<0) {perror("fork");return;}
             if(pid==0)
             { 
              execvp(argv[0],argv);
             }
             while(wait(&status)!=pid);
              exit(1);
            }
              while(wait(&status)!=pid2);
              return;
          }

}

void spawn_proc(int in, int out,char **cmd)
{
  pid_t pid;
  int status;
  
  if ((pid = fork()) == 0)
    {
      if (in!=0)
        {
          dup2(in,0);
          close(in);
        }

      if (out!=1)
        {
          dup2(out,1);
          close(out);
        }

     execvp(cmd[0],cmd);
    }
   else
    {
        while(wait(&status)!=pid);
          return;
        //cout<<"pipeExecuted"<<endl;
    }



 // return pid;
}







