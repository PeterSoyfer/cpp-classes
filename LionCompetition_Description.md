Imagine you are a lion tamer who wants to participate in the lion competition, which can be described as follows: you have your own team of lions (name, height)
and a private schedule (name, enterTime, exitTime) according to which lions enter and exit the showroom where judges mark them (the only parameter that plays role is lion's
height). You know neither names of other lions nor their schedules, but you are still interested in estimating your winning chances before the decision of the jury is published.

The program consists of:
the LionCompetition class constructor that accepts lion descriptions and the private schedule of when the lions enter and exit the showroom;
the lionEntered and lionLeft functions that are called whenever a new lion enters or leaves the room;
the getBiggestLions function that, for the current time, returns a list of our lions in the room that are at least as big as the biggest lion from competing teams in the room
(the presented list has to be sorted alphabetically).

Function definitions:
LionCompetition class constructor parameters: lions - list of elements (struct LionDescription) describing your lions (name, height),
schedule - a private schedule (list of LionSchedule structs) of when your lions enter and leave the showroom (name, enterTime, exitTime)

lion Entered function parameters:
currentTime - integer number of minutes since the start of the show
height

lionLeft function parameters:
currentTime, height

Constraints:
Subsequent invocations of lionLeft and lionEntered are always called in order of currentTime
The schedule is strictly followed - lions enter and exit exactly at their times
The lion inspection (invocation of the getBiggestLions function) takes place either before or after all lions scheduled to enter or leave the room at a given minute did
that - never in between.
Lion names are unique.
Times are always integers.

A single lion enters the room only once during the show.
