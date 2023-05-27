#pragma once
#include <SFML/Graphics.hpp>
#include <array>

enum PieceColor {
	EMPTY,
	CYAN,
	BLUE,
	ORANGE,
	YELLOW,
	GREEN,
	PURPLE,
	RED
};

struct Piece
{
	std::array<std::array<int, 4>, 4> shape;
	sf::Vector2i loc;
	PieceColor color;
	sf::Vector2f center;
	int rotation;
};