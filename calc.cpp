

#include <iostream>
#include <SFML\Graphics.hpp>
#include <fstream>

const std::map<std::string, float> loadData()
{
	std::ifstream file("data.txt");
	std::map<std::string, float> data;
	std::string key;
	while (file >> key)
	{
		key = key.substr(0, key.size() - 1);
		std::transform(key.begin(), key.end(), key.begin(), ::tolower);
		float value; file >> value;
		data[key] = value;
	}
	return data;
}

const std::vector<int> loadSequence()
{
	std::ifstream file("dir-sequence.txt");
	std::vector<int> seq;

	std::string dir;
	while (file >> dir)
	{
		if (dir[0] == '/') break;
		seq.push_back(std::stoi(dir));
	}
	return seq;
}

namespace
{
	std::map<std::string, float> data = loadData();
	const std::vector<int> DIR_SEQUENCE = loadSequence();
	const int DIRS = DIR_SEQUENCE.size();
	const int WIDTH = data["width"], HEIGHT = data["height"];
	const float CELL_SIZE = data["cellsize"];
}

const float FRAME_DURATION = 1.f / 60;

//https://stackoverflow.com/questions/1838656/how-do-i-represent-a-hextile-hex-grid-in-memory

std::vector<char> grid(WIDTH*HEIGHT);
std::vector<sf::Color> colors(DIRS);
sf::RenderWindow window(sf::VideoMode(WIDTH * (CELL_SIZE + 1) + 1, HEIGHT * (CELL_SIZE + 1) + 1), "Langton's Ant");
sf::VertexArray cells(sf::Quads);

const int index(const int &x, const int &y) { return y * WIDTH + x; }

void updateGrid()
{
	cells.clear();
	for (int y = 0; y < HEIGHT; y++)
		for (int x = 0; x < WIDTH; x++)
		{
			const sf::Color color = colors[grid[index(x, y)]];
			const sf::Vector2f upperLeft(1 + x*(CELL_SIZE + 1), 1 + y*(CELL_SIZE + 1));
			cells.append(sf::Vertex(upperLeft, color));
			cells.append(sf::Vertex(upperLeft + sf::Vector2f(CELL_SIZE, 0.f), color));
			cells.append(sf::Vertex(upperLeft + sf::Vector2f(CELL_SIZE, CELL_SIZE), color));
			cells.append(sf::Vertex(upperLeft + sf::Vector2f(0.f, CELL_SIZE), color));
		}
}

enum Direction { Up = 0, Right, Down, Left };


int main()
{
	std::srand(std::time(nullptr));
	sf::Vector2u position(WIDTH / 2, HEIGHT / 2);
	int direction = Up;
	bool withinBounds = true;
	int totalMoves = 0;

	colors[0] = sf::Color(20, 20, 20);
	for (int i = 1; i < DIRS; i++) colors[i] = sf::Color(std::rand() % 256 + 1, std::rand() % 256 + 1, std::rand() % 256 + 1);

	while (withinBounds)
	{
		totalMoves++;
		char &color = grid[index(position.x, position.y)];

		direction += DIR_SEQUENCE[color];
		if (direction > Left) direction %= 4;
		if (direction < Up) direction = 4 + direction % 4;

		color++;
		if (color >= DIRS) color = 0;

		switch (direction)
		{
		case Up: position.y--; break;
		case Right: position.x++; break;
		case Down: position.y++; break;
		case Left: position.x--; break;
		}

		if (position.x < 0.f || position.x >= WIDTH || position.y < 0.f || position.y >= HEIGHT)
		{
			withinBounds = false;
			break;
		}
	}

	std::cout << "\nDone calculating! " << totalMoves << " moves";
	updateGrid();
	while (window.isOpen())
	{
		sf::Event evnt;
		if (window.pollEvent(evnt) && evnt.type == sf::Event::Closed)
			window.close();

		window.clear(sf::Color::Black);
		window.draw(cells);
		window.display();
	}

	return 0;
}