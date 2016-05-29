#pragma once

#include "pch.h"

namespace CustomizableClassHierarchy
{
    public ref class ClassAndSubclasses sealed
    {
    public:
        ClassAndSubclasses(ReflectionHelper::TypeInformation^ parent);

        property ReflectionHelper::TypeInformation^ Parent;
        property Windows::Foundation::Collections::IVector<ClassAndSubclasses^>^ Subclasses;
    };
}
