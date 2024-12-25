#include "Observer.h"

void Observable::add_observer(Observer* observer){
    observers.push_back(observer);
}

void Observable::notify_observers(){
    for(Observer* observer : observers){
        observer->update();
    }
}