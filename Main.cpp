#include "Test/ParticleTest.h"
#include "Test/ForceTest.h"
#include "Test/JointTest.h"
#include "Test/CollisionTest.h"

int main(int argc, char* argv[])
{
    Test* test = new CollisionTest();

    test->Initialize();

    while (!test->IsQuit())
    {
        test->Run();
    }

    delete test;

    return 0;
}