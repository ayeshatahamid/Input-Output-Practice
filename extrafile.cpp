//
// Created by Ayesha on 10/30/2020.
//

#include "extrafile.h"

extrafile::extrafile(string name) {
    this->name = name;
}
void extrafile::setClass(string classString) {
    this->classString = classString;
}
void extrafile::setLength(short length) {
    this->length = length;
}
void extrafile::setCap(int cap) {
    capacity = cap;
}
void extrafile::setWarp(float warp) {
    maxWarp = warp;
}

void extrafile::print() {
    cout << "Name: " << name << endl;
    cout << "Class: " << classString << endl;
    cout << "Length: " << length << endl;
    cout << "Shield capacity: " << capacity << endl;
    cout << "Maximum Warp: " << maxWarp << endl;
    cout << "Armaments: " << endl;
    for (long unsigned int i = 0; i < weaponlist.size(); i++) {
        if (powerlist[i] == 0) {
            cout << weaponlist[i] << endl;
        }
        else {
            cout << weaponlist[i];
            cout << ", " << powerlist[i];
            cout << ", " << consumptionlist[i] << endl;
        }
    }
    if (powerlist.at(0) != 0) {
        cout << "Total firepower: " << returnTotalPower() << endl;
    }
    cout << endl;
}

void extrafile::addWeaponCount() {
    weaponCount++;
}

void extrafile::setWeapon(string weapon) {
    weaponlist.push_back(weapon);
}

void extrafile::setPower(int power) {
    powerlist.push_back(power);
}

void extrafile::setConsumption(float consumption) {
    consumptionlist.push_back(consumption);
}

vector<int> extrafile::returnPowerList() {
    return powerlist;
}

int extrafile::returnTotalPower() {
    int totalPower = 0;
    for (long unsigned int i = 0; i < powerlist.size(); i++) { //go thru list of ships
        totalPower += powerlist.at(i);
    }
    return totalPower;
}


