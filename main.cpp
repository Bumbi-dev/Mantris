#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;

int main() {
    RenderWindow window(VideoMode(500, 500), "Simple Window");
    RectangleShape rect(Vector2f(160, 50));

    rect.setFillColor(Color::Green);
    rect.setPosition((window.getSize().x - rect.getSize().x) / 2, (window.getSize().y - rect.getSize().y) / 2);

    window.draw(rect);
    window.display();

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            for(int i = 0; i < 9999; i++)
                i*=1;

            rect.setPosition(rect.getPosition().x, rect.getPosition().y + 1);

            window.clear();
            window.draw(rect);
            window.display();
            
            if (event.type == Event::Closed)
                window.close();
        }
    }

    return 0;
}

void asteapta() {
    for(int i = 0; i < 9999999999; i++)
        i*=1;

}
