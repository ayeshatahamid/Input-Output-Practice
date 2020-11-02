#include <iostream>
#include <fstream>
#include "extrafile.h"
#include <vector>
using namespace std;

int main()
{
    /*cout << "Which file(s) to open?\n";
    cout << "1. friendlyships.shp" << endl;
    cout << "2. enemyships.shp" << endl;
    cout << "3. Both files" << endl; */
    int option;
    cin >> option;

    vector<extrafile> shiplist;

    ifstream file("friendlyships.shp", ios_base::binary);

    if (option == 2) {
        file.close();
        file.open("enemyships.shp", ios_base::binary);
    }

    int count = 0;
    int weaponCount;
    int timesOpened = 1;

    while (file.is_open()) {
        //read how many ships are there
        file.read((char*)&count, 4);

        for (int i = 0; i < count; i++) {//repeat for every ship
            //NAME
            //read the length of the string
            short length;
            file.read((char *)&length, 4);
            //dynamically allocate char array with the size of the length (already includes null terminator)
            char* name = new char[length];
            //read string to char array
            file.read(name, length * sizeof(name[0])); //name[0] is the byte size of the first/every char
            //convert char array to string
            string stringName;
            for (int j = 0; j < length - 1; j++) {
                stringName += name[j];
            }
            //makes new ship
            extrafile newShip(stringName);

            //delete char array
            delete[] name;


            //CLASS
            file.read((char *)&length, 4);
            char* shipClass = new char[length];
            file.read(shipClass, length * sizeof(shipClass[0]));
            string stringClass;
            for (int j = 0; j < length - 1; j++) {
                stringClass += shipClass[j];
            }
            newShip.setClass(stringClass);

            delete[] shipClass;

            //LENGTH
            short shipLength;
            file.read((char *)&shipLength, 2);

            newShip.setLength(shipLength);

            //CAPACITY
            int maxCap;
            file.read((char*)&maxCap, 4);

            newShip.setCap(maxCap);

            //WARP
            float warpSpeed;
            file.read((char*)&warpSpeed, 4);

            newShip.setWarp(warpSpeed);

            //WEAPONS
            file.read((char*)&weaponCount, 4);
            if (weaponCount == 0) {
                newShip.addWeaponCount();
                newShip.setWeapon("Unarmed");
                newShip.setPower(0);
                newShip.setConsumption(0.0);
            }
            else {
                for (int k = 0; k < weaponCount; k++) {
                    //WEAPON COUNT
                    newShip.addWeaponCount();

                    //WEAPON
                    file.read((char *)&length, 4);
                    char* weapon = new char[length];
                    file.read(weapon, length * sizeof(weapon[0]));
                    string stringWeapon;
                    for (int j = 0; j < length - 1; j++) {
                        stringWeapon += weapon[j];
                    }
                    delete[] weapon;

                    newShip.setWeapon(stringWeapon);

                    //POWER
                    int power;
                    file.read((char*)&power, 4);
                    newShip.setPower(power);

                    //CONSUMPTION
                    float consumption;
                    file.read((char*)&consumption, 4);
                    newShip.setConsumption(consumption);
                }
            }

            //add ship to shiplist
            shiplist.push_back(newShip);
        }

        if (option == 1 || option == 2) { //just open one file
            file.close();
            break;
        }
        else if (option == 3) { //open the other file
            file.close();
            file.open("enemyships.shp", ios_base::binary);
            if (timesOpened == 2) {
                file.close();
            }
            timesOpened++;
        }
    }


    /*cout << "1. Print all ships" << endl;
    cout << "2. Starship with the strongest weapon" << endl;
    cout << "3. Strongest starship overall" << endl;
    cout << "4. Weakest ship (ignoring unarmed)" << endl;
    cout << "5. Unarmed ships" << endl; */


    cin >> option;


    if (option == 1) {
        for (long unsigned int i = 0; i < shiplist.size(); i++) {
            extrafile currentShip = shiplist.at(i);
            currentShip.print();
        }
    }
    else if (option == 2) {
        int maxPower = shiplist[0].returnPowerList().at(0);
        long unsigned int position = 0;
        for (long unsigned int i = 0; i < shiplist.size(); i++) { //go thru list of ships
            for (long unsigned int j = 0; j < shiplist[i].returnPowerList().size(); j++) { //go through list of powers
                if (maxPower < shiplist[i].returnPowerList().at(j)) {
                    maxPower = shiplist[i].returnPowerList().at(j);
                    position = i;
                }
            }
        }
        shiplist[position].print();
    }
    else if (option == 3) {
        int maxPower = 0;
        int totalShipPower = 0;
        long unsigned int position = 0;
        for (long unsigned int i = 0; i < shiplist.size(); i++) { //go thru list of ships
            for (long unsigned int j = 0; j < shiplist[i].returnPowerList().size(); j++) { //go through list of powers
                totalShipPower += shiplist[i].returnPowerList().at(j);
            }
            if (maxPower < totalShipPower) {
                maxPower = totalShipPower;
                position = i;
            }
            totalShipPower = 0;
        }
        shiplist[position].print();
    }
    else if (option == 4) {
        int minPower = shiplist[0].returnTotalPower();
        long unsigned int position = 0;
        for (long unsigned int i = 0; i < shiplist.size(); i++) { //go thru list of ships
            if (minPower > shiplist[i].returnTotalPower()) {
                if (shiplist[i].returnTotalPower() == 0) {
                    continue;
                }
                else {
                    minPower = shiplist[i].returnTotalPower();
                    position = i;
                }
            }
        }
        shiplist[position].print();
    }
    else if (option == 5) {
        for (long unsigned int i = 0; i < shiplist.size(); i ++) {
            for (long unsigned int j = 0; j < shiplist[i].returnPowerList().size(); j++) {
                if (shiplist[i].returnPowerList().at(j) == 0) {
                    shiplist[i].print();
                }
            }
        }
    }
    return 0;
}
