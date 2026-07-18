#include "Core/Guardian.h"

namespace EvoSphere
{
    void initializeGuardian(
        Guardian* guardian,
        const std::string& name,
        const std::string& title,
        ElementType elementType,
        const std::string& specialPower,
        const std::string& blessing,
        const std::string& curse
    )
    {
        if (guardian == nullptr)
        {
            return;
        }

        guardian->name = name;
        guardian->title = title;
        guardian->elementType = elementType;
        guardian->specialPower = specialPower;
        guardian->blessing = blessing;
        guardian->curse = curse;
    }
}
