//
// Created by Nan Ni on 2020/7/22.
//


#include "Person.h"

#include <iostream>

Person::Person(const std::string &name) : name (name) {}


void Person::say(const std::string &message) const {
    room -> broadCast(name, message);
}


void Person::pm(const std::string &who, const std::string& message) const {
    room -> message(name, who, message);
}

void Person::receive(const std::string &origin, const std::string &message) {
    std::string s{origin + ": \"" + message + "\""};
    std::cout << "[ " << name << "'s chat session]" << s << std::endl;
    chat_log.emplace_back(s);
}

bool Person::operator==(const Person &rhs) const {
    return name == rhs.name;
}

bool Person::operator!=(const Person &rhs) const {
    return !(rhs == *this);
}
