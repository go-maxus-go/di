#pragma once

#include <memory>

#include "Gas/IEngine.h"


namespace Gas {

class Engine : public IEngine
{
public: // IEngine
    void start() override;
    void stop() override;

    void setSpeed(int speed) override;

private:
    bool m_started = false;
    int m_speed = 0;
};

} // namespace Gas
