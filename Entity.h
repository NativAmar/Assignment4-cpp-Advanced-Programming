#ifndef ENTITY_H
#define ENTITY_H

using namespace std;
#include <iostream>
#include <string>

class Entity {
    string name;
    int maxAmountOfLife;
    int currentAmountOfLife; //should be bigger than 0 and lower/equal than maximum
    int attackValue;

public:
    //constructors
    Entity() : name(""),maxAmountOfLife(0), currentAmountOfLife(0), attackValue(0) {};
    Entity(string name,int maxAmountOfLife, int damageValue) : name(move(name)),maxAmountOfLife(maxAmountOfLife),
                                                                    currentAmountOfLife(maxAmountOfLife), attackValue(damageValue) {};
    //copy constructor
    Entity(const Entity& Esource) {
        name = Esource.name;
        maxAmountOfLife = Esource.maxAmountOfLife;
        currentAmountOfLife = Esource.currentAmountOfLife;
        attackValue =  Esource.attackValue;
    };
    //destructor
    ~Entity();

    Entity& operator+=(int num); //increase the currentAmountOfLife by the num which received
    Entity& operator-=(const Entity& other); //reduce the currentAmountOfLife according to the received character's attackValue
    Entity& operator-=(int num); //reduce the attckValue according the received number
    Entity& operator=(const Entity& Esource);
    int getCurrentAmountOfLife() const;
    int getAttackValue() const;
    bool operator==(const Entity& other) const; //This operator will compare characters by their damage multiplied by the current amount of life they have
    bool operator>(const Entity& other) const;
    bool operator<(const Entity &other) const;
    friend ostream& operator<<(ostream& os, const Entity& other);//print
};

#endif