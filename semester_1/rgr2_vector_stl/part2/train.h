#pragma once
#include <iostream> 
#include <string>
#include <iomanip>
#include "time_utility.h"

using TrainId = size_t;
using namespace time_utility;


enum class TrainType { 
    PASSENGER, FREIGHT, HIGH_SPEED, SUBWAY, SPECIALIZED
};

std::istream& operator>>(std::istream& is, TrainType& type);
std::ostream& operator<<(std::ostream& out, TrainType type);

class Train {
private:
    TrainId id_;
    TrainType type_;
    std::string destination_;
    std::time_t dispatch_time_;
    std::time_t travelling_time_;

public:
    Train(TrainId id, TrainType type, const std::string& destination, std::time_t dispatch_time,
          std::time_t travelling_time)
        : id_(id),
          type_(type),
          destination_(destination),
          dispatch_time_(dispatch_time),
          travelling_time_(travelling_time) {
    }
    TrainId getId() const {
        return id_;
    }
    TrainType getType() const {
        return type_;
    }
    std::string getDestination() const {
        return destination_;
    }
    std::time_t getDispatchTime() const {
        return dispatch_time_;
    }
    std::time_t getTravellingTime() const {
        return travelling_time_;
    }
    bool operator<(const Train& other) const {
        return dispatch_time_ < other.dispatch_time_;
    }
    friend std::ostream& operator<<(std::ostream& out, const Train& train);
};


inline std::ostream& operator<<(std::ostream& out, const Train& train) {
    out << '\n' << std::left << std::setw(17) << "Train id:" << train.id_ << '\n'
        << std::setw(17) << "Type:" << train.type_ << '\n'
        << std::setw(17) << "Destination:" << train.destination_ << '\n'
        << std::setw(17) << "Dispatch time:";
    PrintTime(train.dispatch_time_);
    out << std::setw(17) << "Travelling time:" << (train.travelling_time_ / 60) << " min\n";
    return out;
}


inline std::istream& operator>>(std::istream& in, TrainType& type) {
    std::string str;
    if (in >> str) {
        if (str == "PASSENGER")
            type = TrainType::PASSENGER;
        else if (str == "FREIGHT")
            type = TrainType::FREIGHT;
        else if (str == "HIGH_SPEED")
            type = TrainType::HIGH_SPEED;
        else if (str == "SUBWAY")
            type = TrainType::SUBWAY;
        else if (str == "SPECIALIZED")
            type = TrainType::SPECIALIZED;
        else
            throw "Error! Invalid train type.";
    }
    return in;
}
inline std::ostream& operator<<(std::ostream& out, TrainType type) {
    switch (type) {
        case TrainType::PASSENGER:
            return out << "PASSENGER";
        case TrainType::FREIGHT:
            return out << "FREIGHT";
        case TrainType::HIGH_SPEED:
            return out << "HIGH_SPEED";
        case TrainType::SUBWAY:
            return out << "SUBWAY";
        case TrainType::SPECIALIZED:
            return out << "SPECIALIZED";
        default:
            return out << "UNKNOWN";
    }
}


