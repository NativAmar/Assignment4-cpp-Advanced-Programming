#include "Game.h"

#include <fstream>
#include <sstream>
#include <string>
#include <iostream>

using namespace std;


Game::Game() {
    entryRoom = new Room("", 0, 0, 0);
    configuration_file = "";
    rooms = nullptr;
    roomCounter = 0;
}

Game::Game(const string& configurationFile, int amountOfLife, int damage) {
    entryRoom = new Room("", 0, 0, 0);
    configuration_file = configurationFile;
    playerEntity = Entity("Player", amountOfLife, damage);
    rooms = nullptr;
    roomCounter = 0;
}

Game::~Game() {
    cleanAndClear();
}

void Game::cleanAndClear() {
    if (rooms != nullptr) {
        for (int i = 0; i < roomCounter; i++) {
            delete rooms[i];
        }
        delete rooms;
        rooms = nullptr;
        roomCounter = 0;
    }
}

void Game::addRoomToArray(Room *room) {
    Room** newRooms = new Room*[roomCounter + 1];
    for (int i = 0; i < roomCounter; ++i) {
        newRooms[i] = rooms[i];
    }
    newRooms[roomCounter] = room;
    delete[] rooms;
    rooms = newRooms;
    roomCounter++;
}

Room* Game::getRoomByID(const string& roomID) const {
    for (int i = 0; i < roomCounter; ++i) {
        if (rooms[i]->getID() == roomID) {
            return rooms[i];
        }
    }
    return nullptr;
}



void Game::parseLine(const string& line) {
    istringstream s(line);
    string roomID;
    int campfire, monsterLife, monsterDamage;
    if (s >> roomID >> campfire >> monsterLife >> monsterDamage) {
        Room *newRoom = new Room(roomID, campfire, monsterLife, monsterDamage);
        addRoomToArray(newRoom);

        Room* finalRoomAddress = getRoomByID(roomID.substr(0, roomID.length() - 1));
        if (finalRoomAddress == nullptr) {
            throw out_of_range("Room does not exist");
        }
        finalRoomAddress->setRoomAccess(newRoom, stoi(&roomID.back()));
    }
}

void Game::parseFile(const string& configurationFile) {
    ifstream file(configuration_file);
    string line;
    if (!file) {
        cerr << "Could not open file " << configurationFile << endl;
        return;
    }
    while (getline(file, line)) {
        if (line.empty()) {
            continue;
        }
        parseLine(line);
    }
}

void Game::initializer() {
    addRoomToArray(entryRoom);
    parseFile(configuration_file);
}

void Game::run() {

    cout << playerEntity << endl;
    cout << "I see you like challenges, by how much do you want to reduce your damage? " << endl;
    int damageReduce;
    cin >> damageReduce;

    playerEntity -= damageReduce;

    Room* currentRoom = entryRoom;
    while (currentRoom != nullptr) {
        cout << playerEntity << endl;
        if (currentRoom->m_campfire == 0 && currentRoom->roomEntity == nullptr) {
            cout << "You arrive to an empty room " << endl;
        }
        if (currentRoom->m_campfire > 0) {
            cout << "You sit by the campfire and heal " << currentRoom->m_campfire << " health" << endl;
            playerEntity += currentRoom->m_campfire;
        }
        string compareRes;
        if (currentRoom->roomEntity != nullptr) {
            if (playerEntity > *(currentRoom->roomEntity)) {
                compareRes = "smaller ";
            }
            else if (playerEntity < *(currentRoom->roomEntity)) {
                compareRes = "larger ";
            }
            else {
                compareRes = "equally sized ";
            }
            cout << "You encounter a " << compareRes << "monster" << endl;
            cout << *(currentRoom->roomEntity) << endl;
            while (currentRoom->roomEntity->getCurrentAmountOfLife() != 0 || playerEntity.getCurrentAmountOfLife() != 0) {
                *(currentRoom->roomEntity) -= playerEntity;
                cout << "You deal " << playerEntity.getAttackValue() << " damage to the monster and leave it with " << currentRoom->roomEntity->getCurrentAmountOfLife() << " health" << endl;
                if (currentRoom->roomEntity->getCurrentAmountOfLife() == 0) {
                    cout << "You defeat the monster and go on with your journey " << endl;
                    break;
                }
                playerEntity -= *(currentRoom->roomEntity);
                cout << "The monster deals " << currentRoom->roomEntity->getAttackValue() << " damage to you and leaves you with " << playerEntity.getCurrentAmountOfLife() << " health" << endl;
                if (playerEntity.getCurrentAmountOfLife() == 0) {
                    cout << "You lost to the dungeon " << endl;
                    //exit and delete all
                    cleanAndClear();
                    return;
                }
            }
        }
        if (currentRoom->roomsCounter == 0 && currentRoom->roomsAccess == nullptr) { // there is no rooms to enter
            cout << "The room continues and opens up to the outside. you won against the dungeon" << endl;
            cleanAndClear();
            return;
        }
        if (currentRoom->roomsCounter == 1) { //one room is possible
            cout << "You see a single corridor ahead of you labeled " << currentRoom->roomsCounter - 1 << " " <<  endl;
            int choice;
            cin >> choice;
            currentRoom = (*currentRoom)[choice];
        }
        else { //more than one possible room
            cout << "You see corridors labeled from 0 to " << currentRoom->roomsCounter - 1 << ". Which one will you choose? " << endl;
            int choose;
            cin >> choose;
            currentRoom = (*currentRoom)[choose];
        }
    }
}
