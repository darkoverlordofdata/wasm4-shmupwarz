/**
 * The most raw entity system. It should not typically be used, but you can create your own
 * entity system handling by extending this. It is recommended that you use the other provided
 * entity system implementations.
 * 
 * @author Arni Arent
 *
 */
#include "artemis.h"    // IWYU pragma: keep

class(ArtemisEntitySystem);

/**
 * Creates an entity system that uses the specified aspect as a matcher against entities.
 * @param aspect to match against entities
 */
ArtemisEntitySystemRef method Ctor(ArtemisEntitySystemRef this, ArtemisAspectRef aspect)
{
    this->actives = CFCreate(CFBag, 64);
    this->aspect = aspect;
    this->systemIndex = ArtemisSystemIndexManagerGetIndexFor(ArtemisEntitySystem);
    this->allSet = ArtemisAspectGetAllSet(this->aspect);
    this->exclusionSet = ArtemisAspectGetExclusionSet(this->aspect);
    this->oneSet = ArtemisAspectGetOneSet(this->aspect);
    this->dummy = ((Size(this->allSet) <= 0)
                    && (Size(this->oneSet) <= 0));

    return this;
}

/**
 * Called before processing of entities begins. 
 */
void ArtemisEntitySystemBegin(ArtemisEntitySystemRef this)
{
    (ArtemisEntitySystemRef)this;
}

void ArtemisEntitySystemProcess(ArtemisEntitySystemRef this)
{
    if (ArtemisEntitySystemCheckProcessing(this)) {
        ArtemisEntitySystemBegin(this);
        ArtemisEntitySystemProcessEntities(this, this->actives);
        ArtemisEntitySystemEnd(this);
    }
}

/**
 * Called after the processing of entities ends.
 */
void ArtemisEntitySystemEnd(ArtemisEntitySystemRef this)
{
    (ArtemisEntitySystemRef)this;
}

/**
 * Any implementing entity system must implement this method and the logic
 * to process the given entities of the system.
 * 
 * @param entities the entities this system contains.
 */
void ArtemisEntitySystemProcessEntities(ArtemisEntitySystemRef this, CFBagRef entities)
{
    (ArtemisEntitySystemRef)this;
    (CFBagRef)entities;
}

/**
 * 
 * @return true if the system should be processed, false if not.
 */
bool ArtemisEntitySystemCheckProcessing(ArtemisEntitySystemRef this)
{
    (ArtemisEntitySystemRef)this;
    return true;
}

/**
 * Override to implement code that gets executed when systems are initialized.
 */
void ArtemisEntitySystemInitialize(ArtemisEntitySystemRef this)
{
    (ArtemisEntitySystemRef)this;
}

/**
 * Called if the system has received a entity it is interested in, e.g. created or a component was added to it.
 * @param e the entity that was added to this system.
 */
void ArtemisEntitySystemInserted(ArtemisEntitySystemRef this, ArtemisEntityRef e)
{
    (ArtemisEntitySystemRef)this;
    (ArtemisEntityRef)e;
}

/**
 * Called if a entity was removed from this system, e.g. deleted or had one of it's components removed.
 * @param e the entity that was removed from this system.
 */
void ArtemisEntitySystemRemoved(ArtemisEntitySystemRef this, ArtemisEntityRef e)
{
    (ArtemisEntitySystemRef)this;
    (ArtemisEntityRef)e;
}

/**
 * Will check if the entity is of interest to this system.
 * @param e entity to check
 */
void ArtemisEntitySystemCheck(ArtemisEntitySystemRef this, ArtemisEntityRef e)
{
    if (this->dummy) return;

    bool contains = Get(ArtemisEntityGetSystemBits(e), (int)this->systemIndex);
    bool interested = true; // possibly interested, let's try to prove it wrong

    CFBitVectorRef componentBits = ArtemisEntityGetComponentBits(e);

    // Check if the entity possesses ALL of the components defined in the aspect.
    if (Size(this->allSet) > 0) {
        for (int i=0; i<Size(this->allSet); i++) {
            if (Get(this->allSet, i)) {
                if (!Get(componentBits, i)) {
                    interested = false;
                    break;
                }
            }
        }
    }

	// Check if the entity possesses ANY of the exclusion components, if it does then the system is not interested.
    if ((Size(this->exclusionSet) >= 0) && interested)  {
        bool any = false;
        for (int i=0; i<Size(this->exclusionSet); i++) {
            if (Get(this->exclusionSet, i)) {
                if (!Get(componentBits, i)) {
                    any = true;
                    break;
                }
            }
        }
        interested = any;
    }

	// Check if the entity possesses ANY of the components in the oneSet. If so, the system is interested.
    if ((Size(this->oneSet) >= 0))  {
        bool any = false;
        for (int i=0; i<Size(this->oneSet); i++) {
            if (Get(this->oneSet, i)) {
                if (!Get(componentBits, i)) {
                    any = true;
                    break;
                }
            }
        }
        interested = any;
    }

    if (interested && !contains) {
        ArtemisEntitySystemInsertToSystem(this, e);
    } else if (!interested && contains) {
        ArtemisEntitySystemRemoveFromSystem(this, e);
    }
}

void ArtemisEntitySystemRemoveFromSystem(ArtemisEntitySystemRef this, ArtemisEntityRef e)
{
    CFBagRemove(this->actives, e);
    Set(ArtemisEntityGetSystemBits(e), (int)this->systemIndex, false);
    ArtemisEntitySystemRemoved(this, e);
}

void ArtemisEntitySystemInsertToSystem(ArtemisEntitySystemRef this, ArtemisEntityRef e)
{
    CFBagAdd(this->actives, e);
    Set(ArtemisEntityGetSystemBits(e), (int)this->systemIndex, true);
    ArtemisEntitySystemInserted(this, e);
}

void ArtemisEntitySystemAdded(ArtemisEntitySystemRef this, ArtemisEntityRef e)
{
    ArtemisEntitySystemCheck(this, e);
}

void ArtemisEntitySystemChanged(ArtemisEntitySystemRef this, ArtemisEntityRef e)
{
    ArtemisEntitySystemCheck(this, e);
}

void ArtemisEntitySystemDeleted(ArtemisEntitySystemRef this, ArtemisEntityRef e)
{
    if (Get(ArtemisEntityGetSystemBits(e), (int)this->systemIndex)) {
        ArtemisEntitySystemRemoveFromSystem(this, e);
    }
}

void ArtemisEntitySystemDisabled(ArtemisEntitySystemRef this, ArtemisEntityRef e)
{
    if (Get(ArtemisEntityGetSystemBits(e), (int)this->systemIndex)) {
        ArtemisEntitySystemRemoveFromSystem(this, e);
    }
}

void ArtemisEntitySystemEnabled(ArtemisEntitySystemRef this, ArtemisEntityRef e)
{
    ArtemisEntitySystemCheck(this, e);
}

void ArtemisEntitySystemSetWorld(ArtemisEntitySystemRef this, ArtemisWorldRef world)
{
    this->world = world;
}

bool ArtemisEntitySystemIsPassive(ArtemisEntitySystemRef this)
{
    return this->passive;
}

void ArtemisEntitySystemSetPassive(ArtemisEntitySystemRef this, bool value)
{
    this->passive = value;
}

CFBagRef ArtemisEntitySystemGetActive(ArtemisEntitySystemRef this)
{
    return this->actives;
}

