﻿// Mandlebrot.cpp : Defines the entry point for the application.
//

#include "Mandlebrot.h"
#include <SFML/Graphics.hpp>
#include <complex>

using namespace std;

const unsigned int WIDTH = 800;
const unsigned int HEIGHT = 800;
const unsigned int ITERATIONS = 40;
const unsigned int THRESHHOLD = 500;

int mandlebrot(int x, int y);

int main()
{
    // create the window
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "My window");

    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // clear the window with black color
        window.clear(sf::Color::Black);

        // draw everything here...
        const unsigned int W = WIDTH;
        const unsigned int H = HEIGHT;

        sf::Uint8* pixels = new sf::Uint8[W * H * 4];

        sf::Texture texture;
        texture.create(W, H);

		sf::Sprite sprite(texture); // needed to draw the texture on screen

		for (register int x = 0; x < W; x += 1) {
			for (register int y = 0; y < H; y += 1) {
				/*pixels[x * y * 4] = mandlebrot(x, y);
				pixels[x * y * 4 + 1] = mandlebrot(x, y);
				pixels[x * y * 4 + 2] = mandlebrot(x, y);*/
				pixels[(y * H + x) * 4] = mandlebrot(x, y);
				pixels[(y * H + x) * 4 + 1] = 0;
				pixels[(y * H + x) * 4 + 2] = 0;
				pixels[(y * H + x) * 4 + 3] = 255;
			}
		}

        texture.update(pixels);


        window.draw(sprite);

        // end the current frame
        window.display();
    }

    return 0;
}

int mandlebrot(int x, int y) {

    complex<double> z(0.0, 0.0);
    complex<double> c((double(x) / WIDTH - 0.5) * 4, (double(y) / HEIGHT - 0.5) * 4);
    for (int i = 0; i < ITERATIONS; i++) {
        z = pow(z, 2) + c;
        if (abs(z) > THRESHHOLD) {
            return int(float(i)/ITERATIONS*255);
        }
    }
    return 0;
}