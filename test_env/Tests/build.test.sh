g++ -std=c++11 -w ./Functions/*.c cumulative_proximity_test.cpp -o cumulative_proximity_test
./cumulative_proximity_test --list-tests
./cumulative_proximity_test
rm -f cumulative_proximity_test

g++ -std=c++11 -w ./Functions/*.c euclidean_distance_test.cpp -o euclidean_distance_test
./euclidean_distance_test --list-tests
./euclidean_distance_test
rm -f euclidean_distance_test

g++ -std=c++11 -w ./Functions/*.c squared_euclidean_distance_test.cpp -o squared_euclidean_distance_test
./squared_euclidean_distance_test --list-tests
./squared_euclidean_distance_test
rm -f squared_euclidean_distance_test

g++ -std=c++11 -w ./Functions/*.c eccentricity_test.cpp -o eccentricity_test
./eccentricity_test --list-tests
./eccentricity_test
rm -f eccentricity_test

g++ -std=c++11 -w ./Functions/*.c recursive_mean_test.cpp -o recursive_mean_test
./recursive_mean_test --list-tests
./recursive_mean_test
rm -f recursive_mean_test

g++ -std=c++11 -w ./Functions/*.c recursive_unbiased_sigma_test.cpp -o recursive_unbiased_sigma_test
./recursive_unbiased_sigma_test --list-tests
./recursive_unbiased_sigma_test
rm -f recursive_unbiased_sigma_test

g++ -std=c++11 -w ./Functions/*.c recursive_biased_sigma_test.cpp -o recursive_biased_sigma_test
./recursive_biased_sigma_test --list-tests
./recursive_biased_sigma_test
rm -f recursive_biased_sigma_test

g++ -std=c++11 -w ./Functions/*.c recursive_eccentricity_test.cpp -o recursive_eccentricity_test
./recursive_eccentricity_test --list-tests
./recursive_eccentricity_test
rm -f recursive_eccentricity_test