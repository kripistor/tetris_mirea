#pragma once
#include <SFML/Graphics.hpp>
#include <array>

enum PieceColor {
	EMPTY,
	CYAN,	// I
	BLUE,	// J
	ORANGE, // L
	YELLOW, // O
	GREEN,  // S
	PURPLE, // T
	RED		// Z
};

struct Piece
{
	std::array<std::array<int, 4>, 4> shape;
	sf::Vector2i loc;
	PieceColor color;
	sf::Vector2f center;
	int rotation;
};