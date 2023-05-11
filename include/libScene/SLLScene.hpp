//
// Created by dirii on 26/03/2023.
//

#ifndef VISUALGO_CS162_SLLSCENE_HPP
#define VISUALGO_CS162_SLLSCENE_HPP

#include "BaseScene.hpp"
#include "MenuLinkedList.hpp"
#include "core/LinkedList.hpp"

/**
 * @brief Class for singly linked list scene
 *
 */
class SLLScene : public BaseScene {
private:
    MenuLinkedList* menu;
    LinkedList* linkedList;

    /**
     * @brief Initialize the scene
     *
     */
    void init();

public:
    /**
     * @brief Construct a new Singly Linked List Scene object
     * @param window The window to render
     */
    explicit SLLScene(sf::RenderWindow* window);

    /**
     * @brief Reset the scene
     *
     */
    void reset();

    /**
     * @brief Poll the event
     *
     * @param event The event
     * @param mousePosView The mouse position
     */
    void pollEvent(sf::Event event, sf::Vector2f mousePosView) override;
    /**
     * @brief Update the scene
     *
     */
    void update() override;
    /**
     * @brief Render the scene
     *
     */
    void render() override;

    /**
     * @brief Generate the event animation for add mode
     *
     * @param chosenNode The chosen node
     * @return std::vector<EventAnimation> The event animation
     */
    std::vector<EventAnimation> addModeEvents(int chosenNode);
    /**
     * @brief Generate the event animation for delete mode
     *
     * @param chosenNode The chosen node
     * @return std::vector<EventAnimation> The event animation
     */
    std::vector<EventAnimation> deleteModeEvents(int chosenNode);
    /**
     * @brief Generate the event animation for update mode
     *
     * @param chosenNode The chosen node
     * @return std::vector<EventAnimation> The event animation
     */
    std::vector<EventAnimation> updateModeEvents(int chosenNode);
    /**
     * @brief Generate the event animation for search mode
     *
     * @param chosenNode The chosen node
     * @return std::vector<EventAnimation> The event animation
     */
    std::vector<EventAnimation> searchModeEvents(int chosenNode);
};

#endif //VISUALGO_CS162_SLLSCENE_HPP
