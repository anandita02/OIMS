#include "headerfiles.h"

#define LAST 10

void  sighandle1(int sig)
{ 
    //main();
   printf("\n");
   prompt_and_parse();
  //return ;
  
}
int number_of_args(char *cmd)
{
 
  int i,quote=0,count=0;
  for(i=0;cmd[i]!='\0';i++)
  {
    if(cmd[i]=='\"'&&(quote==0))
      {quote=1;}
    else if((cmd[i]==' '||cmd[i]=='\t'||cmd[i]=='\n')&&(quote==0))
      {count++;}
    else if(cmd[i]=='\"'&&(quote==1))
      {quote=0;}
      
  }
  return count+1;

}
int make_array_of_args(char *cmd,vector<string>& arglist,vector< vector<string> >& pc,int nw,int *flag_input_redirection,int *flag_output_redirection)
{
   int i,j,count=0,quote=0,pipe_count=0;
   
   string str;
   char buff[10000];
   j=0;
   for(i=0;cmd[i]!='\0';i++)
   {  
      if(cmd[i]=='"'&&quote==0)
      {quote=1; buff[j]='"';j++;}
      else if(cmd[i]=='"'&&quote==1)
      {quote=0; buff[j]='"';j++;}
      else if((cmd[i]==' '||cmd[i]=='\t'||cmd[i]=='\n')&&(quote==0))
      {
         count++;
         buff[j]='\0';
         str=string(buff); 
         arglist.push_back(str);
         //cout<<"str="<<str;
         if(str.compare("|")==0||str.compare("<")==0||str.compare(">")==0)
         {
	  if(str.compare("<"))
	     *flag_output_redirection=1;
           if(str.compare(">"))
             {*flag_input_redirection=1;}
         
          pipe_count++;//used for last command
         arglist.pop_back();
         //cout<<"multi vector"<<endl;
         handle_quotes(arglist);
         pc.push_back(arglist);
         arglist.clear();
         }
         str.erase(0, str.length());
         j=0;
      }
      else
        {
          buff[j]=cmd[i];
          j++;
         }
   }
    if(count+1==nw)
      { 
      buff[j]='\0';
      str=string(buff);
      arglist.push_back(str);
      }
      if(pipe_count>0)
       { pc.push_back(arglist);
          /*for ( std::vector<std::vector<std::string> >::iterator it1 = pc.begin(); it1 != pc.end(); ++it1 )
          {
	     for ( std::vector<std::string>::iterator it2 = (*it1).begin(); it2 != (*it1).end(); ++ it2 )
	      {
		std::cout << (*it2); // print the strings
	      }
	      cout<<endl;
	  }*/
      } 
               
    
     return pipe_count;  
    
}
void prompt_and_parse()
{

char *cmd,*cmdcount,*cmdprev;
    char promptstr[1000]={'m','y','S','h','e','l','l','@','m','y','S','h','e','l','l','\0'};

    vector<vector<string> > pc;
    list<string> histlist;
    list<string>::iterator list_itr;
    std::vector<string> arglist;
    std::vector<string>::iterator it;
    std::vector<string> execvcmands;
    std::vector<string> builtincmands;
    int nw,i,j,pipe_count,first_time=1;
    int count=0,hist_from=0,notsame=0;
    int flag_input_redirection,flag_output_redirection;
    string strcmd;
    char buff[100];
    
    cmdprev=(char*)malloc(sizeof(char)*1000);

    signal(SIGINT,sighandle1);
    
    while(1)
    {
    
    flag_input_redirection=0,flag_output_redirection=0;
    cmd=(char*)malloc(sizeof(char)*1000);
    cmdcount=(char*)malloc(sizeof(char)*10);
    
    getcwd(buff,100);
    
    strcat(promptstr,buff);
   
    strcat(promptstr,"$ ");

    cout<<promptstr;
    strcpy(promptstr,"myshell@myshell");
 
    scanf(" %[^\n]",cmd);
   

 
    if(strcmp(cmd,"!!")==0)
    {strcpy(cmd,cmdprev);}
    else if(cmd[0]=='!')
    {
    hist_from=stringToint(cmd);
    if(hist_from<=0) {cout<<"event not found"<<endl;continue;}
    list_itr=histlist.end();
    for(i=0;i<hist_from;i++)
      list_itr--;
    
    i=0;j=0;
    while((*list_itr).at(i++)!=' ');
    for(;i<(*list_itr).length();i++)
    {
     cmd[j]=(*list_itr).at(i);j++;}
     cmd[j]='\0';
    }
    
    //cout<<"*****1*******"<<endl;
    
    notsame=0;
    
    for(i=0;first_time==0&&cmd[i]!=0;i++)
    {
    if(cmd[i]!=cmdprev[i])
    {
    notsame=1;
    break;
    }
    }
    if(first_time)
    load_history(histlist,1,cmd,&count);
       //1 for load from file into the histlist
    if(first_time==1||notsame==1)
    {
    
    first_time=0;
    load_history(histlist,2,cmd,&count);//2 for insertion in the file
    //cout<<"cmd="<<cmd<<endl;
    intTostring(count,cmdcount);
    
    strcmd=string(cmd);
    
    strcat(cmdcount,strcmd.c_str());
    
    histlist.push_back(cmdcount);
    
    /*for(list_itr=histlist.begin();list_itr!=histlist.end();list_itr++)
    cout<<"hist="<<*(list_itr)<<endl;*/
    }
    
    nw=number_of_args(cmd);
    pipe_count=make_array_of_args(cmd,arglist,pc,nw,&flag_input_redirection,&flag_output_redirection);
    

    
   

   
    /*for(it=arglist.begin();it!=arglist.end();it++)
        cout<<"arg="<<*(it)<<endl;*/
    
    if(std::find(arglist.begin(), arglist.end(), "exit") != arglist.end())
    {
     cout<<"bye.."<<endl;
     exit(0);
    }
    
    if(pipe_count>0)
    {
     //cout<<"calling pipe module"<<endl;
     
     pipemodule(pc,pipe_count,flag_input_redirection,flag_output_redirection);
    
     for(i=0;i<arglist.size();i++)
     arglist.pop_back();
     arglist.clear();
     pc.clear();
     
     continue;
    
     }

     handle_quotes(arglist);



    if(std::find(arglist.begin(), arglist.end(), "history") != arglist.end())
    {
	if(strcmp(cmd,"history")==0)
        {
        for(list_itr=histlist.begin();list_itr!=histlist.end();list_itr++)
        cout<<*(list_itr)<<endl;
        }
        else
        {
          hist_from=stringToint(arglist.back());
          if(hist_from<0) cout<<"invalid command"<<endl;
          else
          {
            list_itr=histlist.end();
            for(i=0;i<hist_from;i++)
            {
              list_itr--;
            }
            
            while(list_itr!=histlist.end())
             {
               cout<<*(list_itr)<<endl;
               list_itr++;
             }
            
          }
        }
    }
    else
    {
     
    builtincmands.push_back("pwd");
    builtincmands.push_back("cd");
    builtincmands.push_back("export");
    builtincmands.push_back("echo");
    
  
    if(std::find(builtincmands.begin(),builtincmands.end(), arglist[0]) != builtincmands.end())
    builtinmodule(promptstr,arglist,nw); 
    
 
    else execvmodule(arglist,1,nw);
   }
    strcpy(cmdprev,cmd);
    
    
    
    for(i=0;i<arglist.size();i++)
    arglist.pop_back();
    arglist.clear();
    pc.clear();
     free(cmd);
     
     
    }
}
   
