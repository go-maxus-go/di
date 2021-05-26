#pragma once


namespace App {

struct IApplication
{
    virtual ~IApplication() = default;

    virtual int exec() = 0;
};

} // namespace Model
