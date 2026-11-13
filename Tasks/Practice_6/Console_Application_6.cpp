#include <SFML/Graphics.hpp>
#include <functional>
#include <cmath>
#include <windows.h>
using namespace sf;

// Функция для отрисовки графика
void drawGraph(RenderWindow& window, std::function<float(float)> func,
    float xMin, float xMax, float scaleX, float scaleY, Color color) {
    VertexArray graph(LinesStrip);

    for (float x = xMin; x <= xMax; x += 0.1f) {
        float y = func(x);                 // вычисление значения функции

        float screenX = 400 + x * scaleX;  // преобразование координат в экранные
        float screenY = 400 - y * scaleY;

        graph.append(Vertex(Vector2f(screenX, screenY), color));
    }

    window.draw(graph);
}

int main() {

    std::string zone = "";

    RenderWindow window(VideoMode(800, 800), "Graph display application");

    CircleShape userPoint(5);          // пользовательская точка, радиус 5 пикселей
    userPoint.setFillColor(Color::Red);
    bool userPointExists = false;

    Font font;
    if (!font.loadFromFile("Comfortaa-Bold.ttf")) {
        return -1;
    }

    Text coordinatesText;
    coordinatesText.setFont(font);
    coordinatesText.setCharacterSize(20);
    coordinatesText.setFillColor(Color::White);
    coordinatesText.setPosition(10, 10);

    // Оси X и Y
    VertexArray xAxis(Lines, 2);
    xAxis[0].position = Vector2f(50, 400);   xAxis[0].color = Color::White;
    xAxis[1].position = Vector2f(750, 400);  xAxis[1].color = Color::White;
    VertexArray yAxis(Lines, 2);
    yAxis[0].position = Vector2f(400, 50);   yAxis[0].color = Color::White;
    yAxis[1].position = Vector2f(400, 750);  yAxis[1].color = Color::White;

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();

            if (event.type == Event::MouseButtonPressed) {
                if (event.mouseButton.button == Mouse::Left) {
                    Vector2i mousePos = Mouse::getPosition(window);

                    // Преобразование экранных координат в «математические»
                    float mathX = (mousePos.x - 400) / 30.0f; // Масштаб 30 по X
                    float mathY = -(mousePos.y - 400) / 5.0f; // Масштаб 30 по Y

                    userPoint.setPosition(mousePos.x - userPoint.getRadius(),
                        mousePos.y - userPoint.getRadius());
                    userPointExists = true;

                    if (mathY == 6 * mathX || mathY == 4 * mathX + 8) {
                        zone = "Border";
                    } else if (mathY <= 6 * mathX && mathY <= 4 * mathX + 8) {
                        zone = "1";
                    } else if (mathY >= 6 * mathX && mathY >= 4 * mathX + 8) {
                        zone = "2";
                    } else if (mathY >= 6 * mathX && mathY <= 4 * mathX + 8) {
                        zone = "3";
                    } else {
                        zone = "4";
                    }

                    coordinatesText.setString("Coordinates: (" + std::to_string(mathX) +
                        ", " + std::to_string(mathY) + ", " + zone + ")");
                }
            }
        }

        window.clear();

        window.draw(xAxis);
        window.draw(yAxis);

        drawGraph(window, [](float x) { return 6 * x; }, -10, 10, 30, 5, Color::Blue);
        drawGraph(window, [](float x) { return 4 * x + 8; }, -10, 10, 30, 5, Color::Red);

        if (userPointExists) {
            window.draw(userPoint);
            window.draw(coordinatesText);
        }

        window.display();
    }

    return 0;
}