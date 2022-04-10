g++ -std=c++11 OnlineEccentricity.test.cpp -o OnlineEccentricity
valgrind --log-file="online-eccentricity-report" --leak-check="full" --track-origins="yes" --leak-check="full" --show-leak-kinds="all" ./OnlineEccentricity