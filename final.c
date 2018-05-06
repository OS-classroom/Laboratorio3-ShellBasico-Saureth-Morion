#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <time.h>
#include "morion.h"
#include "parser.h"


void ImprimirError(char* err);
int sai(char *str);

int main(){
    char str[200];    
    char ** items;
    int num, background;
    int TAM = 5000;
    char expresion[TAM];
    do{
        printf("Comando > ");
        scanf("%s", str); 
        fgets (expresion, TAM, stdin);      
        num = separaItems (expresion, &items, &background);  
	printf ("%d", num);
        int ejecutar = 1;

        if (background==1){
            ejecutar = 0;
            int a = fork ();
            if (a == 0) 
            {
                ejecutar = 1;
                printf("[Ejecutando comando en segundo plano]");
            }
        }
        if (ejecutar == 1)
        {
	    if(strcmp(str,"myps")== 0)
            {
               execl("./mygetdents", "/proc/",NULL);
               printf("\n");
            }
            else if(strcmp(str,"mypwd")== 0)
            {
                if(num==0)
                {
                    ImprimirCarpeta();
                    printf("\n");
                }else{
                    ImprimirError(str);
                }
            }else if(strcmp(str,"micp")== 0)
            {
                if(num==2)
                {
                    char origen[1024];
                    strcpy(origen, items[0]);
                    char destino[1024];
                    strcpy(destino, items[1]);
                    MiCp(origen, destino);

                    printf("Archivo copiado\nOrigen: %s\n",origen);
                    printf("Destino: %s\n",destino);
                }else{
                    ImprimirError(str);
                }
            }else if(strcmp(str,"myecho")== 0)
            {
                if(num>0)
                {
                    char mensaje[1024] = "";
                    for (int q = 0; q<num; q++){
                        strcat(mensaje, items[q]);
                        strcat(mensaje, " ");
                    }
                    MyEcho(mensaje);
                    printf("\n");
                }else{
                    ImprimirError(str);
                }
            }else if(strcmp(str,"myclr")== 0)
            {
                if(num==0)
                {
                    MyClr();
                }else{
                    ImprimirError(str);
                }
            }else if(strcmp(str,"mykill")== 0)
            {
                if(num==2)
                {
                    int a1 = sai(items[0]);
                    int a2 = sai(items[1]);
                    
                    kill_p(a1,a2);
                }else{
                    ImprimirError(str);
                }
            }else if(strcmp(str,"mytime")== 0)
            {
                if(num==0)
                {
                    MyTime();
                }else{
                    ImprimirError(str);
                }
            }else if(strcmp(str,"mygrep")== 0)
            {
                if(num==2)
                {
                    LeerTexto(items[0],items[1]);
                    printf("\n");
        	    printf("Comando > ");
                }else{
                    ImprimirError(str);
                }
            }else if(strcmp(str,"psinfo")== 0)
            {
                if(num==1)
                {
		    items[1]= items[0];
	  	    if(fork()==0){
			execv("./psinfo", items);
		    }                    
                    printf("\n");
                }else{
                    ImprimirError(str);
                }
            }

        }

        liberaItems (items);
        // Si Resulta que la ejecucion era en background y este era el hijo, se cierra
        if(background == 1 && ejecutar == 1)
            return 0;
    }

    while(strcmp(str,"myexit")!= 0);

    return 0;
}

void ImprimirError(char* err)
{
    printf("ERROR, uso no valido del comando, te recomendamos usar la ayuda: help %s\n",err);
}

int sai(char *str)
{
  int           result;
  int           puiss;

  result = 0;
  puiss = 1;
  while (('-' == (*str)) || ((*str) == '+'))
    {
      if (*str == '-')
        puiss = puiss * -1;
      str++;
    }
  while ((*str >= '0') && (*str <= '9'))
    {
      result = (result * 10) + ((*str) - '0');
      str++;
    }
  return (result * puiss);
}
