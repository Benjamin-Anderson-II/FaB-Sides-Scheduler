#include "show.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <cstdio>

// Unsure of where to put this... It's here for now....

std::optional<std::string> getToken(std::stringstream& stream){
    std::string token, temp;
    getline(stream, token, ',');
    if(stream.fail()) return std::nullopt;
    getline(stream, temp, ' '); // a little smelly, but idc
    return token;
}

struct eventDescription getDescFromString(std::string line){
    std::string name;
    float startTime;
    int numRounds;
    float roundLength;
    std::string token;
    std::stringstream stream(line);

    if((name = getToken(stream).value_or("")) == "")
        goto badData;
    if((startTime = std::stof(getToken(stream).value_or("0"))) == 0)
        goto badData;
    if((numRounds = std::stoi(getToken(stream).value_or("0"))) == 0)
        goto badData;
    if((roundLength = std::stof(getToken(stream).value_or("0"))) == 0)
        goto badData;
    roundLength /= 60.0;

    return {
        .name = std::move(name),
        .startTime = startTime,
        .numRounds = numRounds,
        .roundLength = roundLength,
    };
badData: return {};
}

std::optional<Show> Show::createFromFile(std::string fileName) {
    float startTime = 1000;
    float endTime = 0;
    std::vector<Event> events;
    std::string line;
    std::ifstream eventStream;
    struct eventDescription currEventDesc = {};

    eventStream.open(fileName);
    if(eventStream.fail()){
        std::cerr << "Whoopsie, that file doesn't exist\n";
        return std::nullopt;
    }

    //Skip Header Line
    getline(eventStream, line);
    while(getline(eventStream, line)){
        currEventDesc = getDescFromString(line);
        if(currEventDesc.isEmpty()){
            std::cerr << "Error extracting file data\n";
            return std::nullopt;
        }
        Event e = Event::createFromDescription(currEventDesc);
        startTime = std::min(startTime, e.getStartTime());
        endTime = std::max(endTime, e.getEndTime());
        events.push_back(e);
    }
    return Show(Member{
        .startTime = startTime,
        .endTime = endTime,
        .events = std::move(events),
    });
}
Show Show::createFromEventVec(const std::vector<Event>& events) {
    Event t = events[0];
    float start = t.getStartTime();
    float end = t.getEndTime();
    int i = 0;
    for(auto e : events){
        start = std::min(start, e.getStartTime());
        end = std::max(end, e.getEndTime());
        i++;
    }
    return Show(Member{
        .startTime = start,
        .endTime = end,
        .events = std::move(events),
    });
}

void Show::sortByStartTime() {
    auto v = &this->m.events;
    std::sort(v->begin(), v->end(), [](Event a, Event b) {
                                        return a.getStartTime() < b.getStartTime();
                                    });
}

void EprintRound(std::string name, Round r){
    std::cout << "|" + name.substr(0, r.roundLength * 5);
}

void Show::print() {
    std::cout << std::endl;
    for(float i = this->m.startTime; i < this->m.endTime; i++)
        printf("|%2d|.5", (int)i);
    printf("|\n");

    std::vector<Event> events = this->m.events;
    for(size_t i = 0; i < events.size(); i++){
        Event event = events[i];
        // Print Leading blocks
        for(float j = 0; j < event.getStartTime() - this->m.startTime; j+=0.5)
            printf("|  ");

        for(int k = 0; k < event.getNumRounds(); k++){
            EprintRound(event.getName(), event[k]);
        }

        float j = event.getEndTime();
        for(; j < this->m.endTime; j+=0.5)
            printf("|  ");
        printf("|\n");
    }
}

