#include "board.h"

Board::Board(): color_wall{128,128,128}
{
	cell_color[PieceColor::EMPTY]  =	sf::Color::Black;
	cell_color[PieceColor::CYAN]   =	sf::Color::Cyan;
	cell_color[PieceColor::BLUE]   =	sf::Color::Blue;
	cell_color[PieceColor::ORANGE] =	{ 255, 165, 0 };
	cell_color[PieceColor::YELLOW] =    sf::Color::Yellow;
	cell_color[PieceColor::GREEN]  =	sf::Color::Green;
	cell_color[PieceColor::GREEN]  =	sf::Color::Green;
	cell_color[PieceColor::PURPLE] =    { 128, 0, 128 };
	cell_color[PieceColor::RED]    =	sf::Color::Red;
}

void Board::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	sf::RectangleShape rect(sf::Vector2f(cell_size, cell_size));

	for (int x = 0; x < columns; x++)
	{
		for (int y = 0; y < rows; y++)
		{
			if (x == 0 || x == columns - 1 || y == rows - 1)
			{
				rect.setOutlineThickness(0.f);
				rect.setFillColor(color_wall);
			}
			else 
			{
				rect.setOutlineColor(sf::Color::Black);
				rect.setOutlineThickness(-1.f);
				rect.setFillColor(cell_color[grid[x][y]]);
			}
		
			rect.setPosition(x * cell_size, y * cell_size);	
			target.draw(rect, states);
		}
	}
}

void Board::add_piece(const Piece& piece)
{
	for (int x = 0; x < 4; x++){
		for (int y = 0; y < 4; y++)
		{
			if (!piece.shape[y][x]) continue;

			const sf::Vector2i piece_coord{ x, y };
			const sf::Vector2i board_coord = piece_coord_to_board_coord(piece_coord, piece);

			grid[board_coord.x][board_coord.y] = piece.color;
		}
	}
}

void Board::remove_piece(const Piece& piece)
{
	for (int x = 0; x < 4; x++)
	{
		for (int y = 0; y < 4; y++)
		{
			if (!piece.shape[y][x]) continue;

			const sf::Vector2i piece_coord{ x, y };
			const sf::Vector2i board_coord = piece_coord_to_board_coord(piece_coord, piece);

			grid[board_coord.x][board_coord.y] = PieceColor::EMPTY;
		}
	}
}

bool Board::collides(const Piece& piece) const
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (piece.shape[j][i] != 0)
			{
				const sf::Vector2i piece_coord{ i, j };
				const sf::Vector2i board_coord = piece_coord_to_board_coord(piece_coord, piece);
				
				const int y = board_coord.y;
				const int x = board_coord.x;

				if (y < 0 || y == rows - 1 || x < 1 || x == columns - 1)
					return true;

				// collision with existing pieces
				if (grid[x][y] != PieceColor::EMPTY)
					return true;
			}
		}
	}
	return false;
}

sf::Vector2i Board::rotate(const sf::Vector2i& piece_coord, const sf::Vector2f& center, const int rotation) const
{
	sf::Vector2f relative_center = sf::Vector2f(piece_coord) - center;
	float temp;
	
	switch (rotation)
	{
	case 0:	// 0
		break;
	case 1:	// 90
		temp = relative_center.x;
		relative_center.x = -relative_center.y;
		relative_center.y = temp;
		break;
	case 2:	// 180
		relative_center.x = -relative_center.x;
		relative_center.y = -relative_center.y;
		break;
	case 3:	// 270
		temp = -relative_center.x;
		relative_center.x = relative_center.y;
		relative_center.y = temp;
		break;
	}
	return sf::Vector2i(relative_center + center);
}

sf::Vector2i Board::piece_coord_to_board_coord(const sf::Vector2i& piece_coord, const Piece& piece) const
{
	return piece.loc + rotate(piece_coord, piece.center, piece.rotation);
}

void Board::clear_row()
{
	for (int row = rows - 1; row >= 0; row--)
	{
		if (is_full(row))
		{
			count_score++;
			for (int column = 1; column < columns - 1; column++)
			{
				grid[column][row] = PieceColor::EMPTY;
			}
			drop_row(row);
		}
	}
}

bool Board::is_full(int row) const
{
	for (int column = 1; column < columns - 1; column++)
	{
		if (grid[column][row] == PieceColor::EMPTY)
		{
			return false;
		}
	}
	return true;
}

void Board::drop_row(int _row)
{
	for (int column = 1; column < columns - 1; column++)
	{
		for (int row = _row; row > 0; row--)
		{
			grid[column][row] = grid[column][row - 1];
			grid[column][row - 1] = PieceColor::EMPTY;
		}
	}
}

void Board::set_wall_color(const sf::Color& color)
{
	color_wall = color;
}








