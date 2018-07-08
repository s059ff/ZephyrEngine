#include "zephyr\test.h"

#include "zephyr.gamesystem\Entity.h"
#include "zephyr.gamesystem\EntityComponent.h"
#include "zephyr.gamesystem.components\TransformComponent.h"

using namespace zephyr;
using namespace zephyr::gamesystem;
using namespace zephyr::gamesystem::components;

class MyComponent : public EntityComponent
{
public:

    virtual void ReceiveMessage(const string& message, void* argument[]) override
    {
        test("Message", message, "My message");
        test("Argument", argument, (void*)nullptr);
    }
};

void main()
{
    Entity* e = Entity::Instantiate();
    test("EntityCount", Entity::EntityCount, 1);

    e->Attach<TransformComponent>();
    test("Attachment", e->Get<TransformComponent>()->Owner, e);

    EntityComponent* c = e->Detach<TransformComponent>();
    test("Detachment", (void*)c->Owner, (void*)nullptr);
    delete c;

    e->Name = "Kitty";
    test("Name", e->Name, "Kitty");
    test("Find(Name)", Entity::Find("Kitty"), e);

    Entity* e2 = Entity::Instantiate();
    e2->Attach<TransformComponent>();
    e2->Attach<MyComponent>();

    Entity::BroadcastMessage("My message");
}
