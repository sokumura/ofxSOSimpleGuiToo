#pragma once

#include "ofMain.h"

void base64DrawBitmapString(const string &text, int x, int y);
ofRectangle base64GetStringBoundingBox(const string &text, int x = 0, int y = 0);

int base64GetStringLineHeight();