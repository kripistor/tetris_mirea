#pragma once
#include <SFML/Graphics.hpp>
#include <random>
#include "board.h"
#include "piece.h"

class Tetris
{
public:
	Tetris();
	void run();

private:
	void process_events();
	void update();
	void render();

	void set_piece();
	void set_next_piece();
	void reset();

private:
	sf::RenderWindow window;
	std::array<Piece, 7> pieces;
	Board board;
	Board next_piece_board;
	Piece piece;
	Piece next_piece;
	sf::Transform trans;

	std::random_device rd;
	std::mt19937 rng;
	std::uniform_int_distribution<int> dist;
	
	const sf::Time time_per_frame = sf::seconds(1.f / 60.f);
	double timer = 1500;

	struct Highscore {
		sf::Text text;
		sf::Text cur_score;
		int score;
	};
	Highscore highscore;
	sf::Font font;
	sf::Text game_over_msg;
	sf::Text next_shape_msg;

	bool game_over;
};