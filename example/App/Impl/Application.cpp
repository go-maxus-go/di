#include "Application.h"

#include "Car/ICar.h"


namespace App {

Application::Application(Car::CarPtr car)
    : car(std::move(car))
{}

int Application::exec()
{
    car->drive();
    car->stop();

    return 0;
}

} // namespace Model
