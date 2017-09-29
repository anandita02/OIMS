#include"headerfiles.h"
#define LAST 10

void load_history(list<string>& histlist,int flag,char cmd[],int *count)
{
  
  string line,cmdstr;
  if(flag==1)
  {
  ifstream hfile("history7.txt");
  if(hfile.is_open())
   { 
      while(!hfile.eof())
       {
          getline(hfile,line);
           *count+=1;

          histlist.push_back(line);
         
        }  
       hfile.close();
      *count-=1;
   }
  }
 
 else if(flag==2)
  { 
    char  *c;
    c=(char *)malloc(sizeof(char)*10000);
    cmdstr=string(cmd);
    ofstream hfile;
    hfile.open("history7.txt",ios::app);
    *count+=1;
    intTostring((*count),c);
    
    strcat(c,cmdstr.c_str());
   
    cmdstr=string(c);    
   
    hfile<<cmdstr<<endl;
    
    hfile.close();
    
    
  }
     
}


