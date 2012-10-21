#include "base64BitmapString.h"

#include "fontdata.inc"

class base64Text
{
public:
	
	int fontSpacing;
	int lineHeight;
	int baseLine;
    int sw;
	
	ofImage image;
	map<char, ofRectangle> charMap;
	
	base64Text() : fontSpacing(1), lineHeight(11), baseLine(8) {
        sw = 0;
    }
	
	void loadFont(const char* fontDataBase64)
	{
		string data = base64_decode(fontDataBase64);
		
		ofBuffer buf(data.data(), data.size());
		ofPixels pix;
		ofLoadImage(pix, buf);
		
		image.setFromPixels(pix);
		
		int lastOffset = 0;
		char charCode = ' ';
		
		for (int i = 0; i < image.getWidth(); i++)
		{
			ofColor c = image.getColor(i, 0);
			
			if (c == ofColor::red)
			{
				charMap[charCode] = ofRectangle(lastOffset, 0, i - lastOffset, image.getHeight());
				
				lastOffset = i + 1;
				charCode++;
			}
		}
		
		for (int y = 0; y < image.getHeight(); y++)
		{
			for (int x = 0; x < image.getWidth(); x++)
			{
				ofColor c = image.getColor(x, y);
				if (c == ofColor::black)
				{
					c.set(255);
				}
				else
				{
					c.set(255, 0);
				}
				
				image.setColor(x, y, c);
			}
		}
		
		image.update();
	}
	
	inline int getCharWidth(char c)
	{
		return charMap[c].width;
	}
	
	void drawChar(char c)
	{
		ofRectangle &r = charMap.at(c);
		
		glBegin(GL_QUADS);
		glTexCoord2i(r.x, r.y);
		glVertex2i(0, 0);
		
		glTexCoord2i(r.x + r.width, r.y);
		glVertex2i(r.width, 0);
		
		glTexCoord2i(r.x + r.width, r.y + r.height);
		glVertex2i(r.width, r.height);
		
		glTexCoord2i(r.x, r.y + r.height);
		glVertex2i(0, r.height);
		glEnd();
	}
	
	void drawString(const string &text, int x, int y)
	{
		glPushMatrix();
		glTranslatef(x, y, 0);
		
		int ox = 0;
		int oy = 0;
        int _sw = 0;
		
		image.getTextureReference().bind();
		
		for (int i = 0; i < text.size(); i++)
		{
			char c = text[i];
			
			if (c == '\n')
			{
				if(sw < _sw) sw = _sw;
                ox = 0;
				oy += lineHeight;
			}
			else
			{
				glPushMatrix();
				glTranslatef(ox, oy, 0);
				drawChar(c);
				glPopMatrix();
				
				ox += getCharWidth(c) + fontSpacing;
                _sw += ox;
			}
		}
		
		image.getTextureReference().unbind();
		
		glPopMatrix();
	}
	
	ofRectangle getStringBoundingBox(const string &text, int x, int y)
	{
		ofRectangle result;
		
		result.x = x;
		result.y = y;
		
		int ox = 0;
		int oy = baseLine;
		
		for (int i = 0; i < text.size(); i++)
		{
			char c = text[i];
			
			if (c == '\n')
			{
				ox = 0;
				oy += lineHeight;
			}
			else
			{
				ox += getCharWidth(c) + fontSpacing;
			}
			
			result.width = max((int)result.width, ox);
			result.height = max((int)result.height, oy);
		}
		
		return result;
	}
};

static base64Text *t = NULL;

static void init_font()
{
	if (t == NULL)
	{
		t = new base64Text();
		//t->loadFont(standard58);
        t->loadFont(standard56);
	}
}

void base64DrawBitmapString(const string &text, int x, int y)
{
	init_font();
	t->drawString(text, x, y);
}

ofRectangle base64GetStringBoundingBox(const string &text, int x, int y)
{
	init_font();
	return t->getStringBoundingBox(text, x, y);
}

int base64GetStringLineHeight()
{
	init_font();
	return t->lineHeight;
}