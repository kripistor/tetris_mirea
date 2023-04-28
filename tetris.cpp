#include <iostream>
#include <string>
#include "tetris.h"

Tetris::Tetris()
	:
	window(sf::VideoMode(550, 550), "Tetris"),
	rng(rd()),
	dist(0, 6),
	game_over( false )
{
	reset();
	set_next_piece();
	set_piece();
	next_piece_board.set_wall_color(sf::Color::Transparent);
	if (!font.loadFromFile("fonts/Squarewave.ttf")){
        std::cerr << "failed font\n";
    }

	highscore.text.setFont(font);
	highscore.text.setString("Score");
	highscore.text.setPosition({ 400,50 });

	highscore.cur_score.setFont(font);
	highscore.cur_score.setCharacterSize(50);
	highscore.cur_score.setPosition({ 415,80 });
	highscore.score = 0;

	game_over_msg.setFont(font);
	game_over_msg.setString("Game Over!");
	game_over_msg.setPosition({ 250,250 });

	next_shape_msg.setFont(font);
	next_shape_msg.setString("Next Shape");
	next_shape_msg.setPosition({ 375,300 });

	trans.scale({ 0.5,0.5 });
	trans.translate(675, 750);
}

void Tetris::run()
{
	sf::Clock clock;
	sf::Time time_since_last_update = sf::Time::Zero;
	while (window.isOpen())
	{
		process_events();
		time_since_last_update += clock.restart();
		while (time_since_last_update > time_per_frame)
		{
			time_since_last_update -= time_per_frame;
			process_events();
			update();
		}
		render();
	}
}

void Tetris::process_events()
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window.close();

		else if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Right)
			{
				piece.loc.x++;
				if (board.collides(piece))
					piece.loc.x--;
			}

			else if (event.key.code == sf::Keyboard::Left)
			{
				piece.loc.x--;
				if (board.collides(piece))
					piece.loc.x++;
			}

			else if (event.key.code == sf::Keyboard::Down)
			{
				piece.loc.y++;
				if (board.collides(piece))
					piece.loc.y--;
			}

			else if (event.key.code == sf::Keyboard::Up)
			{
				piece.rotation = (piece.rotation + 1) % 4;
				if (board.collides(piece))
				{
					piece.loc.x -= 1;
					if (board.collides(piece))
						piece.loc.x += 2;
					if (board.collides(piece))
					{
						piece.loc.x -= 1;
						piece.rotation = (piece.rotation - 1) & 3;
					}
				}
			}
		}
	}
}

void Tetris::update()
{
	timer -= 100;
	if (timer == 0)
	{
		piece.loc.y++;
		timer = 1500;
	}
	
	if (board.collides(piece))
	{
		piece.loc.y--;
		board.add_piece(piece);
		set_piece();
	}
	board.clear_row();

	highscore.score = board.get_count_score();
	highscore.cur_score.setString(std::to_string(highscore.score));
}

void Tetris::render()
{
	window.clear();

	if (!game_over)
	{
		board.add_piece(piece);
		next_piece_board.add_piece(next_piece);
		window.draw(board);
		window.draw(next_piece_board, trans);
		window.draw(highscore.text);
		window.draw(highscore.cur_score);
		window.draw(next_shape_msg);
		board.remove_piece(piece);
		next_piece_board.remove_piece(next_piece);
	}
	else
		window.draw(game_over_msg);

	window.display();
}

void Tetris::set_piece()
{
	piece = next_piece;
	set_next_piece();

	if (board.collides(piece))
		game_over = true;
}

void Tetris::set_next_piece()
{
	next_piece = pieces[dist(rng)];
}

void Tetris::reset()
{
	pieces[0] = { { {{1,1,1,1},{0,0,0,0},{0,0,0,0},{0,0,0,0}} }, sf::Vector2i(5,0), PieceColor::CYAN, {1.f,0.f},0 };
	pieces[1] = { { {{1,0,0,0},{1,1,1,0},{0,0,0,0},{0,0,0,0}} }, sf::Vector2i(5,0), PieceColor::BLUE, {0.f,1.f},0 };
	pieces[2] = { { {{0,0,0,1},{0,1,1,1},{0,0,0,0},{0,0,0,0}} }, sf::Vector2i(5,0), PieceColor::ORANGE, {3.f,1.f},0 };
	pieces[3] = { { {{1,1,0,0},{1,1,0,0},{0,0,0,0},{0,0,0,0}} }, sf::Vector2i(5,0), PieceColor::YELLOW, {0.5,0.5},0 };
	pieces[4] = { { {{0,0,1,1},{0,1,1,0},{0,0,0,0},{0,0,0,0}} }, sf::Vector2i(5,0), PieceColor::GREEN, {2.f,1.f},0 };
	pieces[5] = { { {{0,1,0,0},{1,1,1,0},{0,0,0,0},{0,0,0,0}} }, sf::Vector2i(5,0), PieceColor::PURPLE, {1.f,0.f},0 };
	pieces[6] = { { {{1,1,0,0},{0,1,1,0},{0,0,0,0},{0,0,0,0}} }, sf::Vector2i(5,0), PieceColor::RED, {1.f,0.f},0 };
}


