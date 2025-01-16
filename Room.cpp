#include "Room.h"
#include <stdexcept>

using namespace std;

int Room::roomsCapacity = 9;

Room::Room(const string &roomID, int campfire, int monsterCurrAmountOfLife, int monsterAttackValue): roomEntity(nullptr),
                                                                                                     roomsAccess(nullptr), roomsCounter(0) {
    if (monsterCurrAmountOfLife < 0 || monsterAttackValue < 0) {
        throw invalid_argument("Invalid input");
    }
    if (monsterCurrAmountOfLife != 0 && monsterAttackValue != 0) {
        roomEntity = new Entity("Monster", monsterCurrAmountOfLife, monsterAttackValue);
    }
    room_id = roomID;
    m_campfire = campfire;
}

//copy constructor
Room::Room(const Room &other) {
    //copy simple fields
    this->room_id = other.room_id;
    this->m_campfire = other.m_campfire;
    this->roomsCounter = other.roomsCounter;

    if (other.roomEntity)
        this->roomEntity = new Entity(*other.roomEntity);
    else
        this->roomEntity = nullptr;

    if (other.roomsAccess) {
        this->roomsAccess = new Room *[roomsCounter];
        for (int i = 0; i < other.roomsCounter; ++i) {
            this->roomsAccess[i] = other.roomsAccess[i];
        }
    } else
        this->roomsAccess = nullptr;
}

Room::~Room() {
    delete roomEntity;
    delete[] roomsAccess;
    roomsAccess = nullptr;
}

// Assignment Operator
Room &Room::operator=(const Room *other) {
    if (this != other) {
        delete roomEntity;
        delete roomsAccess;
        room_id = other->room_id;
        m_campfire = other->m_campfire;
        if (other->roomEntity) {
            roomEntity = new Entity(*other->roomEntity);
        } else {
            roomEntity = nullptr;
        }
        roomsCounter = other->roomsCounter;
        if (other->roomsAccess) {
            this->roomsAccess = new Room *[roomsCounter];
            for (int i = 0; i < roomsCounter; ++i) {
                this->roomsAccess[i] = other->roomsAccess[i];
            }
        } else {
            roomsAccess = nullptr;
        }
    }
    return *this;
}

Room *Room::operator[](int index) {
    if (roomsCounter == 0 || index >= roomsCounter) {
        throw out_of_range("Index out of range");
    } else {
        return this->roomsAccess[index];
    }
}

const Room *Room::operator[](int index) const {
    if (roomsCounter == 0 || index >= roomsCounter) {
        throw out_of_range("Index out of range");
    } else {
        return this->roomsAccess[index];
    }
}

int Room::getRoomCounter() const {
    return roomsCounter;
}

bool Room::setRoomAccess(Room* room, int index) {
    if (index < 0 || index >= roomsCapacity) {
        throw out_of_range("Index out of range");
    }
    if (room == nullptr) {
        throw invalid_argument("Invalid input");
    }
    if (index >= roomsCounter) {
        // Allocate new memory for roomsAccess with one place more than the current counter
        Room** newRoomsAccess = new Room*[index + 1];
        // Copy existing rooms to the new array
        for (int i = 0; i < roomsCounter; ++i) {
            newRoomsAccess[i] = roomsAccess[i];
        }
        // Initialize new elements to nullptr
        for (int i = roomsCounter; i <= index; ++i) {
            newRoomsAccess[i] = nullptr;
        }
        // Delete the old array and assign the new array
        delete[] roomsAccess;
        roomsAccess = newRoomsAccess;
        roomsCounter = index + 1;
    }

    roomsAccess[index] = room;

    return true; // Assignment successful
}

string Room::getID() const {
    return room_id;
}
