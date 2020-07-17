#include <iostream>
#include "Shape.h"
#include "Vector2.h"

void nc::Shape::Draw(Core::Graphics& graphics, nc::Vector2 position, float scale, float angle){
	std::cout << "Drawing 2" << std::endl;
	graphics.SetColor(m_color);

	for (size_t i = 0; i < m_points.size() - 1; i++) {
		nc::Vector2 p1 = m_points[i];
		nc::Vector2 p2 = m_points[i + 1];

		p1 = p1 * scale;
		p2 = p2 * scale;

		p1 = nc::Vector2::Rotate(p1, angle);
		p2 = nc::Vector2::Rotate(p2, angle);

		p1 = p1 + position;
		p2 = p2 + position;




		graphics.DrawLine(p1.x, p1.y, p2.x, p2.y);
	}

}
