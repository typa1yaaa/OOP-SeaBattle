#ifndef OBSERVER_H
#define OBSERVER_H
#include <vector>

class Observer{
public:
    virtual void update() = 0; // метод для обработки обновления
    virtual ~Observer() = default;
};

class Observable{
private:
    std::vector<Observer*> observers;
public:
    void add_observer(Observer* observer);

    void notify_observers();

    virtual ~Observable() = default;
};
#endif //OBSERVER_H