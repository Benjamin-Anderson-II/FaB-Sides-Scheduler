typedef struct {
    float startTime;    // What time the round is supposed to start
} Round;

typedef struct {
    char  name[128];
    float roundLength;  // Length of the round (either .5 or 1 hr)
    int   numRounds;
    std::vector<Round> rounds;
} Event;
