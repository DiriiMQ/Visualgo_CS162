//
// Created by dirii on 23/03/2023.
//

#ifndef VISUALGO_CS162_CONSTANTS_HPP
#define VISUALGO_CS162_CONSTANTS_HPP

#include <SFML/Graphics.hpp>

// create struct node for circular linked list
struct Node {
    int data;
    struct Node *next;
};

namespace constants{
    namespace sceneVariables {
        constexpr int SCENE_COUNT = 8;
        enum Scene {
            MAIN_MENU_SCENE,
            SINGLY_LINKED_LIST_SCENE,
            DOUBLY_LINKED_LIST_SCENE,
            CIRCULAR_LINKED_LIST_SCENE,
            STACK_SCENE,
            QUEUE_SCENE,
            STATIC_ARRAY_SCENE,
            DYNAMIC_ARRAY_SCENE,
        };
        constexpr char SCENE_NAMES[SCENE_COUNT][50] = {
                "Main Menu",
                "Singly Linked List",
                "Doubly Linked List",
                "Circular Linked List",
                "Stack",
                "Queue",
                "Static Array",
                "Dynamic Array",
        };
        constexpr char NAME_MODE_BUTTON[SCENE_COUNT][50] = {
            "Main Menu",
            "SLL",
            "DLL",
            "CLL",
            "Stack",
            "Queue",
            "Static Array",
            "Dynamic Array"
        };
    }

    namespace MenuLinkedList {
        constexpr int BUTTON_COUNT = 5;
        enum Button {
            CREATE_BUTTON,
            ADD_BUTTON,
            DELETE_BUTTON,
            UPDATE_BUTTON,
            SEARCH_BUTTON,
            NONE
        };
        constexpr char BUTTON_NAMES[BUTTON_COUNT][50] = {
                "Create",
                "Add",
                "Delete",
                "Update",
                "Search"
        };
        constexpr int BUTTON_NAME_SIZE = 15;

        namespace CreateMode {
            constexpr int BUTTON_COUNT = 3;
            enum Button {
                RANDOM_BUTTON,
                DEFINED_LIST_BUTTON,
                FILE_BUTTON,
                NONE
            };
            constexpr char BUTTON_NAMES[BUTTON_COUNT][50] = {
                    "Random",
                    "Defined List",
                    "File"
            };
            constexpr int NAME_SIZE = 15;

            constexpr int TEXTBOX_COUNT = 2;
            constexpr char TEXTBOX_NAMES[2][50] = {
                    "Amount = ",
                    "List = "
            };

            constexpr int TEXTBOX_LENGTH[2] = {
                    2,
                    30 // for input a defined list
            };
        }
    }

    // information of window
    static int Width = 1760,
            Height = 992;
    constexpr char titleWindow[] = "Visualgo CS162 - Phan Minh Quang";
    static int fps = 144;

    constexpr char fontPath[] = "../assets/fonts/OpenSans.ttf";

    // colors
    static sf::Color normalGreen = sf::Color(0, 255, 0),
                        hoverGreen = sf::Color(0, 200, 0),
                        clickGreen = sf::Color(0, 150, 0);

    static sf::Color normalGray = sf::Color(200, 200, 200),
                        hoverGray = sf::Color(150, 150, 150),
                        clickGray = sf::Color(100, 100, 100);

    // positions of buttons
    static sf::Vector2f submenuButtonPos = sf::Vector2f(0, 700),
                        demoCodeButtonPos = sf::Vector2f(1736, 700),
                        modeButtonPos = sf::Vector2f(10, 10);

    // size of buttons
    static sf::Vector2f sideButtonSize = sf::Vector2f(24, 200),
                        modeButtonSize = sf::Vector2f(150, 40),
                        optionButtonSize = sf::Vector2f(100, sideButtonSize.y / static_cast<float>(5) - 1),
                        goButtonSize = sf::Vector2f(50, 30);
    static float distance2ModeButtons = 10;

    // size text of buttons
    static int sizeTextModeButton = 15;

    // rounding button
    static int CORNER_POINT_COUNT_BUTTON = 15,
                CORNER_RADIUS_BUTTON = 5;
}

#endif //VISUALGO_CS162_CONSTANTS_HPP
