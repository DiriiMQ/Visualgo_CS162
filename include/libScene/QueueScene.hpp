//
// Created by dirii on 29/03/2023.
//

#ifndef VISUALGO_CS162_QUEUESCENE_HPP
#define VISUALGO_CS162_QUEUESCENE_HPP

#include "BaseScene.hpp"
#include "MenuDataStructure.hpp"
#include "core/LinkedList.hpp"

/**
 * @brief Class for queue scene
 *
 */
class QueueScene : public BaseScene{
private:
    MenuDataStructure* menu;
    LinkedList* linkedList;

    /**
     * @brief Initialize the scene
     *
     */
    void init();

public:
    /**
     * @brief Construct a new Queue Scene object
     * @param window The window to render
     */
    explicit QueueScene(sf::RenderWindow* window);

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
     * @brief Generate the event animation for push mode
     *
     * @param chosenNode The chosen node
     * @return std::vector<EventAnimation> The event animation
     */
    std::vector<EventAnimation> pushModeEvents(int chosenNode);
    /**
     * @brief Generate the event animation for pop mode
     *
     * @param chosenNode The chosen node
     * @return std::vector<EventAnimation> The event animation
     */
    std::vector<EventAnimation> popModeEvents(int chosenNode);
};

#endif //VISUALGO_CS162_QUEUESCENE_HPP
