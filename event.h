#ifndef FAB_EVENT_H
#define FAB_EVENT_H

#include <string>
#include <vector>
#include <array>

struct Round {
    float startTime;    // What time the round is supposed to start
    float endTime;
    float roundLength;  // Length of the round (either .5 or 1 hr)
    bool  isBreak;
};

struct eventDescription {
    std::string name;
    float startTime;
    int numRounds;
    float roundLength;
    bool isEmpty();
};

class Event {
    public:
        struct Member {
            std::string name;
            std::vector<Round> rounds;
        } m;
        explicit Event(Member m) : m(std::move(m)) {}

        static Event createFromDescription(eventDescription);
        static Event createFromRoundVec(std::string, std::vector<Round>&);

        static std::array<Event, 2> splitEventAtTime(const Event&, float);

        // Getters
        Round &operator[](unsigned int i){return this->m.rounds[i];}
        Round firstRound() {return this->m.rounds.front();}
        Round lastRound()  {return this->m.rounds.back();}
        float startTime() {return this->m.rounds.front().startTime;}
        float endTime()   {return this->m.rounds.back().endTime;}
};

#endif
