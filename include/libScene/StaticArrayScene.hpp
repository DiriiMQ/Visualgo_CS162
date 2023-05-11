//
// Created by dirii on 27/03/2023.
//

#ifndef VISUALGO_CS162_STATICARRAYSCENE_HPP
#define VISUALGO_CS162_STATICARRAYSCENE_HPP

#include "BaseScene.hpp"
#include "MenuArray.hpp"
#include "core/Array.hpp"

/**
 * @brief Class for static array scene
 *
 */
class StaticArrayScene : public BaseScene{
private:
    MenuArray* menu;
    Array* array;

    /**
     * @brief Initialize the scene
     *
     */
    void init();

public:
    /**
     * @brief Construct a new Static Array Scene object
     * @param window The window to render
     */
    explicit StaticArrayScene(sf::RenderWindow* window);

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

#endif //VISUALGO_CS162_STATICARRAYSCENE_HPP
