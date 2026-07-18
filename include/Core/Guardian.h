#pragma once

#include <string>

#include "Utils/Constants.h"

namespace EvoSphere
{
    struct Guardian
    {
        std::string name;
        std::string title;
        ElementType elementType = ElementType::None;
        std::string specialPower;
        std::string blessing;
        std::string curse;
    };

    void initializeGuardian(
        Guardian* guardian,
        const std::string& name,
        const std::string& title,
        ElementType elementType,
        const std::string& specialPower,
        const std::string& blessing,
        const std::string& curse
    );
}
