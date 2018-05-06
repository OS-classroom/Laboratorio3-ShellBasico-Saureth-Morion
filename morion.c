//#define _POSIX_SOURCE
#include <unistd.h>
//#undef _POSIX_SOURCE
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <signal.h>

void ImprimirCarpeta();
int MiCp(const char *from, const char *to);
void MyEcho(const char *msj);
void MyClr();
void MyTime();
void LeerTexto(char* cadena, char* ruta);
void kill_p(int s, int ipid);
/*
int main(void)
{
    
    Ejemplos  de uso 

    MyClr();

    ImprimirCarpeta();

    MyEcho("\nHola\n");

    MyTime();

    LeerTexto("/home/Estudiantes/adrian.martinez/Desktop/SO/LabSistemasOperativos/Lab3/borrrar.txt", "no");
    
    kill_p(7547);
***********************************************************
    char origen[1024];
    strcpy(origen, cwd);
    strcat(origen, "/morion.c");
    char destino[1024];
    strcpy(destino, cwd);
    strcat(destino, "/caso.c");
    micp(origen, destino);
***********************************************************
    
    

    return 0;
}*/

/////////////////////////////////////////////////////////////   Imprimir carpeta
void ImprimirCarpeta(){
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL)
        fprintf(stdout, "%s", cwd);
    else
        perror("getcwd() error");
}


/////////////////////////////////////////////////////////////   Copiar Archivos
int MiCp(const char *from, const char *to)
{
    int fd_to, fd_from;
    char buf[4096];
    ssize_t nread;
    int saved_errno;

    fd_from = open(from, O_RDONLY);
    if (fd_from < 0)
        return -1;

    fd_to = open(to, O_WRONLY | O_CREAT | O_EXCL, 0666);
    if (fd_to < 0)
        goto out_error;

    while (nread = read(fd_from, buf, sizeof buf), nread > 0)
    {
        char *out_ptr = buf;
        ssize_t nwritten;

        do {
            nwritten = write(fd_to, out_ptr, nread);

            if (nwritten >= 0)
            {
                nread -= nwritten;
                out_ptr += nwritten;
            }
            else if (errno != EINTR)
            {
                goto out_error;
            }
        } while (nread > 0);
    }

    if (nread == 0)
    {
        if (close(fd_to) < 0)
        {
            fd_to = -1;
            goto out_error;
        }
        close(fd_from);

        /* Success! */
        return 0;
    }

  out_error:
    saved_errno = errno;

    close(fd_from);
    if (fd_to >= 0)
        close(fd_to);

    errno = saved_errno;
    return -1;
}


/////////////////////////////////////////////////////////////   Imprimir mensaje en consola
void MyEcho(const char *msj)
{
    fprintf(stdout, "%s",msj);
}

/////////////////////////////////////////////////////////////   Limpiar consola
void MyClr()
{
  const char *CLEAR_SCREEN_ANSI = "\e[1;1H\e[2J";
  write(STDOUT_FILENO, CLEAR_SCREEN_ANSI, 12);
}

/////////////////////////////////////////////////////////////   Tiempo actual
void MyTime(){
    time_t rawtime;
    struct tm * timeinfo;
  
    time ( &rawtime );
    timeinfo = localtime ( &rawtime );
    printf ( "%s", asctime (timeinfo) );
  
}

/////////////////////////////////////////////////////////////   Leer txt linea por línea
void LeerTexto(char* cadena, char* ruta)
{
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

   fp = fopen(ruta, "r");
    if (fp == NULL){
        printf("Error:\n");
    }
        

   while ((read = getline(&line, &len, fp)) != -1) {

        if(strstr(line, cadena) != NULL) {
            printf("%s", line);
        }
        
    }

   free(line);
}

/////////////////////////////////////////////////////////////   Kill process

void kill_p(int s, int ipid)
{
    pid_t pid=ipid;
    int a = kill(pid,s);
    
    printf("La señal %d fue enviada al proceso: %d",a,ipid);

    
}
