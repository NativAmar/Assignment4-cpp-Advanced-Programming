#ifndef GAME_H
#define GAME_H

#include "Room.h"
#include "Entity.h"

class Game {
    Room *entryRoom;
    string configuration_file;
    Room **rooms;
    int roomCounter;
    Entity playerEntity;

public:
    Game();
    Game(const string& configurationFile, int amountOfLife, int damage);
    ~Game();
    void cleanAndClear();
    void addRoomToArray(Room *room);
    Room *getRoomByID(const string& roomID) const;
    void parseFile(const string& configurationFile);
    void parseLine(const string& line);
    void initializer();//Game initializer
    void run();
};

#endif
