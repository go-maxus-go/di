#include "Application.h"

#include "Logic/ICar.h"



namespace App {

Application::Application(Logic::CarPtr car)
    : car(std::move(car))
{}

int Application::exec()
{
    car->useParkingBreak(false);
    car->drive();
    car->useBreak(true);
    car->useParkingBreak(true);

    return 0;
}

} // namespace Model
