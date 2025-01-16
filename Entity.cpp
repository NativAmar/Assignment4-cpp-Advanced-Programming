#include "Entity.h"

Entity& Entity::operator+=(int num) {
    if (num >= 0) {
        this->currentAmountOfLife += num;
    }
    //to make sure the current amount of life don't increase more than the maximum level
    if (this->currentAmountOfLife >= this->maxAmountOfLife) {
        this->currentAmountOfLife = this->maxAmountOfLife;
    }
    return *this;
}

Entity& Entity::operator-=(const Entity& other) {
    this->currentAmountOfLife -= other.attackValue;
    if (this->currentAmountOfLife <= 0) {
        this->currentAmountOfLife = 0;
    }
    return *this;
}

Entity& Entity::operator-=(int num) {
    this->attackValue -= num;
    return *this;
}

Entity& Entity::operator=(const Entity& other) {
    if (this == &other)
        return *this;
    this->name = other.name;
    this->currentAmountOfLife = other.currentAmountOfLife;
    this->maxAmountOfLife = other.maxAmountOfLife;
    this->attackValue = other.attackValue;
    return *this;
}

int Entity::getCurrentAmountOfLife() const {
    return this->currentAmountOfLife;
}

int Entity::getAttackValue() const {
    return this->attackValue;
}

bool Entity::operator==(const Entity& other) const {
    return this->attackValue * this->currentAmountOfLife == other.attackValue * other.currentAmountOfLife;
}

bool Entity::operator>(const Entity &other) const {
    return this->attackValue * this->currentAmountOfLife > other.attackValue * other.currentAmountOfLife;
}

//I should check if it's necessary
bool Entity::operator<(const Entity &other) const {
    return this->attackValue * this->currentAmountOfLife < other.attackValue * other.currentAmountOfLife;
}

bool Entity::operator>=(const Entity &other) const {
    return this->attackValue * this->currentAmountOfLife >= other.attackValue * other.currentAmountOfLife;
}

bool Entity::operator<=(const Entity &other) const {
    return this->attackValue * this->currentAmountOfLife <= other.attackValue * other.currentAmountOfLife;
}
//till here

ostream& operator<<(ostream& os, const Entity& other) {
    os << other.name << " (" << other.currentAmountOfLife << "/" << other.maxAmountOfLife << ")" << " - " << other.attackValue;
    return os;
}



