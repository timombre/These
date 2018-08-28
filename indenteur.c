#include <stdio.h>
#define MAX_FILE 1000000
typedef enum 
{
  false, true, halftrue
}
 boolean;

void BeginLine(int nbtabs, char fstr[], long int index)
{
  int j;
  for(j=0;j<2*nbtabs;j++)fstr[index++] = ' ';
   
}
void Indent(FILE* pFile, int nbtabs, char fstr[], long int i, char c)
{
  boolean newline=true, expr=false, cond=false, comm=false;  
  while(i<MAX_FILE && !feof(pFile))
  {
    c = fgetc(pFile);
    switch(c)
    {
      case ' ':
      if(newline==true)break;
      else fstr[i++] = c;break;
      case ',':fstr[i++] = c;
      if(!expr)fstr[i++] = ' ';
      break;
      case '*':
          if(fstr[i-1]=='/')
          comm=true;
          fstr[i++] = c;
          break;
      case '/':
          if(fstr[i-1]=='*')comm=false;
          if(fstr[i-1]=='/')comm=halftrue;
          fstr[i++] = c;
          break;
      case '=':
      if(fstr[i-1]!='&' && fstr[i-1]!='.' && fstr[i-1]!='+' && fstr[i-1]!='*' &&
         fstr[i-1]!='/' && fstr[i-1]!='|' && fstr[i-1]!='!' && fstr[i-1]!='=' &&
         fstr[i-1]!='<' && fstr[i-1]!='>'&& fstr[i-1]!='~'  && !expr && !cond && 
         comm!=true)
      fstr[i++] = ' ';     
      newline = false;
      fstr[i++] = c;
      if(!expr && !cond && comm!=true)fstr[i++] = ' ';
      break;
      case '\'':newline = false;
      if(fstr[i-1]!='\\')
      {
          switch(expr)
          {    
          case false:expr = halftrue;break;
          case halftrue:expr = false;break;
          default:break;
          }    
      }    
      fstr[i++] = c;
      break;
      case '"':
      newline = false;
      if(fstr[i-1]!='\\')
      {
          switch(expr)
          {    
          case false:expr = true;break;
          case true:expr = false;break;
          default:break;
          }    
      }    
      if(fstr[i-1]!='\\')expr = !expr;
      fstr[i++] = c;
      break;
      case '(':newline = false;cond=true;fstr[i++]=c;break;
      case ')':cond = false;
      fstr[i++] = c;
      break;
      case '{':case '}':if(!expr && !cond && comm!=true)
      {
        if(newline==false);  
        fstr[i++] = '\n';
        if(c=='}')nbtabs--;
        BeginLine(nbtabs, fstr, i);
        i+= 2*nbtabs;
        fstr[i++] = c;
        fstr[i++] = '\n';
        newline=true;
        if(c=='{')nbtabs++;
        BeginLine(nbtabs, fstr, i);
        i+= 2*nbtabs;
      }
      else fstr[i++] = c;
      break;
      case '\n':
      if(newline==true)break;
      if(!expr && !cond && comm!=true)
      {
        comm=false;  
        fstr[i++] = c;
        BeginLine(nbtabs, fstr, i);
        i+= 2*nbtabs;
        newline=true;
      }
      else fstr[i++] = c;
      break;
      case ';':if(!expr && !cond && comm!=true && (i>3 && 
                  (fstr[i-1]!='p' || fstr[i-2]!='m' || fstr[i-3]!='a')) && 
                  (i>4 && (fstr[i-1]!='p' || fstr[i-2]!='s' || fstr[i-3]!='b' ||
                  fstr[i-4]!='n')))
      {
        fstr[i++] = c;
        fstr[i++] = '\n';
        BeginLine(nbtabs, fstr, i);
        i+= 2*nbtabs;
        newline=true;
      }
      else fstr[i++] = c;
      break;
      default:newline = false;fstr[i++] = c;
      break;
    }
  }
  fstr[i-1] = '\0';
  
}
int main(int argc, char *argv[])
{
  FILE* pFile;
  char c, fstr[MAX_FILE] = "\0";
  long int i = 1;
  int nbtabs = 0;
  pFile = fopen(argv[1], "r");
  i=0;
  if(pFile==NULL)
  {
    perror("Indenteur:Erreur lors de l'ouverture du fichier.\nCode d'erreur");
    return 1;
    
  }
  Indent(pFile, nbtabs, fstr, i, c);
  fclose(pFile);
  if(argv[2]!=NULL)pFile = fopen(argv[2], "w+");
  else pFile = fopen("a.txt", "w+");
  if(pFile==NULL)
  {
    perror("Indenteur:Erreur lors de la création du fichier.\nCode d'erreur");
    return 1;
  }
  fputs(fstr, pFile);
  fclose(pFile);
  printf("Indenteur:Pas d'erreur a l'execution\nCode de sortie : 0\n");
  return 0;
}
