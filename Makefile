SRCS=cpu_fil.c cpu_col.c cpu_threads.c cpu_mutex.c cpu_local.c es_fil.c es_threads.c
OBJS=cpu_fil.o cpu_col.o cpu_threads.o cpu_mutex.o cpu_local.o es_fil.o es_threads.o
PROGS=cpu_fil cpu_col cpu_threads cpu_mutex cpu_local es_fil es_threads

all:	${PROGS}

cpu_fil:	cpu_fil.c
	cc -o cpu_fil cpu_fil.c

cpu_col:	cpu_col.c
	cc -o cpu_col cpu_col.c

cpu_threads:	cpu_threads.c
	cc -o cpu_threads cpu_threads.c -lpthread -lm

cpu_mutex:	cpu_mutex.c
	cc -o cpu_mutex cpu_mutex.c -lpthread -lm

cpu_local:	cpu_local.c
	cc -o cpu_local cpu_local.c -lpthread -lm

es_fil:	es_fil.c
	cc -o es_fil es_fil.c

es_threads:	es_threads.c
	cc -o es_threads es_threads.c -lpthread -lm

clean:
	rm -f ${PROGS}
