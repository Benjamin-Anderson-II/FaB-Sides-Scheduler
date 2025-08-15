# Flesh and Blood Side Events Scheduler
## Expectation
The application will take in Judges (and their shifts), and Events. It will then create a schedule of which Judges are assigned to each Event, and incorporate each Judge's Break.

Only one Judge is to be assigned to any given Event.

The Breaks will be centered around the middle of the day as best as possible and a Judge will never have consecutive Breaks.

If a judge cannot get a break between events it is preferred to place their break just after the last round.

Breaks may occur at these times:
- Just after an event starts
- While a Judge is not working an Event



### Misc
- Judge-Event ratio is 1-1
- Judges are Full-Time (X Hours) or Half-Time (X Hours)
  - Full-Time gets two breaks:
    - 1 hour
    - 30 mins
- Events are multiple rounds.
  - rounds are either ~30 mins or ~60 mins
  - commonly there are 4-5 rounds

