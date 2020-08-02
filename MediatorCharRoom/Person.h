//
// Created by Nan Ni on 2020/7/22.
//

#ifndef MEDIATORCHARROOM_PERSON_H
#define MEDIATORCHARROOM_PERSON_H

#include <string>
#include <vector>

#include "ChatRoom.h"


//class ChatRoom;

class Person {
public:
    std::string name;
    ChatRoom* room{nullptr};
    std::vector<std::string> chat_log;

    Person(const std::string &name);

    void say(const std::string &message) const;
    void pm(const std::string &who, const std::string& message) const;

    void receive(const std::string &origin, const std::string &message); //origin: where we get the message from?

    bool operator==(const Person &rhs) const;

    bool operator!=(const Person &rhs) const;



};


#endif //MEDIATORCHARROOM_PERSON_H
