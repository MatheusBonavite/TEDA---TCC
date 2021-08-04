CC = gcc
winDel = del
linuxDel = rm

all: micro_clusters_app

micro_clusters.o: micro_clusters.c
	$(CC) -c micro_clusters.c

micro_cluster_lib.o: self_libs/micro_cluster_lib.c
	$(CC) -c self_libs/micro_cluster_lib.c

sqlite3.o: sqlite/sqlite3.c
	$(CC) -c sqlite/sqlite3.c

micro_clusters_app: micro_clusters.o micro_cluster_lib.o sqlite3.o
	$(CC) -o micro_clusters_app micro_clusters.o micro_cluster_lib.o sqlite3.o

clean:
	$(winDel) -rf *.exe && $(winDel) -rf *.o || true