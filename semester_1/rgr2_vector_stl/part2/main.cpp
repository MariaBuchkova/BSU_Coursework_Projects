#include "time_utility.h"
#include "train.h"
#include <fstream>
#include <iostream>

int main() {

    using namespace time_utility;

    std::random_device rd;
    std::mt19937 generator(rd());

    std::time_t t1 = SetTime(12, 23);
    try {
        t1 = SetTime(12, 60);
    } catch (const std::out_of_range& err) {
        std::cerr << err.what() << std::endl;
    }

    std::time_t t2 = GenerateRandomTime(generator);

    std::cout << "t1: ";
    PrintTime(t1);

    std::cout << "t2: ";
    PrintTime(t2);

    std::cout << "t1 < t2: " << std::boolalpha << (t1 < t2) << '\n';
    std::cout << "t2 < t1: " << std::boolalpha << (t2 < t1) << '\n';

    // my code goes here

    std::ifstream in("input.txt");
    try {
        if (!in) {
            throw "Error! InFile not open";
        }
        if (in.peek() == std::ifstream::traits_type::eof()) {
            throw "Error! InFile is empty";
        }
    } catch (const char* msg) {
        std::cerr << msg;
        return 1;
    }
    std::vector<Train> trains;
    TrainId id;
    TrainType type;
    std::string destination;
    std::size_t hour, minute, travelling_min_time;
    try {
        while (in >> id >> type >> destination >> hour >> minute >> travelling_min_time) {
            std::time_t departure = SetTime(hour, minute);
            std::time_t duration = travelling_min_time * 60;
            Train x(id, type, destination, departure, duration);
            trains.push_back(x);
        }
        in.close();
    } catch (const char* msg) {
        std::cerr << msg;
        return 1;
    }

    size_t size = trains.size();
    
    if (trains.empty()) {
        std::cerr << "no data to process\n";
        return 1;
    }

    std::cout << "\nTrains sorted by ascending train departure time:\n";
    std::vector<Train> vector(trains);
    std::sort(vector.begin(), vector.end());
    for (size_t i = 0; i < size; ++i) {
        std::cout << trains[i];
    }

    std::cout<<"\nTrains in the time range 8.00 - 13.00:\n";
    std::time_t start_time = SetTime(8, 0);
    std::time_t end_time = SetTime(13, 0);
    bool found_in_range = false;
    for (const auto& train : trains) {
        if (train.getDispatchTime() >= start_time && train.getDispatchTime() <= end_time) {
            std::cout << train;
            found_in_range = true;
        }
    }

    if (!found_in_range) {
        std::cout << "No trains were found in the specified range.\n";
    }

    const std::string target_destination = "Minsk";
    std::cout << "\nTrains going to " << target_destination << ":\n";
    bool found_to_destination = false;
    for (const auto& train : trains) {
        if (train.getDestination() == target_destination) {
            std::cout << train;
            found_to_destination = true;
        }
    }

    if (!found_to_destination) {
        std::cout << "No trains to " << target_destination << "were found.";
    }

    TrainType target_type = TrainType::PASSENGER;
    std::cout << '\n' << target_type << " trains going to " << target_destination  << ":\n";

    bool found_type_to_destination = false;
    for (const auto& train : trains) {
        if (train.getDestination() == target_destination && train.getType() == target_type) {
            std::cout << train;
            found_type_to_destination = true;
        }
    }

    if (!found_type_to_destination) {
        std::cout << "No " << target_type << " trains to " << target_destination << " were found.\n";
    }


    std::time_t min_travel_time = trains[0].getTravellingTime();
    const Train* fastest_train = &trains[0];

    for (size_t i = 0; i < trains.size(); ++i) {
        if (trains[i].getDestination() == target_destination &&
            trains[i].getTravellingTime() < min_travel_time) {
            min_travel_time = trains[i].getTravellingTime();
            fastest_train = &trains[i];
        }
    }

    if (fastest_train != nullptr) {
        std::cout << "\nFastest train going to " << target_destination << " found :\n "
                  << *fastest_train << "\n ";
        std::cout << "Travel time: " << (min_travel_time / 60) << " minutes";
    } else {
        std::cout << "\nNo trains to " << target_destination << " found.\n";
    }







    return EXIT_SUCCESS;
}
