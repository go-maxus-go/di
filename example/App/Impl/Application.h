#pragma once

#include <memory>

#include "Car/Fwd.h"

#include "App/IApplication.h"


namespace App {

class Application : public IApplication
{
public:
    using di = Car::CarTag;
    Application(Car::CarPtr car);

public: // IApplication
    int exec() override;

private:
    Car::CarPtr car;
};

} // namespace Model
