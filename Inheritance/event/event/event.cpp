//
//  event.cpp
//  event
//
//  Created by Mitchell McLinton on 6/2/20.
//  Copyright © 2020 Mitchell McLinton. All rights reserved.
//

#include <iostream>
#include <string>
using namespace std;

/* TODO: remove all above */

///////////////////////////////////////////////////////////////////////////////////////////
// Event Definition & Implementation
///////////////////////////////////////////////////////////////////////////////////////////
class Event {
public:
    Event(std::string name);
    virtual ~Event() = 0;
    std::string name() const;
    virtual bool isSport() const;
    virtual std::string need() const = 0;
private:
    std::string m_name;
};

Event::Event(std::string name) : m_name(name)
{}

Event::~Event()
{}

std::string Event::name() const {
    return m_name;
}

bool Event::isSport() const {       // most Events are sports, but some are not --> virtual capability given
    return true;
}

///////////////////////////////////////////////////////////////////////////////////////////
// BasketballGame Definition & Implementation
///////////////////////////////////////////////////////////////////////////////////////////
class BasketballGame : public Event {
public:
    BasketballGame(std::string name);
    virtual ~BasketballGame();
    virtual std::string need() const;
};

BasketballGame::BasketballGame(std::string name) : Event(name)
{}

BasketballGame::~BasketballGame() {
    std::cout << "Destroying the " << name() << " basketball game" << endl;
}

std::string BasketballGame::need() const {
    return "hoops";
}

///////////////////////////////////////////////////////////////////////////////////////////
// Concert Definition & Implementation
///////////////////////////////////////////////////////////////////////////////////////////
class Concert : public Event {
public:
    Concert(std::string name, std::string genre);
    virtual ~Concert();
    virtual bool isSport() const;
    virtual std::string need() const;
private:
    std::string m_genre;
};

Concert::Concert(std::string name, std::string genre) : Event(name), m_genre(genre)
{}

Concert::~Concert() {
    std::cout << "Destroying the " << name() << " " << m_genre << " concert" << endl;
}

bool Concert::isSport() const {
    return false;
}

std::string Concert::need() const {
    return "a stage";
}

///////////////////////////////////////////////////////////////////////////////////////////
// HockeyGame Definition & Implementation
///////////////////////////////////////////////////////////////////////////////////////////
class HockeyGame : public Event {
public:
    HockeyGame(std::string name);
    virtual ~HockeyGame();
    virtual std::string need() const;
};

HockeyGame::HockeyGame(std::string name) : Event(name)
{}

HockeyGame::~HockeyGame() {
    std::cout << "Destroying the " << name() << " hockey game" << endl;
}

std::string HockeyGame::need() const {
    return "ice";
}

/* TODO: remove all below */

///////////////////////////////////////////////////////////////////////////////////////////
// display() function
///////////////////////////////////////////////////////////////////////////////////////////

void display(const Event* e)
{
    std::cout << e->name() << ": ";
    if (e->isSport())
    std::cout << "(sport) ";
    std::cout << "needs " << e->need() << endl;
}

///////////////////////////////////////////////////////////////////////////////////////////
// main()
///////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    Event* events[4];
    events[0] = new BasketballGame("Lakers vs. Suns");
      // Concerts have a name and a genre.
    events[1] = new Concert("Banda MS", "banda");
    events[2] = new Concert("KISS", "hard rock");
    events[3] = new HockeyGame("Kings vs. Flames");

    std::cout << "Here are the events." << endl;
    for (int k = 0; k < 4; k++)
        display(events[k]);

      // Clean up the events before exiting
    std::cout << "Cleaning up." << endl;
    for (int k = 0; k < 4; k++)
    delete events[k];
}
