#include "GraphicsComponent.h"
#include <sol.hpp>

#include "Entity.h"

GraphicsComponent::GraphicsComponent(Entity* e, sol::table& componentTable) : Component(e) {
	_transform = _owner->get<TransformComponent>();

	auto filenameRef = componentTable["filename"];
	if (filenameRef.valid()) {
		_filename = filenameRef;
		_filename = "Data/" + _filename;

		if (componentTable["size"][1])
			_spriteWidth = componentTable["size"][1];

		if (componentTable["size"][2])
			_spriteHeight = componentTable["size"][2];

		_animatedSprite.setOrigin(_spriteWidth / 2, _spriteHeight / 2);

		if (!setTexture())
			return;

		sol::table animations = componentTable["animations"];
		if (animations) {
			setAnimations(animations);

			changeAnimation(_animationList.begin()->first);
			auto animRef = componentTable["defaultAnim"];
			if (animRef.valid())
				changeAnimation(animRef);
			else {
				printf("No valid default animation, using %s.\n", _animationList.begin()->first.c_str());
			}
		}
		else {
			_frameTime = 0;
			Animation animation;
			animation.setSpriteSheet(_texture);
			animation.addFrame(sf::IntRect(0, 0, _spriteWidth, _spriteHeight));
			_animationList["default"] = animation;
			changeAnimation("default");
		}

	}
	else {
		printf("Error, GraphicsComponent.filename is not a string!\n");
	}
}

void GraphicsComponent::render(sf::RenderWindow* window, const sf::Time& dTime) {
	if (_transform) {
		if (_frameTime > 0) {
			_animatedSprite.update(dTime);
		}

		_animatedSprite.setScale((!_transform->_flipX * 2 - 1) * _transform->_scale.x, (!_transform->_flipY * 2 - 1) * _transform->_scale.y);

		_outline = sf::Color(255, 0, 0, 100);
		_outlineThickness = 5;

		if (_outlineThickness > 0 && _outline.a > 0) {
			_animatedSprite.setColor(sf::Color(255, 0, 0, 100));

			_animatedSprite.setPosition(_transform->_position.x + _outlineThickness, _transform->_position.y);
			window->draw(_animatedSprite);

			_animatedSprite.setPosition(_transform->_position.x - _outlineThickness, _transform->_position.y);
			window->draw(_animatedSprite);

			_animatedSprite.setPosition(_transform->_position.x, _transform->_position.y + _outlineThickness);
			window->draw(_animatedSprite);

			_animatedSprite.setPosition(_transform->_position.x, _transform->_position.y - _outlineThickness);
			window->draw(_animatedSprite);
		}

		_animatedSprite.setColor(sf::Color(255, 255, 255, 255));
		_animatedSprite.setPosition(_transform->_position);
		window->draw(_animatedSprite);

		return;
	}

	// if there's no transform component, try again
	_transform = _owner->get<TransformComponent>();
}

void GraphicsComponent::changeAnimation(const std::string& animName) {
	if (_animationList.count(animName)) {
		if (_animationList[animName] != _currentAnimation) {
			// If the animation is new, restart it (so attacks and jumps aren't screwed)
			_currentAnimation = _animationList[animName];
			_frameTime = _currentAnimation._frameTime;
			_animatedSprite.setFrameTime(sf::milliseconds(_frameTime));
			_animatedSprite.stop();
			_animatedSprite.play(_currentAnimation);
			//printf("%s: Animation changed to: %s.\n", _owner->getType().c_str(), animName.c_str());
		}
		return;
	}

	printf("No animations with %s found.\n", animName.c_str());
}

void GraphicsComponent::setAnimations(sol::table & animationTable) {
	for (auto key_value_pair : animationTable) {
		std::string animationName = key_value_pair.first.as<std::string>();
		sol::object& value = key_value_pair.second;
		sol::table detailsTable = value.as<sol::table>();

		float frameTime = 0;

		if (detailsTable["frameTime"])
			frameTime = detailsTable["frameTime"];

		sol::table frameTable = detailsTable["animation"];

		Animation animation = Animation(frameTime);
		animation._name = animationName;
		animation.setSpriteSheet(_texture);

		for (int i = frameTable.size(); i > 0; i--) {
			std::pair<sol::object, sol::object> table = frameTable[i];
			sf::IntRect frame;
			sol::table position = table.second.as<sol::table>();
			frame = sf::IntRect( position[1], position[2], _spriteWidth, _spriteHeight);
			animation.addFrame(frame);
		}

		_animationList[animationName] = animation;
	}
}

bool GraphicsComponent::setTexture(){
	if (_texture.loadFromFile(_filename)){
		return true;
	}

	printf("Error, could not load %s!\n", _filename.c_str());
	return false;
}