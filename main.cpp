#include <cstdio>
#include <cstring>
#include <vector>

/****NOTES****/
// Time is hourly from 0 to 23 
//  - It is assumed that events to not run past midnight.
//  - Ex: 4:30pm is represented as 16.5
//
// NOT IMPLEMENTED, BUT CONSIDERED:
//  - Giving all events a 30 min buffer at the end.
/*************/

// Magic Numbers
#define MAXROUNDS 64

// Structures

/* Judge Structures */
typedef struct {
    float startTime;      // Beginning of the Judge's Shift
    float endTime;        // End of the Judge's Shift
    bool breakHalf;     // Whether they have their 0.5 hr break still (1=yes)
    bool breakFull;     // Whether they have their 1.0 hr break still (1=yes)
} Judge;

typedef struct {
    float startTime;      // What time the round is supposed to start
    float roundLength;  // Length of the round (either .5 or 1 hr)
} Round;

typedef struct {
    Round rounds[MAXROUNDS];    // typically there are only 4-5 rounds,
                                //   extreme padding is for futureproofing
                                //   without the overhead of a std::vector
} Event;

// Function Prototypes
void initEvents(std::vector<Event> *events);
void initJudges(std::vector<Judge> *judges);
void printEvents(std::vector<Event> events);

// Globals
float startAll;
float endAll;

int main (void) {
    std::vector<Event> events;
    std::vector<Judge> judges;

    // initialize variables
    initEvents(&events);
    //initJudges(&judges);

    printEvents(events);

    return 0;
}

