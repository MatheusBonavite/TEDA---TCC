g++ -std=c++11 OfflineEccentricity.test.cpp -o OfflineEccentricity
valgrind --log-file="offline-eccentricity-report" --leak-check="full" ./OfflineEccentricity