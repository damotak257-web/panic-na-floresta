#include "panic_forest.hpp"

int main() {
    Tyra::Engine engine;
    PanicForestGame game(&engine);
    engine.run(&game);
    return 0;
}