void fillEvents(std::vector<Event> *e);
void initEvents(std::vector<Event> *events){
    // Get number of Events
    int numEvents = 12;

    // create default Events
    for(int i = 0; i < numEvents; i++){
        events->push_back({});
        memset(&((*events)[i]), -1., sizeof(Event)); // set start time of all rounds to -1
    }

    /* TEMPORARY */
    fillEvents(events);

    // calculate this
    startAll = 9;
    endAll = 21.5;
}
void fillEvents(std::vector<Event> *e){
    // CC
    (*e)[0].rounds[0].startTime = 9;
    (*e)[0].rounds[0].roundLength = 0.5;
    (*e)[0].rounds[1].startTime = 9.5;
    (*e)[0].rounds[1].roundLength = 0.5;
    (*e)[0].rounds[2].startTime = 10;
    (*e)[0].rounds[2].roundLength = 0.5;
    (*e)[0].rounds[3].startTime = 10.5;
    (*e)[0].rounds[3].roundLength = 0.5;
    (*e)[0].rounds[4].startTime = 11;
    (*e)[0].rounds[4].roundLength = 0.5;
    (*e)[0].rounds[5].startTime = 11.5;
    (*e)[0].rounds[5].roundLength = 0.5;
    (*e)[0].rounds[6].startTime = 12;
    (*e)[0].rounds[6].roundLength = 0.5;
    (*e)[0].rounds[7].startTime = 12.5;
    (*e)[0].rounds[7].roundLength = 0.5;
    (*e)[0].rounds[8].startTime = 13;
    (*e)[0].rounds[8].roundLength = 0.5;

    //Draft
    (*e)[1].rounds[0].startTime = 9;
    (*e)[1].rounds[0].roundLength = 0.5;
    (*e)[1].rounds[1].startTime = 9.5;
    (*e)[1].rounds[1].roundLength = 0.5;
    (*e)[1].rounds[2].startTime = 10;
    (*e)[1].rounds[2].roundLength = 0.5;
    (*e)[1].rounds[3].startTime = 10.5;
    (*e)[1].rounds[3].roundLength = 0.5;
    (*e)[1].rounds[4].startTime = 11;
    (*e)[1].rounds[4].roundLength = 0.5;
    (*e)[1].rounds[5].startTime = 11.5;
    (*e)[1].rounds[5].roundLength = 0.5;
    (*e)[1].rounds[6].startTime = 12;
    (*e)[1].rounds[6].roundLength = 0.5;
    (*e)[1].rounds[7].startTime = 12.5;
    (*e)[1].rounds[7].roundLength = 0.5;
    (*e)[1].rounds[8].startTime = 13;
    (*e)[1].rounds[8].roundLength = 0.5;
    (*e)[1].rounds[9].startTime = 13.5;
    (*e)[1].rounds[9].roundLength = 0.5;
    (*e)[1].rounds[10].startTime = 14;
    (*e)[1].rounds[10].roundLength = 0.5;
    (*e)[1].rounds[11].startTime = 14.5;
    (*e)[1].rounds[11].roundLength = 0.5;
    (*e)[1].rounds[12].startTime = 15;
    (*e)[1].rounds[12].roundLength = 0.5;
    (*e)[1].rounds[13].startTime = 15.5;
    (*e)[1].rounds[13].roundLength = 0.5;
    (*e)[1].rounds[14].startTime = 16;
    (*e)[1].rounds[14].roundLength = 0.5;
    (*e)[1].rounds[15].startTime = 16.5;
    (*e)[1].rounds[15].roundLength = 0.5;
    (*e)[1].rounds[16].startTime = 17;
    (*e)[1].rounds[16].roundLength = 0.5;
    (*e)[1].rounds[17].startTime = 17.5;
    (*e)[1].rounds[17].roundLength = 0.5;
    (*e)[1].rounds[18].startTime = 18;
    (*e)[1].rounds[18].roundLength = 0.5;
    (*e)[1].rounds[19].startTime = 18.5;
    (*e)[1].rounds[19].roundLength = 0.5;
    (*e)[1].rounds[20].startTime = 19;
    (*e)[1].rounds[20].roundLength = 0.5;
    (*e)[1].rounds[21].startTime = 19.5;
    (*e)[1].rounds[21].roundLength = 0.5;
    (*e)[1].rounds[22].startTime = 20;
    (*e)[1].rounds[22].roundLength = 0.5;
    (*e)[1].rounds[23].startTime = 20.5;
    (*e)[1].rounds[23].roundLength = 0.5;
    (*e)[1].rounds[24].startTime = 21;
    (*e)[1].rounds[24].roundLength = 0.5;

    // Seal 1
    (*e)[2].rounds[0].startTime = 10;
    (*e)[2].rounds[0].roundLength = 0.5;
    (*e)[2].rounds[1].startTime = 10.5;
    (*e)[2].rounds[1].roundLength = 0.5;
    (*e)[2].rounds[2].startTime = 11;
    (*e)[2].rounds[2].roundLength = 0.5;
    (*e)[2].rounds[3].startTime = 11.5;
    (*e)[2].rounds[3].roundLength = 0.5;
    (*e)[2].rounds[4].startTime = 12;
    (*e)[2].rounds[4].roundLength = 0.5;
    (*e)[2].rounds[5].startTime = 12.5;
    (*e)[2].rounds[5].roundLength = 0.5;
    (*e)[2].rounds[6].startTime = 13;
    (*e)[2].rounds[6].roundLength = 0.5;

    // Common
    (*e)[3].rounds[0].startTime = 11;
    (*e)[3].rounds[0].roundLength = 0.5;
    (*e)[3].rounds[1].startTime = 11.5;
    (*e)[3].rounds[1].roundLength = 0.5;
    (*e)[3].rounds[2].startTime = 12;
    (*e)[3].rounds[2].roundLength = 0.5;
    (*e)[3].rounds[3].startTime = 12.5;
    (*e)[3].rounds[3].roundLength = 0.5;
    (*e)[3].rounds[4].startTime = 13;
    (*e)[3].rounds[4].roundLength = 0.5;
    (*e)[3].rounds[5].startTime = 13.5;
    (*e)[3].rounds[5].roundLength = 0.5;

    // Blitz
    (*e)[4].rounds[0].startTime = 12;
    (*e)[4].rounds[0].roundLength = 0.5;
    (*e)[4].rounds[1].startTime = 12.5;
    (*e)[4].rounds[1].roundLength = 0.5;
    (*e)[4].rounds[2].startTime = 13;
    (*e)[4].rounds[2].roundLength = 0.5;
    (*e)[4].rounds[3].startTime = 13.5;
    (*e)[4].rounds[3].roundLength = 0.5;
    (*e)[4].rounds[4].startTime = 14;
    (*e)[4].rounds[4].roundLength = 0.5;
    (*e)[4].rounds[5].startTime = 14.5;
    (*e)[4].rounds[5].roundLength = 0.5;

    // Ar CC
    (*e)[5].rounds[0].startTime = 13;
    (*e)[5].rounds[0].roundLength = 0.5;
    (*e)[5].rounds[1].startTime = 13.5;
    (*e)[5].rounds[1].roundLength = 0.5;
    (*e)[5].rounds[2].startTime = 14;
    (*e)[5].rounds[2].roundLength = 0.5;
    (*e)[5].rounds[3].startTime = 14.5;
    (*e)[5].rounds[3].roundLength = 0.5;
    (*e)[5].rounds[4].startTime = 15;
    (*e)[5].rounds[4].roundLength = 0.5;
    (*e)[5].rounds[5].startTime = 15.5;
    (*e)[5].rounds[5].roundLength = 0.5;
    (*e)[5].rounds[6].startTime = 16;
    (*e)[5].rounds[6].roundLength = 0.5;
    (*e)[5].rounds[7].startTime = 16.5;
    (*e)[5].rounds[7].roundLength = 0.5;
    (*e)[5].rounds[8].startTime = 17;
    (*e)[5].rounds[8].roundLength = 0.5;

    // Ar Seal
    (*e)[6].rounds[0].startTime = 14;
    (*e)[6].rounds[0].roundLength = 0.5;
    (*e)[6].rounds[1].startTime = 14.5;
    (*e)[6].rounds[1].roundLength = 0.5;
    (*e)[6].rounds[2].startTime = 15;
    (*e)[6].rounds[2].roundLength = 0.5;
    (*e)[6].rounds[3].startTime = 15.5;
    (*e)[6].rounds[3].roundLength = 0.5;
    (*e)[6].rounds[4].startTime = 16;
    (*e)[6].rounds[4].roundLength = 0.5;
    (*e)[6].rounds[5].startTime = 16.5;
    (*e)[6].rounds[5].roundLength = 0.5;
    (*e)[6].rounds[6].startTime = 17;
    (*e)[6].rounds[6].roundLength = 0.5;

    // Ar Com
    (*e)[7].rounds[0].startTime = 15;
    (*e)[7].rounds[0].roundLength = 0.5;
    (*e)[7].rounds[1].startTime = 15.5;
    (*e)[7].rounds[1].roundLength = 0.5;
    (*e)[7].rounds[2].startTime = 16;
    (*e)[7].rounds[2].roundLength = 0.5;
    (*e)[7].rounds[3].startTime = 16.5;
    (*e)[7].rounds[3].roundLength = 0.5;
    (*e)[7].rounds[4].startTime = 17;
    (*e)[7].rounds[4].roundLength = 0.5;
    (*e)[7].rounds[5].startTime = 17.5;
    (*e)[7].rounds[5].roundLength = 0.5;

    // Ar Blitz
    (*e)[8].rounds[0].startTime = 16;
    (*e)[8].rounds[0].roundLength = 0.5;
    (*e)[8].rounds[1].startTime = 16.5;
    (*e)[8].rounds[1].roundLength = 0.5;
    (*e)[8].rounds[2].startTime = 17;
    (*e)[8].rounds[2].roundLength = 0.5;
    (*e)[8].rounds[3].startTime = 17.5;
    (*e)[8].rounds[3].roundLength = 0.5;
    (*e)[8].rounds[4].startTime = 18;
    (*e)[8].rounds[4].roundLength = 0.5;
    (*e)[8].rounds[5].startTime = 18.5;
    (*e)[8].rounds[5].roundLength = 0.5;

    // Prom CC
    (*e)[9].rounds[0].startTime = 17;
    (*e)[9].rounds[0].roundLength = 0.5;
    (*e)[9].rounds[1].startTime = 17.5;
    (*e)[9].rounds[1].roundLength = 0.5;
    (*e)[9].rounds[2].startTime = 18;
    (*e)[9].rounds[2].roundLength = 0.5;
    (*e)[9].rounds[3].startTime = 18.5;
    (*e)[9].rounds[3].roundLength = 0.5;
    (*e)[9].rounds[4].startTime = 19;
    (*e)[9].rounds[4].roundLength = 0.5;
    (*e)[9].rounds[5].startTime = 19.5;
    (*e)[9].rounds[5].roundLength = 0.5;
    (*e)[9].rounds[6].startTime = 20;
    (*e)[9].rounds[6].roundLength = 0.5;
    (*e)[9].rounds[7].startTime = 20.5;
    (*e)[9].rounds[7].roundLength = 0.5;
    (*e)[9].rounds[8].startTime = 21;
    (*e)[9].rounds[8].roundLength = 0.5;

    // Seal 2
    (*e)[10].rounds[0].startTime = 18;
    (*e)[10].rounds[0].roundLength = 0.5;
    (*e)[10].rounds[1].startTime = 18.5;
    (*e)[10].rounds[1].roundLength = 0.5;
    (*e)[10].rounds[2].startTime = 19;
    (*e)[10].rounds[2].roundLength = 0.5;
    (*e)[10].rounds[3].startTime = 19.5;
    (*e)[10].rounds[3].roundLength = 0.5;
    (*e)[10].rounds[4].startTime = 20;
    (*e)[10].rounds[4].roundLength = 0.5;
    (*e)[10].rounds[5].startTime = 20.5;
    (*e)[10].rounds[5].roundLength = 0.5;
    (*e)[10].rounds[6].startTime = 21;
    (*e)[10].rounds[6].roundLength = 0.5;
}

void initJudges(std::vector<Judge> *judges){
    //
}

void printEvents(std::vector<Event> events){
    for(float i = startAll; i < endAll; i++)
        printf("|%2d|.5", (int)i);
    printf("|\n");
    for(int i = 0; i < events.size(); i++){
        Round *rounds = events[i].rounds;
        for(float j = 0; j < rounds[0].startTime - startAll; j+=0.5)
            printf("|  ");
        int k = 0;
        while(rounds[k].startTime > 0){
            printf("|##");
            k++;
        }
        for(float j = rounds[k-1].startTime + rounds[k-1].roundLength; j < endAll; j+=0.5)
            printf("|  ");
        printf("|\n");
    }
}
