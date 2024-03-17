#include "zephyr.gamesystem\Entity.h"
#include "zephyr.gamesystem\EntityComponent.h"
#include "zephyr.gamesystem.components\TransformComponent.h"

#include "test.h"

using namespace zephyr;
using namespace zephyr::gamesystem;
using namespace zephyr::gamesystem::components;

class FruitComponent : public EntityComponent
{
public:

    FruitComponent()
    {
        instance_count++;
    }

    virtual ~FruitComponent() override
    {
        instance_count--;
    }

    virtual void ReceiveMessage(const string& message, void* arguments[]) override
    {
        test("Entity::BroadcastMessage -> message", message, "update");
        test("Entity::BroadcastMessage -> argument", *(int*)(arguments[0]), 200);
    }

public:
    int value;
    static int instance_count;
};

int FruitComponent::instance_count = 0;

void test_entity_instantiate()
{
    test("Entity::EntityCount", Entity::EntityCount, 0);
    Entity* e = Entity::Instantiate();
    test("Entity::EntityCount", Entity::EntityCount, 1);
    Entity::Kill(e);
    Entity::Update();
    test("Entity::EntityCount", Entity::EntityCount, 0);
    test("EntityComponent memory leak check", FruitComponent::instance_count, 0);
}

void test_entity_attach_detach()
{
    Entity* e = Entity::Instantiate();
    EntityComponent* c = e->Attach(new FruitComponent());
    test("Entity::Attach()", e->Get<FruitComponent>(), c);
    test("EntityComponent::Owner", c->Owner, e);
    test("Entity::Detach()", e->Detach<FruitComponent>(), c);
    test("EntityComponent::Owner", c->Owner, (Entity*)nullptr);
    delete c;

    Entity::Clear();
    test("Entity::EntityCount", Entity::EntityCount, 0);
    test("EntityComponent memory leak check", FruitComponent::instance_count, 0);
}

void test_entity_broadcast_message()
{
    Entity* e = Entity::Instantiate();
    e->Attach<FruitComponent>();

    int value = 200;
    void* args[] = { &value };
    Entity::BroadcastMessage("update", args);

    Entity::Clear();
    test("Entity::EntityCount", Entity::EntityCount, 0);
    test("EntityComponent memory leak check", FruitComponent::instance_count, 0);
}

void test_entity_find()
{
    Entity* e1 = Entity::Instantiate();
    Entity* e2 = Entity::Instantiate();
    FruitComponent* c1 = (FruitComponent*)e1->Attach(new FruitComponent());
    FruitComponent* c2 = (FruitComponent*)e2->Attach(new FruitComponent());
    c1->value = 100;
    c2->value = 200;

    auto pred = [](Entity* e) { return e->Get<FruitComponent>()->value == 200; };
    test("Entity::Find(pred)", Entity::Find(pred), e2);

    Entity::Clear();
    test("Entity::EntityCount", Entity::EntityCount, 0);
    test("EntityComponent memory leak check", FruitComponent::instance_count, 0);
}
