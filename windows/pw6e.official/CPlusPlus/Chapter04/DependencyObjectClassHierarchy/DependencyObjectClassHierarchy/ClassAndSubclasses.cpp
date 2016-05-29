#include "pch.h"
#include "ClassAndSubclasses.h"

using namespace DependencyObjectClassHierarchy;
using namespace Platform;
using namespace Platform::Collections;
using namespace ReflectionHelper;

ClassAndSubclasses::ClassAndSubclasses(TypeInformation^ parent)
{
    this->Parent = parent;
    this->Subclasses = ref new Vector<ClassAndSubclasses^>();
}

