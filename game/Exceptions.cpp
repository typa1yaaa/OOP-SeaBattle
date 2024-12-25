#include "Exceptions.h"

const char* NoAbilitiesException::what() const noexcept {
    return "Invalid ability value: The ability is empty. :(";
};

const char* NoShipManagerException::what() const noexcept {
    return "You have submitted an empty ship manager. Please fill it out :)";
};

const char* MismatchOfValues::what() const noexcept {
    return "Oh no, you don't have the number of ships equal to the number of orientations. Please fill it out :)";
};

const char* InvalidShipPossition::what() const noexcept {
    return "Invalid ship placement: Ships cannot touch or overlap! :|";
};

const char* InvalidOrientation::what() const noexcept {
    return "Invalid ship orientsnion: A ship can only have a horizontal (H) or vertical (V) orientation! :|";
};

const char* ViolationAttackForField::what() const noexcept {
    return "Trespassing: You are trying to attack a cell outside the field. :/";
};

const char* ViolationScannerForField::what() const noexcept {
    return "Trespassing: You are trying to scan a cell outside the field. :/";
};

InvalidShipLength::InvalidShipLength()
    : std::invalid_argument("Error: length must be between 1 and 4.") {}

// const char* InvalidShipLength::what() const noexcept {
//     return std::invalid_argument::what();
// }

InvalidFieldSize::InvalidFieldSize()
    : std::invalid_argument("Error: field_size must be a positive integer >=7.") {}

// const char* InvalidFieldSize::what() const noexcept {
//     return std::invalid_argument::what();
// }
const char* InvalidPoint::what() const noexcept {
    return "Error: your cell is out of the field.";
};
