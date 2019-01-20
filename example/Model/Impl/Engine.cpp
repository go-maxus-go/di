#include "Engine.h"

#include <iostream>


namespace Model {

int Engine::speed() const
{
    return m_speed;
}

void Engine::setSpeed(int speed)
{
    std::swap(m_speed, speed);
    if (m_speed != speed)
        std::cout << "Speed changed: " << m_speed << std::endl;
}

} // namespace Model
