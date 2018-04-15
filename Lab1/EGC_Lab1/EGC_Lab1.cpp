//
//  main.cpp
//  SDL_Lab1
//
//  Created by CGIS on 16/02/16.
//  Copyright © 2016 CGIS. All rights reserved.
//

#include <iostream>
#include "include\SDL.h"
#include "algorithm"

//define window dimensions
const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;

SDL_Window *window = NULL;
SDL_Surface *windowSurface = NULL;
SDL_Event currentEvent;

SDL_Rect rectangleCoordinates = { 100, 100, 200, 200 };
Uint32 rectagleColor;

bool quit = false;

int mouseX, mouseY;

bool initWindow()
{
	bool success = true;

	//Try to initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "SDL initialization failed" << std::endl;
		success = false;
	}
	else {
		//Try to create the window
		window = SDL_CreateWindow("SDL Hello World Example", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI);

		if (window == NULL)
		{
			std::cout << "Failed to create window: " << SDL_GetError() << std::endl;
			success = false;
		}
		else
		{
			//Try to get the window surface
			windowSurface = SDL_GetWindowSurface(window);

			if (windowSurface == NULL)
			{
				std::cout << "Failed to get the window surface: " << SDL_GetError() << std::endl;
				success = false;
			}
			else
			{
				//Initialize surface color
				SDL_FillRect(windowSurface, NULL, SDL_MapRGB(windowSurface->format, 255, 255, 255));

				//Update the surface
				SDL_UpdateWindowSurface(window);
			}

		}
	}

	return success;
}

void destroyWindow()
{
	//Destroy window
	SDL_DestroyWindow(window);
	window = NULL;

	//Quit SDL
	SDL_Quit();
}

struct forma
{
	int startx, starty, length, height;
	int rgb[3];
};

void redraw(forma form[], int n)
{
	SDL_FillRect(windowSurface, NULL, SDL_MapRGB(windowSurface->format, 255, 255, 255));

	for (int i = 0; i <= n; i++)
	{
		rectangleCoordinates = { form[i].startx, form[i].starty, form[i].length, form[i].height };
		rectagleColor = SDL_MapRGB(windowSurface->format, form[i].rgb[0], form[i].rgb[1], form[i].rgb[2]);
		SDL_FillRect(windowSurface, &rectangleCoordinates, rectagleColor);
	}
}

