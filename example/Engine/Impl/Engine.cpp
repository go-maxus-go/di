#include "Engine.h"

#include <iostream>


namespace Engine {

void Engine::start()
{
    m_started = true;
    std::cout << "Engine start" << std::endl;
}

void Engine::stop()
{
    m_started = false;
    std::cout << "Engine stop" << std::endl;
}

void Engine::setSpeed(int speed)
{
    m_speed = speed;
}

} // namespace Engine
