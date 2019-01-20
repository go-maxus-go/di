#pragma once

#include <memory>

#include "Model/IEngine.h"


namespace Model {

class Engine : public IEngine
{
public: // IEngine
    int speed() const override;
    void setSpeed(int speed) override;

private:
    int m_speed = 0;
};

} // namespace Model
