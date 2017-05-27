#ifndef GRAPHICSCOMPONENT_H
#define GRAPHICSCOMPONENT_H

#include <string>
#include "Scripts.h"
#include "Component.h"
#include "SFML\Graphics.hpp"

#include "AnimatedSprite.hpp"

class GraphicsComponent : public Component {
public:
	GraphicsComponent(Entity* e, sol::table& componentTable);

	void setImageFilename(const std::string& filename) {
		this->_filename = filename;
		setTexture();
	}

	std::string getImageFilename() const {
		return _filename;
	}
	bool _flipX = false;

	void render(sf::RenderWindow*, const sf::Time&, const sf::Vector2f&);

	void changeAnimation(const std::string&);

private:
	std::string _filename;
	sf::Texture _texture;

	int _frameTime = 0;

	AnimatedSprite _animatedSprite;
	Animation& _currentAnimation = Animation();
	std::map<std::string, Animation> _animationList;

	int _spriteWidth;
	int _spriteHeight;

	bool setTexture();
	void setAnimations(sol::table&);

};

#endif