
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define nbin 31


/* fonctions d ecriture*/

void Ecriture1(long double average,long double variance,long double table[2][nbin],char l[30]) {	
int j;
char str[30];
		
	FILE *fichier;
sprintf( str, "histo%s", l );
    
	fichier=fopen(str,"w+");
fprintf(fichier,"#average and variance :%.12Lf %.12Lf  \n",average,variance);
	for (j=0;j<nbin;j=j++){

long double bin=table[0][j];
long double occurance=table[1][j];
	fprintf(fichier,"%.12Lf %.12Lf  \n",bin,occurance);
	}

	fclose(fichier);
}


/*fonction lecture des donnees*/

void recupdata(int nbc,long double truc[nbc*sizeof(long double)],char stock[30]){

char str[30];	
long double grap;

		
	FILE *fichier;
	int i;
	
 sprintf( str, "%s", stock);
    fichier = fopen(str,"r");

 if (graphene != NULL)
    {
	

	for (i=0;i<(nbc);i=i++)
{

        fscanf(fichier," %Lf ",&grap); 

truc[i]=grap;



 }
        	
    }
	fclose(fichier);
}




/*programme principal*/

int main(int argc, char* argv[])  //demande un fichier en argumant
{

int nbc ;
char str[30];
FILE *f;
sprintf(str, "wc -l %s > tmp", argv[1]);
system(str);
f = fopen("tmp","rw" );
fscanf(f,"%d",&nbc); 
system("rm -f tmp");

//bash plus efficace pour obtenir le nombre d'elements dans le fichier

long double* data =NULL;
 data = malloc(nbc*sizeof(long double));
    if (data == NULL) // Si l allocation a echoue
    {
        exit(0); // On arrete immediatement le programme
    }



recupdata(nbc,data,argv[1]);


int i;
long double a = data[0];
long double b = data[0];

for(i=0;i<nbc;i++)
{if (data[i]>=a){ a=data[i];} 
if (data[i]<=b) { b=data[i];}
}

// recuperation des bornes des donnees

printf ("\n %s %Lf %Lf \n",argv[1],a,b);

long double bin= (a-b)/(nbin-1);

long double table[2][nbin];

int storage =0;

for(i=0;i<nbin;i++)
{table[0][i]=0;table[1][i]=0;
}

for(i=0;i<nbin;i++)
{table[0][i]=b + bin*i;
}
for(i=0;i<nbc;i++)
{
storage=floor(((data[i])-b)/bin);
table[1][storage]++; //incremente le bon bin
}

for(i=0;i<nbin;i++)
{table[1][i]=table[1][i]/nbc/(a-b)*nbin;
}

long double average =0;
long double variance =0;

for(i=0;i<nbc;i++)
{average= average+(data[i]);
variance= variance + (data[i]*data[i]);
}

average= average/(nbc);

variance= sqrt(variance/(nbc)-average*average);

long double test=0;

for(i=0;i<nbin;i++)
{test=table[1][i]+test;}

printf ("\n %Lf %Lf %Lf  \n",a,b,test*(a-b)/nbin);
//si le dernier vaut 1 on a bien normalise

Ecriture1(average,variance,table,argv[1]);


free (data);

return 0;
}











