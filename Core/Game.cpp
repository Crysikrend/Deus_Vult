#include "Game.h"

Game::Game(sf::RenderWindow* window)
	:_window(window), _game(window) {}

void Game::init() {
	// Set up the view
	windowResized();

	// Set the game as the thing to display
	_currentScreen = &_game;
	_currentScreen->init();
}

void Game::windowResized() {
	// This function is called whenever the window is resized
	_view = sf::View(sf::FloatRect(0, 0, _window->getSize().x, _window->getSize().y));
	_window->setView(_view);
}

bool Game::update(const sf::Time& dTime) {
	return _currentScreen->update(dTime);
}

void Game::render(const sf::Time& dTime) {
	_currentScreen->render(dTime);
}

void Game::quit() {
	_game.quit();
}
