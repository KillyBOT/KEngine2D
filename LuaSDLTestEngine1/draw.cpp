#include "draw.h"
#include <math.h>

void drawLineRect(int x, int y, int w, int h) {
	SDL_Rect rect = { x, y, w, h };

	SDL_RenderDrawRect(gRenderer, &rect);
}

void drawFillRect(int x, int y, int w, int h) {
	SDL_Rect rect = { x, y, w, h };

	SDL_RenderFillRect(gRenderer, &rect);
}
void drawLine(int x1, int y1, int x2, int y2) {
	SDL_RenderDrawLine(gRenderer, x1, y1, x2, y2);
}
void drawLines(int n, ...) {
	va_list ap;
	int x1, y1, x2, y2;

	if (n < 2) return;

	va_start(ap, n);
	x1 = va_arg(ap, int);
	y1 = va_arg(ap, int);
	for (int i = 1; i < n; i++) {

		x2 = va_arg(ap, int);
		y2 = va_arg(ap, int);

		SDL_RenderDrawLine(gRenderer, x1, y1, x2, y2);

		x1 = x2;
		y1 = y2;

	}
	va_end(ap);
}
void drawCircle(int x, int y, double r) {
	SDL_Point points[257];

	double theta = 0;
	double step = M_PI / 128;

	for (int n = 0; n < 257; n++) {
		points[n].x = x + cos(theta) * r;
		points[n].y = y + sin(theta) * r;

		theta += step;
	}

	for (int n = 0; n < 256; n++) {
		SDL_RenderDrawLine(gRenderer, points[n].x, points[n].y, points[n + 1].x, points[n + 1].y);
	}
}