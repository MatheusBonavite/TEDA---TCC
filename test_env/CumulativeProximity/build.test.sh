g++ -std=c++11 CumulativeProximity.test.cpp -o CumulativeProximity
valgrind --log-file="euclidean-report" --leak-check="full" ./CumulativeProximity