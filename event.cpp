#include "event.h"
#include <array>
#include <vector>

bool eventDescription::isEmpty() {
    return name.empty() && 
           startTime == 0 &&
           numRounds == 0 &&
           roundLength == 0;
}

Round newRound(float start, float length, bool isBreak){
    return {
        .startTime = start,
        .endTime = start + length,
        .roundLength = length,
        .isBreak = isBreak,
    };
}

Event Event::createFromDescription(eventDescription ed){
    const std::string name = ed.name;
    std::vector<Round> rounds{};

    for(int i = 0; i < ed.numRounds; i++) {
        float roundStart = ed.startTime + ed.roundLength * i;
        rounds.push_back(newRound(roundStart, ed.roundLength, false));
    }

    return Event(Member{
        .name = std::move(name),
        .rounds = std::move(rounds),
    });
}

Event Event::createFromRoundVec(std::string name, std::vector<Round> &rounds){
    return Event(Member{
        .name = std::move(name),
        .rounds = std::move(rounds),
    });
}

std::array<Event, 2> Event::splitEventAtTime(const Event& event, float time){
    size_t i = 0;
    for(auto round : event.m.rounds) {
        if(round.endTime > time) break;
        i++;
    }
    std::vector<Round> split_lo(event.m.rounds.begin(), event.m.rounds.begin() + i);
    std::vector<Round> split_hi(event.m.rounds.begin() + i, event.m.rounds.end());

    return {{
        Event::createFromRoundVec(event.m.name, split_lo),
        Event::createFromRoundVec(event.m.name, split_hi)
    }};
}
