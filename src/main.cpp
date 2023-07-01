#include <iostream>
#include <memory>
#include "Game/Application.hpp"

class MyApp : public Game::Application
{
    virtual void on_update() override
    {
        std::cout << "Update frame: " << frame++ << std::endl;
    }

    int frame = 0;
};

int main(int argc, char** argv)
{
    auto myApp = std::make_unique<MyApp>();

    int returnCode = myApp->start(1000, 1000, "Civilization", argv);

    return returnCode;
}