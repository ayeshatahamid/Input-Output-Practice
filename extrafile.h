//
// Created by Ayesha on 10/30/2020.
//

#ifndef LAB5_EXTRAFILE_H
#define LAB5_EXTRAFILE_H
#include <iomanip>
#include <iostream>
#include <vector>
using namespace std;


class extrafile {
    string name;
    string classString;
    short length;
    int capacity;
    float maxWarp;

    int weaponCount = 0;
    string weapon;
    int power;
    float consumption;

public:
    extrafile(string name);
    void setClass(string classString);
    void setLength(short length);
    void setCap(int cap);
    void setWarp(float warp);
    void print();

    int returnTotalPower();
    void addWeaponCount();
    void setWeapon(string weapon);
    void setPower(int power);
    void setConsumption(float consumption);
    vector<int> returnPowerList();

    vector<string> weaponlist;
    vector<int> powerlist;
    vector<float> consumptionlist;
};


#endif //LAB5_EXTRAFILE_H
