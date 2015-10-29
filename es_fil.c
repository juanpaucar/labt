// obtener ASCII codes

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <fcntl.h>

main (int argc, char *argv[]) {
  struct timeval ts, tf;
  unsigned char c[65536];
  int l, i, fd, code[256] = {0};
  int n = 1;

  if (argc != 2) {printf ("USO: ./ascii <fname>\n"); exit (1);}

  fd = open (argv[1], O_RDONLY);
  if (fd < 0) {printf ("OPEN...\n"); exit (1);}

  gettimeofday (&ts, NULL);
  while ((l = read (fd, c, 65536)) != 0) 
    for (i=0; i<l; i++)
      code [c[i]]++;
  gettimeofday (&tf, NULL);
  printf ("%f secs\n", ((tf.tv_sec - ts.tv_sec)*1000000u +
           tf.tv_usec - ts.tv_usec)/ 1.e6);

  close (fd);
  for (i=0; i<256; i++)
    /*printf ("%3d %d\n", i, code[i]);*/
  
  exit (0);
}
