#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include<windows.h>
using namespace sf;
using namespace std;
class comp_num {
	private:
		double re_p = 0, im_p = 0;
	public:
		comp_num()
		{
		}
		comp_num(double re, double im)
		{
			re_p = re;
			im_p = im;
		}
		comp_num(const comp_num& a) {
			re_p = a.re_p;
			im_p = a.im_p;
		}
		comp_num& operator= (const comp_num& a){
			re_p = a.re_p;
			im_p = a.im_p;
			return (*this);
		}
		comp_num operator+(const comp_num& a) {
			return comp_num(re_p + a.re_p, im_p + a.im_p);
		}
		comp_num operator-(const comp_num& a) {
			return comp_num(re_p - a.re_p, im_p - a.im_p);
		}
		comp_num operator*(const comp_num& a) {
			return comp_num(re_p * a.re_p - im_p * a.im_p, re_p * a.im_p + im_p * a.re_p);
		}
		double abs() {
			return sqrt(re_p * re_p + im_p * im_p);
		}
};
int cont(int c, bool type) {
	if (type) {
		if (c > 1850) {
			c = 1850;
		}
		if (c < 50) {
			c = 50;
		}
	}
	else {
		if (c > 1050) {
			c = 1050;
		}
		if (c < 50) {
			c = 50;
		}
	}
	return c;
}
int main()
{
	long long width = 1800, height = 1000, k = 100, ogr = 2;
	double xmin = -2.;
	double xmax = 1.;
	double ymin = -1.5;
	double ymax = 1.5;
	sf::RenderWindow wnd(sf::VideoMode(1000, 1000), "SFML", Style::Fullscreen);
	sf::Uint8* pixels = new sf::Uint8[width * height * 4];
	bool fl_paint = 1;
	bool fl_mouse = 0;
	int x_mouse = 0, y_mouse = 0;
	int x_now = 0, y_now = 0;
	bool contin = 1;
	while (wnd.isOpen())
	{
		if (fl_paint) {
			wnd.clear();
			sf::ConvexShape convex;
			convex.setPointCount(4);
			convex.setPoint(0, sf::Vector2f(1850, 0));
			convex.setPoint(1, sf::Vector2f(1850, 50));
			convex.setPoint(2, sf::Vector2f(1900, 50));
			convex.setPoint(3, sf::Vector2f(1900, 0));
			wnd.draw(convex);
			double hx = (xmax - xmin) / width;
			double hy = (ymax - ymin) / height;
			double x = xmin, y = ymin;
			for (int xx = 0; xx < height; xx++) {
				y += hy;
				x = xmin;
				for (int yy = 0; yy < width; yy++) {
					x += hx;
					comp_num z{ 0, 0 };
					
					comp_num c{ x, y};
					int i = k;
					for (; i > 0; i--) {
						z = z * z + c;
						if (z.abs() > ogr) {
							break;
						}
					}
					if (x >= 0) {
						int fscwe = 0;
					}
					pixels[(xx * width + yy) * 4] = 255 / 100. * i;
					pixels[(xx * width + yy) * 4 + 1] = 0;
					pixels[(xx * width + yy) * 4 + 2] = 255 / 100. * i;
				}
			}
			sf::Texture tx;
			tx.create(width, height);
			tx.update((sf::Uint8*)pixels, width, height, 0, 0);
			sf::Sprite sprite(tx);
			sprite.setPosition(50, 50);
			wnd.draw(sprite);
			wnd.display();
			fl_paint = 0;
		}
		if (fl_mouse){
			wnd.clear();
			sf::ConvexShape convex;
			convex.setPointCount(4);
			convex.setPoint(0, sf::Vector2f(1850, 0));
			convex.setPoint(1, sf::Vector2f(1850, 50));
			convex.setPoint(2, sf::Vector2f(1900, 50));
			convex.setPoint(3, sf::Vector2f(1900, 0));
			wnd.draw(convex);
			sf::Texture tx;
			tx.create(width, height);
			tx.update((sf::Uint8*)pixels, width, height, 0, 0);
			sf::Sprite sprite(tx);
			sprite.setPosition(50, 50);
			wnd.draw(sprite);
			Vector2i pixelPos = Mouse::getPosition(wnd);
			x_now = cont(pixelPos.x, 1);
			y_now = cont(pixelPos.y, 0);
			sf::Vertex line[] =
			{
				sf::Vertex(sf::Vector2f(x_mouse, y_mouse)),
				sf::Vertex(sf::Vector2f(x_mouse, y_now))
			};
			wnd.draw(line, 2, sf::Lines);
			sf::Vertex line1[] =
			{
				sf::Vertex(sf::Vector2f(x_mouse, y_mouse)),
				sf::Vertex(sf::Vector2f(x_now, y_mouse))
			};
			wnd.draw(line1, 2, sf::Lines);
			sf::Vertex line2[] =
			{
				sf::Vertex(sf::Vector2f(x_now, y_mouse)),
				sf::Vertex(sf::Vector2f(x_now, y_now))
			};
			wnd.draw(line2, 2, sf::Lines);
			sf::Vertex line3[] =
			{
				sf::Vertex(sf::Vector2f(x_mouse, y_now)),
				sf::Vertex(sf::Vector2f(x_now, y_now))
			};
			wnd.draw(line3, 2, sf::Lines);
			wnd.display();
			Sleep(100);
		}

		sf::Event event;
		while (wnd.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				wnd.close();
				break;
			}
			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					x_mouse = event.mouseButton.x;
					y_mouse = event.mouseButton.y;
					fl_mouse = 1;
					if (x_mouse < 1900 && x_mouse > 1850 && y_mouse > 0 && y_mouse < 50) {
						contin = 0;
					}
					x_mouse = cont(x_mouse, 1);
					y_mouse = cont(y_mouse, 0);
				}
			}
			if (event.type == sf::Event::MouseButtonReleased)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					fl_mouse = 0;
					fl_paint = 1;
					double hx = (xmax - xmin) / width;
					double hy = (ymax - ymin) / height;
					xmax = xmin + hx * max(x_now - 50, x_mouse - 50);
					xmin = xmin + hx * min(x_now - 50, x_mouse - 50);
					ymax = ymin + hy * max(y_now - 50, y_mouse - 50);
					ymin = ymin + hy * min(y_now - 50, y_mouse - 50);
				}
			}
		}
		if (!contin) {
			break;
		}
	}
	return 0;
}