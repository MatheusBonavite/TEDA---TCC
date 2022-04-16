g++ -std=c++11 CumulativeProximity.test.cpp -o CumulativeProximity
valgrind --log-file="cumulative-report" --leak-check="full" ./CumulativeProximity