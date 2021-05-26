#pragma once

#include <memory>

#include "Logic/Fwd.h"

#include "App/IApplication.h"



namespace App {

class Application : public IApplication
{
public:
    using di = Logic::CarTag;
    Application(Logic::CarPtr car);

public: // IApplication
    int exec() override;

private:
    Logic::CarPtr car;
};

} // namespace Model
