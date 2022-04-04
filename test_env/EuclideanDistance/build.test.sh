g++ -std=c++11 EuclideanDistance.test.cpp -o EuclideanTest
valgrind --log-file="euclidean-report" --leak-check="full" ./EuclideanTest