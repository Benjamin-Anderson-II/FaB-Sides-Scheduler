#include "main.h"
#include "utils.h"

int main (void) {
    std::vector<Event> events;
    std::vector<Judge> judges;

    // initialize variables
    initEvents(events);
    //initJudges(&judges);

    printEvents(events);

    return 0;
}

void initEvents(std::vector<Event> &events){
    readEventsFromFile(events);
    sortEvents(events);
}

void initJudges(std::vector<Judge> *judges){
    //
}

