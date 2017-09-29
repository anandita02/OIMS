#include "headerfiles.h"
/*void  sighandle1(int sig)
{ 
    //main();
   //signal(SIGINT,sighandle1);
  //return ;
  
}*/
void execvmodule(vector<string>& arglist,int flag,int nw)
{
   char **argv;
   string str;
   pid_t pid1;
   //const char * ch;
   argv=(char **)malloc(sizeof(char *)*nw);
   //std::vector<string>::iterator it1;
   int i,status;
   
   
   for(i=0;i<arglist.size();i++)
    {
        argv[i]=(char *)malloc(sizeof(char)*100);        
        strcpy(argv[i],arglist[i].c_str());
        
    }
    argv[i]=NULL;
    //signal(SIGINT,sighandle1);
   
   
    pid1=fork();
    if(pid1<0) 
    {
    perror(" ");
    exit(1);
    }
    else if(pid1==0)   
    {
        
       //signal(SIGINT,sighandle1);
    if(execvp(argv[0],argv)<0)
    cout<<"command not found"<<endl;return;
    }
    else
    {
        // kill(pid1,SIGINT);
     while(wait(&status)!=pid1);
       //while(wait(&status)!=pid1); 
    }
    
    return;
       
}

