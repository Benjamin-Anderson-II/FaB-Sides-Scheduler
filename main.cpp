#include "events.h"

int main (int argc, const char *argv[]) {
    // initialize variables
    Events events((char *)"test1.event");
    events.sort();
    events.print();

    return 0;
}
