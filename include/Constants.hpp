//
// Created by dirii on 23/03/2023.
//

#ifndef VISUALGO_CS162_CONSTANTS_HPP
#define VISUALGO_CS162_CONSTANTS_HPP

#include <SFML/Graphics.hpp>

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
        namespace AddMode{
            constexpr int TEXTBOX_COUNT = 2;
            constexpr char TEXTBOX_NAMES[2][50] = {
                    "Position = ",
                    "Value = "
            };
            constexpr int TEXTBOX_LENGTH[2] = {
                    2,
                    2
            };
            enum Textbox{
                POSITION_TEXTBOX,
                VALUE_TEXTBOX,
                NONE
            };
        }
        namespace DeleteMode{
            constexpr int TEXTBOX_COUNT = 1;
            constexpr char TEXTBOX_NAME[50] = "Position = ";
            constexpr int TEXTBOX_LENGTH = 2;
            enum Textbox{
                POSITION_TEXTBOX,
                NONE
            };
        }
        namespace UpdateMode{
            constexpr int TEXTBOX_COUNT = 2;
            constexpr char TEXTBOX_NAMES[2][50] = {
                    "Position = ",
                    "Value = "
            };
            constexpr int TEXTBOX_LENGTH[2] = {
                    2,
                    2
            };
            enum Textbox{
                POSITION_TEXTBOX,
                VALUE_TEXTBOX,
                NONE
            };
        }
        namespace SearchMode{
            constexpr int TEXTBOX_COUNT = 1;
            constexpr char TEXTBOX_NAME[50] = "Value = ";
            constexpr int TEXTBOX_LENGTH = 2;
            enum Textbox{
                VALUE_TEXTBOX,
                NONE
            };
        }
    }

    namespace NodeInfo{
        static float radius = 30,
                    outlineThickness = 2;
        static int pointCount = 200,
                    fontSize = 20;
        static sf::Vector2f originNode(100, 300);
        static float offsetX = 151;
    }

    namespace Arrow{
        static sf::Vector2i sizeArrow(752, 214),
                            sizeRectangle(192, 37);
        static sf::Vector2f defaultScaleArrow(0.2f, 0.2f),
                            defaultScaleRectangle(0.6f, 0.21f);
    }

    namespace ControlMenu{
        enum class Button{
            PREVIOUS,
            PLAY,
            NEXT,
            SPEED_DOWN,
            SPEED_UP,
            None
        };

        constexpr int BUTTON_COUNT = 5,
                        BUTTON_NAME_SIZE = 15,
                        TEXT_SIZE = 15;
        constexpr char BUTTON_NAMES[BUTTON_COUNT][50] = {
                "<",
                "[=]",
                ">",
                "<<",
                ">>"
        };

        static sf::Vector2f buttonSize(50, 50);
        static float coordinateY = 930,
                    middleX = 1760 / 2.0f,
                    leftX = 1760 / 7.0f;
        static sf::Vector2f buttonPos[5] = {
                sf::Vector2f(middleX - 2 * buttonSize.x, coordinateY),
                sf::Vector2f(middleX, coordinateY),
                sf::Vector2f(middleX + 2 * buttonSize.x, coordinateY),
                sf::Vector2f(leftX, coordinateY),
                sf::Vector2f(leftX + 3 * buttonSize.x, coordinateY)
        };
    }

    // information of window
    static int Width = 1760,
            Height = 992;
    constexpr char titleWindow[] = "Visualgo CS162 - Phan Minh Quang";
    static int fps = 144;

    constexpr char fontPath[] = "../assets/fonts/Hack_reg.ttf";

    // colors
    static sf::Color normalGreen(0, 255, 0),
                        hoverGreen(0, 200, 0),
                        clickGreen(0, 150, 0);

    static sf::Color normalGray(200, 200, 200),
                        hoverGray(150, 150, 150),
                        clickGray(100, 100, 100);

    static sf::Color normalOrange(255, 145, 77);

    // positions of buttons
    static sf::Vector2f submenuButtonPos = sf::Vector2f(0, 730),
                        demoCodeButtonPos = sf::Vector2f(1736, 730),
                        modeButtonPos = sf::Vector2f(10, 10);

    // size of buttons
    static sf::Vector2f sideButtonSize = sf::Vector2f(24, 200),
                        modeButtonSize = sf::Vector2f(150, 40),
                        optionButtonSize = sf::Vector2f(130, sideButtonSize.y / static_cast<float>(5) - 1),
                        goButtonSize = sf::Vector2f(50, 30);
    static float distance2ModeButtons = 10;

    // size text of buttons
    static int sizeTextModeButton = 15;

    // rounding button
    static int CORNER_POINT_COUNT_BUTTON = 15;
    static float CORNER_RADIUS_BUTTON = 5;
}

#endif //VISUALGO_CS162_CONSTANTS_HPP
