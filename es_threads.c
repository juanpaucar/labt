// Calcula la frecuencia de cada uno de los 256 caracteres ASCII
// Usa threads con mutex. Los threads usan contadores parciales locales
// El archivo es particionado en T segmentos (T - numero de threads)

#include <pthread.h>
#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

typedef struct args {
  int fd;		// descriptor del archivo
  int ini;		// inicio del segmento de archivo 
  int fin;		// fin (+1) del segmento
} arg;

pthread_mutex_t mx;
int codeF[256] = {0};

void codes (arg *args) {
  int i, j, l, code[256] = {0};
  unsigned char c[65536];

// ubicarse al inicio del segmento
  if (lseek (args->fd, args->ini, SEEK_SET)<0) {printf ("LSEEK...\n"); exit(1);}

// procesar 64k a la vez
  for (i = args->ini + 65536; i < args->fin; i+=65536) {
    l = read (args->fd, c, 65536);
    for (j=0; j<l; j++)
      code[c[j]]++;
  }

// procesar los ultimos bytes del segmento
  l = read (args->fd, c, args->fin - i + 65536);
  for (j=0; j<l; j++)
    code[c[j]]++;

// Actualizar contadores globales con los resultados parciales de este thread
  pthread_mutex_lock(&mx);
  for (i=0; i<256; i++)
    codeF[i] += code[i];
  pthread_mutex_unlock(&mx);
}

main (int argc, char *argv[]) {
  struct timeval ts, tf;
  int i, j, T, N, cl, fr;
  pthread_t *th;
  arg *args;
  struct stat stats;

  if (argc != 3) {printf ("USO: %s <fname> <Ths>\n", argv[0]); exit (1);}

// obtener tamanio del archivo
  stat (argv[1], &stats);
  N = stats.st_size;

  T = atoi(argv[2]); 	// numero de threads (T)

  th = malloc (T * sizeof (pthread_t)); 
  args = malloc (T * sizeof (arg));
  if (th == NULL||args == NULL) { printf ("Memoria\n"); exit (1);}
      
  (void) pthread_mutex_init(&mx, 0);

  cl = (int)ceil((float)N/(float)T);
  fr = (int)floor((float)N/(float)T);

// Asignar sementos de los archivos a los T threads
  for (i=0;i<N%T;i++){
    args[i].fd = open (argv[1], O_RDONLY);
    if (args[i].fd < 0) {printf ("OPEN...\n"); exit (1);}
    args[i].ini = i*cl;
    args[i].fin = (i+1)*cl;
  }
  for (i=N%T;i<T;i++){
    args[i].fd = open (argv[1], O_RDONLY);
    if (args[i].fd < 0) {printf ("OPEN...\n"); exit (1);}
    args[i].ini =(N%T)*cl + (i-(N%T))*fr;
    args[i].fin =(N%T)*cl + (i-(N%T)+1)*fr;
  }

  gettimeofday (&ts, NULL);
  for (i=0; i<T; i++)
    pthread_create (&th[i], NULL, (void *) codes, &args[i]);

// esperar que todos los threads finalicen  
  for (i=0; i<T; i++)
    if (pthread_join (th[i], NULL)) {printf ("PJOIN (%d)\n", i); exit (1);};

  gettimeofday (&tf, NULL);
  printf ("LOCAL: %f secs\n", ((tf.tv_sec - ts.tv_sec)*1000000u +
          tf.tv_usec - ts.tv_usec)/ 1.e6);

  for (i=0; i<256; i++)
    /*printf ("%3d %d\n", i, codeF[i]);*/

  exit (0);
}
