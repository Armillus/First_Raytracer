#include "Core.hpp"

int main(int argc, const char **argv)
{
    try {
        rt::Core core(argc, argv);
        return (core.run());
    } catch (const std::exception &) {
        return 1;
    }
}