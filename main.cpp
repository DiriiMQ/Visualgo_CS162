#include "Window.hpp"

int main() {
    Window window;

    while (window.running()) {
        window.update();

        window.render();
    }

    return 0;
}
