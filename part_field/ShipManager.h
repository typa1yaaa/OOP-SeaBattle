#ifndef SHIPMANAGER_H
#define SHIPMANAGER_H

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "Ship.h"


class ShipManager{
private:
    std::vector<Ship> all_ships;
    
public:
    std::vector<int> count_ships;
    std::vector<int> len_ships; 
    ShipManager(const vector<int>& count_ship, const vector<int>& len_ship);
    vector<Ship>& GetAllShips();
    void SetAllShips(std::vector<Ship> new_allships);
    Ship* SearchShipId(int shipId);
    
    ShipManager(ShipManager&& other) noexcept;
    ShipManager(const ShipManager& other);
    ShipManager Clone();
    friend std::ostream& operator<<(std::ostream& out, ShipManager& ship_manager);
    friend std::istream& operator>>(std::istream& in, ShipManager& ship_manager);
};    

#endif //SHIPMANAGER_H