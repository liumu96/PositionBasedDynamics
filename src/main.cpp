#include <iostream>

int main()
{
    try
    {
        // todo
        /**
         * 1. init the window
         * 2. init the scene: including the simulating object
         * 3. setting the iteration loop
         * 4. solver for animation
         */
        return 0;
    }
    catch (const std::runtime_error &e)
    {
        std::cout << "Exception caught: " << e.what() << std::endl;
        return -1;
    }
    std::cout << "Position Based Dynamics" << std::endl;
}