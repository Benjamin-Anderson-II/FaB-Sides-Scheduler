#include "events.h"

#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

/* Constructor Helper */
int readline(char (*l)[256], FILE *f){
    char *r = fgets(*l, sizeof(*l), f);
    (*l)[strcspn(*l, "\n")]=0;
    return (r) ? 1 : 0;
}
/* Constructor Helper */
size_t readField(char **str, char *out){
    // trim leading
    while(isspace((unsigned char)*(*str))) (*str)++;

    // get length of str
    size_t str_len = strcspn(*str, "\0");

    // get addr of ","
    char *end = (*str) + strcspn(*str, ",");

    // trim trailing
    char *comma = end-1;
    while(comma > *str && isspace((unsigned char)*comma)) comma--;
    comma++;

    // copy trimmed string and add null terminator
    size_t out_size = (comma - *str) < str_len ? (comma - *str) : str_len;
    memcpy(out, *str, out_size);
    out[out_size] = 0;

    // move str forward
    *str = *end ? end + 1 : end;

    return out_size;
}
/* Constructor */
Events::Events(char *fileName) {
    this->startTime = 1000;
    this->endTime = 0;
    // First line is header data
    char line[256];
    char field[128];
    FILE *fptr = fopen(fileName, "r");
    if(fptr == NULL){
        fprintf(stderr, "Whoopsie, that file doesn't exist\n");
        return;
    }

    readline(&line, fptr);
    while(readline(&line, fptr)){
        Event e;
        char *l = (char *)line;
        int start, num_rounds;

        // Read Name
        readField(&l, (char *)field);
        memcpy(e.name, field, 128);

        // Read Start Time
        readField(&l, (char *)field);
        if(field == 0){
            fprintf(stderr, "%s has an incorrect value for Start Time. Aborting\n", e.name);
            exit(1);
        }
        start = atoi(field);
        if(start < this->startTime)
            this->startTime = start;

        // Read Num Rounds
        readField(&l, (char *)field);
        e.numRounds = atoi(field);
        if(field == 0){
            fprintf(stderr, "%s has an incorrect value for Number of Rounds. Aborting\n", e.name);
            exit(1);
        }

        // Read Round Length
        readField(&l, (char *)field);
        e.roundLength = (float)atoi(field) / 60;
        if(field == 0){
            fprintf(stderr, "%s has an incorrect value for Round Length. Aborting\n", e.name);
            exit(1);
        }

        for(int i = 0; i < e.numRounds; i++) {
            Round r;
            r.startTime = start + (e.roundLength * i);
            e.rounds.push_back(r);
            if(r.startTime + e.roundLength > this->endTime)
                this->endTime = r.startTime + e.roundLength;
        }

        this->events.push_back(e);
    }
    fclose(fptr);
    return;
}

int partition(std::vector<Event> &events, int low, int high){
    int pivot = events[high].rounds[0].startTime;
    int i = (low - 1);

    for(int j = low; j < high; j++){
        if(events[j].rounds[0].startTime <= pivot) {
            i++;
            std::swap(events[i], events[j]);
        }
    }
    std::swap(events[i+1], events[high]);

    return (i+1);
}

void sortEvents(std::vector<Event> &events, int low, int high){
    if(low < high) {
        int pi = partition(events, low, high);
        sortEvents(events, low, pi - 1);
        sortEvents(events, pi + 1, high);
    }
}

void Events::sort() {
    sortEvents(this->events, 0, this->events.size() - 1);
}

Event &Events::operator[](unsigned int i){
    return this->events[i];
}

float Events::getStartTime(){
    return this->startTime;
}
float Events::getEndTime(){
    return this->endTime;
}
std::vector<Event> Events::getEventsAsVector(){
    return this->events;
}

void Events::print() {
    // Header
    for(float i = this->startTime; i < this->endTime; i++)
        printf("|%2d|.5", (int)i);
    printf("|\n");

    std::vector<Event> events = this->events;
    for(int i = 0; i < events.size(); i++){
        std::vector<Round> rounds = events[i].rounds;
        char sub[10];
        int sublen = events[i].roundLength * 5;
        memcpy(sub, events[i].name, sublen);
        sub[sublen] = 0; // Compiler moves the sub declaration to outside the loop...
        // Print Leading blocks
        for(float j = 0; j < rounds[0].startTime - this->startTime; j+=0.5)
            printf("|  ");

        int k = 0;
        for(int k = 0; k < events[i].numRounds; k++){
            printf("|%s", sub);
        }

        float j = events[i].rounds[0].startTime + events[i].roundLength * events[i].numRounds;
        for(; j < this->endTime; j+=0.5)
            printf("|  ");
        printf("|\n");
    }
}

