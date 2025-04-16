/**
* 
*/
#include "artemis.h"    // IWYU pragma: keep

class(ArtemisComponentType);

ArtemisComponentTypeRef method Ctor(ArtemisComponentTypeRef this, CFClassRef cls, ulong index)
{

    this->type = cls;
    this->index = index;
    if (this->index < 0) {
        this->index = ArtemisComponentTypeIndex++;
    }
    this->taxonomy = ArtemisTaxonomy_BASIC;
    return this;
}

CFStringRef ArtemisComponentTypeGetName(ArtemisComponentTypeRef this)
{
    return CFCreate(CFString, this->obj.cls->name);
}

ulong ArtemisComponentTypeGetIndex(ArtemisComponentTypeRef this)
{
    return this->index;
}

ArtemisTaxonomy ArtemisComponentTypeGetTaxonomy(ArtemisComponentTypeRef this)
{
    return this->taxonomy;
}

