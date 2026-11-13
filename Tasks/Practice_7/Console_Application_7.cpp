#include <SFML/Graphics.hpp>
using namespace sf;

int main()
{
    // Создаём окно 400×400 (ВАШ КОД)
	RenderWindow window(VideoMode(400, 400), "SFML matrix");

    while (window.isOpen())
    {
        const int cellSize = 80;
        const int gridSize = 5;

        // Массив для хранения ячеек
        RectangleShape cells[gridSize][gridSize];

        // Инициализируем ячейки вложенными циклами
        for (int i = 0; i < gridSize; ++i)
        {
            for (int j = 0; j < gridSize; ++j)
            {
                cells[i][j].setSize(Vector2f(cellSize - 2, cellSize - 2)); // размер ячейки
                cells[i][j].setPosition(i * cellSize, j * cellSize);       // позиция из индексов
                cells[i][j].setFillColor(Color::Black);                    // цвет заливки
                cells[i][j].setOutlineColor(Color::White);                 // цвет границы
                cells[i][j].setOutlineThickness(1);
            }
        }

        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();

        }

        for (int i = 0; i < gridSize; i++) {
            for (int j = 0; j < gridSize; j++) {
                if (i == j)
                    cells[i][j].setFillColor(
                        Color::Green);
            }
        }

        for (int i = 0; i < gridSize; i++) {
            for (int j = 0; j < gridSize; j++) {
                if (i == 0 || i == gridSize - 1)
                    cells[i][j].setFillColor(
                        Color::Green);
            }
        }

        window.clear(Color::White);

        for (int i = 0; i < gridSize; ++i)
        {
            for (int j = 0; j < gridSize; ++j)
            {
                window.draw(cells[i][j]);

            }
        }

        window.display();

    }

    return 0;

}