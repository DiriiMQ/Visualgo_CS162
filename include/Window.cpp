//
// Created by dirii on 23/03/2023.
//

#include "Window.hpp"

void Window::init() {
    this->relativeWindow = this->window;
    this->currentScene = constants::sceneVariables::MAIN_MENU_SCENE;

    // init buttons
    this->submenuButton = new Button(
            this->window,
            constants::submenuButtonPos,
            constants::sideButtonSize,
            ">",
            "<",
            15,
            sf::Color::Black,
            constants::normalGray,
            constants::hoverGray,
            constants::clickGray
            );

    this->demoCodeButton = new Button(
            this->window,
            constants::demoCodeButtonPos,
            constants::sideButtonSize,
            "<",
            ">",
            15,
            sf::Color::Black,
            constants::normalGray,
            constants::hoverGray,
            constants::clickGray
            );
}

void Window::initWindow() {
    this->videoMode.width = constants::Width;
    this->videoMode.height = constants::Height;
    this->window = new sf::RenderWindow(
            this->videoMode,
            constants::titleWindow,
            sf::Style::Titlebar | sf::Style::Close);

    this->window->setFramerateLimit(constants::fps);
}

Window::Window() {
    this->initWindow();
    this->initScenes();
    this->init();
}

const bool Window::running() const {
    return this->window->isOpen();
}

void Window::pollEvent() {
    // event polling
    while (this->window->pollEvent(this->event)) {
        switch (this->event.type) {
            case sf::Event::Closed:
                this->window->close();
                break;
            case sf::Event::KeyPressed:
                if (this->event.key.code == sf::Keyboard::Q) {
                    std::cout << "You have pressed Q!\n";
                }
                if (this->event.key.code == sf::Keyboard::W) {
                    std::cout << "You have pressed W!\n";
                }
                break;
            default:
                break;
        }

        if (this->submenuButton->pollEvent(this->mousePosView)) {
            std::cout << "You have clicked on submenu button!\n";
            this->scenes[this->currentScene]->isMenuOpen = (this->submenuButton->getTextString() == ">");
        }

        if (this->demoCodeButton->pollEvent(this->mousePosView)) {
            std::cout << "You have clicked on demo code button!\n";
            this->scenes[this->currentScene]->isDemoCodeOpen = (this->demoCodeButton->getTextString() == ">");
        }

        for (int i = 1; i < constants::sceneVariables::SCENE_COUNT; i++) {
            if (this->scenes[i]->modeButton->pollEvent(this->mousePosView)) {
                std::cout << "You have clicked on " << constants::sceneVariables::SCENE_NAMES[i] << " scene!\n";
                this->currentScene = static_cast<constants::sceneVariables::Scene>(i);
            }
        }

        this->scenes[this->currentScene]->pollEvent(this->mousePosView);
    }
}

void Window::update() {
    this->scenes[this->currentScene]->modeButton->setColor(constants::normalGray);

    this->updateMousePosition();
    this->pollEvent();

    this->submenuButton->update();
    this->demoCodeButton->update();
    this->scenes[this->currentScene]->modeButton->setColor(constants::hoverGreen);

    for (int i = 1; i < constants::sceneVariables::SCENE_COUNT; i++) {
        this->scenes[i]->modeButton->update();
    }

    this->scenes[this->currentScene]->update();
}

void Window::render() {
    /*
 * clear old frames
 * create objects
 * display it
 */

    this->window->clear(sf::Color::White);

    // drawing game
    this->submenuButton->render();
    this->demoCodeButton->render();
    for (int i = 1; i < constants::sceneVariables::SCENE_COUNT; i++) {
        this->scenes[i]->modeButton->render();
    }

    this->scenes[this->currentScene]->render();

    this->window->display();
}

void Window::initScenes() {
    this->scenes[constants::sceneVariables::MAIN_MENU_SCENE] = new MainMenu(this->window);
    this->scenes[constants::sceneVariables::SINGLY_LINKED_LIST_SCENE] = new SLLScene(this->window);
    this->scenes[constants::sceneVariables::DOUBLY_LINKED_LIST_SCENE] = new DLLScene(this->window);
    this->scenes[constants::sceneVariables::CIRCULAR_LINKED_LIST_SCENE] = new CLLScene(this->window);
    this->scenes[constants::sceneVariables::STACK_SCENE] = new StackScene(this->window);
    this->scenes[constants::sceneVariables::QUEUE_SCENE] = new QueueScene(this->window);
    this->scenes[constants::sceneVariables::STATIC_ARRAY_SCENE] = new StaticArrayScene(this->window);
    this->scenes[constants::sceneVariables::DYNAMIC_ARRAY_SCENE] = new DynamicArrayScene(this->window);

    for (int i = 1; i < constants::sceneVariables::SCENE_COUNT; i++) {
        this->scenes[i]->createModeButton(
                sf::Vector2f(
                        constants::modeButtonPos.x * static_cast<float>(i) +
                            (constants::distance2ModeButtons + constants::modeButtonSize.x) * static_cast<float>(i - 1),
                        constants::modeButtonPos.y
                        ),
                        constants::sceneVariables::NAME_MODE_BUTTON[i]
                );
    }
}