int main(int argc, char * argv[]) {
	char colour = 'b';
	int rgb[3] = { 0, 0, 255 };
	int start[2] = { 0, 0 };
	int finish[2] = { 0, 0 };

	const int n = 100;
	int index = 0;
	int last = -1;

	forma forme[n];

	if (!initWindow())
	{
		std::cout << "Failed to initialize" << std::endl;
		return -1;
	}

	rectagleColor = SDL_MapRGB(windowSurface->format, 0, 0, 255);

	while (!quit) {
		//Handle events on queue
		if (SDL_WaitEvent(&currentEvent) != 0)
		{
			//User requests quit
			if (currentEvent.type == SDL_QUIT)
			{
				quit = true;
			}

			//Mouse event -> pressed button
			if (currentEvent.type == SDL_MOUSEBUTTONDOWN)
			{
				if (currentEvent.button.button == SDL_BUTTON_LEFT)
				{
					SDL_GetMouseState(&mouseX, &mouseY);
					std::cout << "Mouse click => " << "x: " << mouseX << ", y: " << mouseY << std::endl;

					start[0] = mouseX;
					start[1] = mouseY;

					last++;
				}
			}

			//Mouse event -> mouse movement
			if (currentEvent.type == SDL_MOUSEMOTION)
			{
				if (currentEvent.button.button == SDL_BUTTON_LEFT)
				{
					SDL_GetMouseState(&mouseX, &mouseY);
					std::cout << "Mouse move => " << "x: " << mouseX << ", y: " << mouseY << std::endl;

					finish[0] = mouseX;
					finish[1] = mouseY;

					// Redraw the canvas
					//SDL_FillRect(windowSurface, NULL, SDL_MapRGB(windowSurface->format, 255, 255, 255));
					redraw(forme, last);

					// Paint the rectangle
					rectangleCoordinates = { std::min(start[0], finish[0]), std::min(start[1], finish[1]), abs(start[0] - finish[0]), abs(start[1] - finish[1]) };
					rectagleColor = SDL_MapRGB(windowSurface->format, rgb[0], rgb[1], rgb[2]);
					SDL_FillRect(windowSurface, &rectangleCoordinates, rectagleColor);
				}

			}

			if (currentEvent.type == SDL_MOUSEBUTTONUP)
			{
				if (currentEvent.button.button == SDL_BUTTON_LEFT)
				{
					SDL_GetMouseState(&mouseX, &mouseY);

					forme[last].startx = std::min(start[0], finish[0]);
					forme[last].starty = std::min(start[1], finish[1]);
					forme[last].length = abs(start[0] - finish[0]);
					forme[last].height = abs(start[1] - finish[1]);
					forme[last].rgb[0] = rgb[0];
					forme[last].rgb[1] = rgb[1];
					forme[last].rgb[2] = rgb[2];

					index = last;
				}
			}

			//Keyboard event
			if (currentEvent.type == SDL_KEYDOWN)
			{
				switch (currentEvent.key.keysym.sym)
				{
				case SDLK_UP:
					switch (colour) {
					case 'r':
						rgb[0] = 255 < rgb[0] + 1 ? 255 : rgb[0] + 1;
						break;
					case 'g':
						rgb[1] = 255 < rgb[1] + 1 ? 255 : rgb[1] + 1;
						break;
					case 'b':
						rgb[2] = 255 < rgb[2] + 1 ? 255 : rgb[2] + 1;
						break;
					default:
						break;
					}
					forme[index].rgb[0] = rgb[0];
					forme[index].rgb[1] = rgb[1];
					forme[index].rgb[2] = rgb[2];
					//rectagleColor = SDL_MapRGB(windowSurface->format, rgb[0], rgb[1], rgb[2]);
					std::cout << "r: " << rgb[0] << " g: " << rgb[1] << " b: " << rgb[2] << std::endl;
					redraw(forme, last);
					break;

				case SDLK_DOWN:
					switch (colour) {
					case 'r':
						rgb[0] = 0 > rgb[0] - 1 ? 0 : rgb[0] - 1;
						break;
					case 'g':
						rgb[1] = 0 > rgb[1] - 1 ? 0 : rgb[1] - 1;
						break;
					case 'b':
						rgb[2] = 0 > rgb[2] - 1 ? 0 : rgb[2] - 1;
						break;
					default:
						break;
					}
					forme[index].rgb[0] = rgb[0];
					forme[index].rgb[1] = rgb[1];
					forme[index].rgb[2] = rgb[2];
					//rectagleColor = SDL_MapRGB(windowSurface->format, rgb[0], rgb[1], rgb[2]);
					std::cout << "r: " << rgb[0] << " g: " << rgb[1] << " b: " << rgb[2] << std::endl;
					redraw(forme, last);
					break;

				case SDLK_LEFT:
					index = std::max(std::min(index - 1, last), 0);
					std::cout << "Selected rectangle nr. " << index << std::endl;
					rgb[0] = forme[index].rgb[0];
					rgb[1] = forme[index].rgb[1];
					rgb[2] = forme[index].rgb[2];
					break;

				case SDLK_RIGHT:
					index = std::max(std::min(index + 1, last), 0);
					std::cout << "Selected rectangle nr. " << index << std::endl;
					rgb[0] = forme[index].rgb[0];
					rgb[1] = forme[index].rgb[1];
					rgb[2] = forme[index].rgb[2];
					break;

				case SDLK_r:
					colour = 'r';
					std::cout << "Selected red" << std::endl;
					break;

				case SDLK_g:
					colour = 'g';
					std::cout << "Selected green" << std::endl;
					break;

				case SDLK_b:
					colour = 'b';
					std::cout << "Selected blue" << std::endl;
					break;

				case SDLK_z:
					forme[last].startx = 0;
					forme[last].starty = 0;
					forme[last].length = 0;
					forme[last].height = 0;
					forme[last].rgb[0] = 255;
					forme[last].rgb[0] = 255;
					forme[last].rgb[0] = 255;
					last = std::max(last - 1, 0);
					redraw(forme, last);
					break;

				default:
					break;
				}
			}
			//SDL_FillRect(windowSurface, &rectangleCoordinates, rectagleColor);
			SDL_UpdateWindowSurface(window);
		}
	}

	destroyWindow();
	return 0;
}
