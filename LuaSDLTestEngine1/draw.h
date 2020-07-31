#ifndef DRAW_H
#define DRAW_H

#include "globals.h"

#include <stdarg.h>

void drawLineRect(int x, int y, int w, int h);
void drawFillRect(int x, int y, int w, int h);
void drawLine(int x1, int y1, int x2, int y2);
void drawLines(int n, ...);
void drawCircle(int x, int y, double r);

#endif