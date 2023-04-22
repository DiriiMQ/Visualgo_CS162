//
// Created by dirii on 08/04/2023.
//

#ifndef VISUALGO_CS162_NODEINFO_HPP
#define VISUALGO_CS162_NODEINFO_HPP

#include "BaseDraw.hpp"
#include "SingleNode.hpp"
#include "Arrow.hpp"

class NodeInfo : public BaseDraw {
public:
    enum class ArrowType {
        LEFT,
        RIGHT
    };

    enum class StatusNode{
        InChain,
        OutChain,
        Visible
    };

    enum class TypeNode{
        Normal,
        Outside,
        Effective
    };

    NodeInfo(sf::RenderWindow* window, std::string value, sf::Vector2f position, bool _isDLL);
    ~NodeInfo();
    void updateNode();
    void updateArrows(ArrowType type, sf::Vector2f end);
    void render() override;

    void initArrow(ArrowType type, sf::Vector2f start, sf::Vector2f end);
    void destroyArrow(ArrowType type);

    void reInitPos(int index);
    void reInitPreVal();

    void setEffectivePosition(sf::Vector2f start);
    void setArrows(ArrowType type, sf::Vector2f start, sf::Vector2f end);
    void setValue(std::string value);

    sf::Vector2f getPosition();
    std::string getValue();

    void toggleActiveColorNode();
    void toggleActiveColorArrow(ArrowType type);

    void setPrintPreVal();
    void setPrintNormal();

    void setNodeInChain();
    void setNodeOutside();
    void setNodeVisible();

    void setTitle(const std::string& title);

    void hide(ArrowType type);
    void show(ArrowType type);

    StatusNode getStatusNode();
    
    void resetColorNode();
    void resetColorArrow(ArrowType type);
    void resetTitle();

    void reset();

private:
    sf::Vector2f positions[3];
    SingleNode* node;
    Arrow* arrows[2][2];
    std::string values[2];
    sf::Text title;

    StatusNode statusNode;
    bool isPrintPreVal, isDLL, isPrintNormal;
};

#endif //VISUALGO_CS162_NODEINFO_HPP
