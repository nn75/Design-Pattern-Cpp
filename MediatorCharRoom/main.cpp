#include <iostream>
#include "ChatRoom.h"
#include "Person.h"


int main() {
    ChatRoom room;

    Person john{"John"};
    Person jane{"Jane"};

    room.join(&john);
    room.join(&jane);

    john.say("hi room");
    jane.say("oh, hey john");


    Person simon{"Simon"};
    room.join(&simon);
    simon.say("Hi, everyone!");


    jane.pm("Simon", "glad you to found us, Simon");
    return 0;
}
