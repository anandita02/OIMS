#include "headerfiles.h"

void builtinmodule(char promptstr[],vector<string>& arglist,int nw)
{ //cout<<"builtin"<<endl;
   vector<string>::iterator itr;
   itr=arglist.begin();
   string path,str;
   char *env;
   const char *name;
   int count=0;
   char buff[1000];
   unsigned int j=0,quote=0;
   env=(char *)malloc(sizeof(char)*1000); 
   if(strcmp((*itr).c_str(),(string("cd")).c_str())==0)
    { 
      itr++;
      if(itr==arglist.end())
      path="~";
      else path=(*itr).c_str();
     if(strcmp(path.c_str(),"~")==0)
      { 
        if(chdir("/home/anandita")<0) {perror("chdir");return;}
        strcat(promptstr,"~");
        
       }  
       else if(strcmp(path.c_str(),"#")==0)
       {
        if(chdir("/home/anandita")<0) {perror("chdir");return;}
        strcat(promptstr,"~");          
       }
       
      else
        {
         if(chdir(path.c_str())<0) {perror("chdir");return;}
            
        }

    }
   else if(strcmp((*itr).c_str(),(string("pwd")).c_str())==0)
           {getcwd(buff,100); cout<<endl<<buff<<endl;}
   


     else if(strcmp((*itr).c_str(),(string("echo")).c_str())==0)
           {   itr++;
                  for(;itr!=arglist.end();itr++)
                            {  
                                if(strcmp((*itr).c_str(),"$$")==0)
                                 { cout<<getpid()<<endl; return;}
				else if((*itr).at(0)=='$')
                                {  
				 strcpy(buff,(*itr).c_str());	
				 env=getenv(buff+1);
                                 if(env!=NULL) 
                                 {printf("%s\n",env);return;}
                                }
                                        
 				else if(((*itr).at(j)=='"'||(*itr).at(j)=='\'')&&quote==0) 
 				{quote=1;}
                                  
                                 if(quote==1)
                                 { 
				    for(j=0;j<(*itr).length();j++)
                                    {if(quote&&(((*itr).at(j))!='"'||((*itr).at(j))!='\''))
                                       {cout<<(*itr).at(j);}
				    }
                                }

				
                                  
                            }
                if(quote) {cout<<endl;return;}
                             
                itr=arglist.begin();           
                itr++;
              
                while(itr!=arglist.end())
                { cout<<*itr<<" ";itr++;}
                  cout<<endl;
  }
  

      else if(strcmp((*itr).c_str(),(string("export")).c_str())==0)
              {
                      //itr=arglist.begin();
                      ++itr;

                      for(;itr!=arglist.end();itr++)
 			{  
			  count++;
                          if(count>3) {cout<<"not valid"<<endl; return;} 
			   if(itr==arglist.begin()+1)
                               name=(*itr).c_str();
                           else if((*itr)=="=") continue;
                           
						//value=stringToint(*itr);
                            if(setenv(name,(*itr).c_str(), 1)<0) {perror(" ");return;}
                           	
			}
		  

              }       
        
} 





