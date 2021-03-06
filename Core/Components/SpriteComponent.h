#ifndef SPRITECOMPONENT_H
#define SPRITECOMPONENT_H

#include "GraphicsComponentBase.h"

#include "OutlineComponent.h"
#include "TransformComponent.h"
#include "../Animation/AnimatedSprite.hpp"

class SpriteComponent : public GraphicsComponentBase {
public:
	SpriteComponent(Entity* e, sol::table& componentTable);

	void setImageFilename(const std::string& filename) {
		this->_filename = filename;
		setTexture();
	}

	std::string getImageFilename() const {
		return _filename;
	}
	void render(sf::RenderWindow*, const sf::Time&);

	void changeAnimation(const std::string&);
	void playAnimation(const std::string&, float) {};

	sf::Vector2i getSize() const;

private:
	// Sprite details
	std::string _filename;
	sf::Texture* _texture;
	int _spriteWidth = 32;
	int _spriteHeight = 32;
	sf::Color _spriteColour;

	// Animations
	AnimatedSprite _animatedSprite;
	SPRAnimation _currentAnimation = SPRAnimation();
	std::map<std::string, SPRAnimation> _animationList;
	int _frameTime = 0;

	// Component links
	TransformComponent* _transform;
	OutlineComponent* _outline;
	float _outlineThickness;
	bool _noOutline;

	bool setTexture();
	void setAnimations(sol::table&);
	void drawOutline(sf::RenderWindow*);
};

#endif