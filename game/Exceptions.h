#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <iostream>
using namespace std;

class NoAbilitiesException: public exception{
    public:
        const char* what() const noexcept override;
};

class NoShipManagerException: public exception{
public:
    const char* what() const noexcept override;
};

class MismatchOfValues: public exception{
public:
    const char* what() const noexcept override;
};

class InvalidShipPossition: public exception{
public:
    const char* what() const noexcept override;
};

class InvalidOrientation: public exception{
public:
    const char* what() const noexcept override;   
};

class ViolationAttackForField: public exception{
public:
    const char* what() const noexcept override;
};

class ViolationScannerForField: public exception{
public:
    const char* what() const noexcept override;
};

class InvalidShipLength: public invalid_argument{
public:
    InvalidShipLength();
    
    // const char* what() const noexcept override;
};

class InvalidFieldSize: public invalid_argument{
public:
    InvalidFieldSize();
    
    // const char* what() const noexcept override;
};

class InvalidPoint: public exception{
public:
    const char* what() const noexcept override;
};
#endif // EXCEPTIONS_H