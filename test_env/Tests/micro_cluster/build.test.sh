g++ -std=c++11 -w micro_cluster.c micro_cluster_test.cpp -o micro_cluster_test
./micro_cluster_test --list-tests
./micro_cluster_test
rm -f micro_cluster_test