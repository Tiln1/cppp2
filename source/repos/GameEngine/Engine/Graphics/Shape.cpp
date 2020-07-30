#include <fstream>
#include <iostream>
#include "Shape.h"
#include "../Math/Vector2.h"
#include "../Math/Transform.h"

namespace nc {
	void Shape::Draw(Core::Graphics& graphics, nc::Vector2 position, float scale, float angle) {
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

	void Shape::Draw(Core::Graphics& graphics, const Transform& transform) {
		Draw(graphics, transform.position, transform.scale, transform.angle);
	}


	bool Shape::Load(const std::string& filename)
	{
		bool success = false;
		std::ifstream stream(filename);
		if (stream.is_open()) {
			success = true;
			stream >> m_color;

			std::string line;
			std::getline(stream, line);
			size_t size = stoi(line);

			for (size_t i = 0; i < size; i++) {
				Vector2 point;
				stream >> point;

				m_points.push_back(point);
			}
			stream.close();
		}

		m_radius = 0;
		for (size_t i = 0; i < m_points.size(); i++) {
			nc::Vector2 p1 = m_points[i];
			float length = p1.Length();

			if (length > m_radius) { m_radius = length; }
		}
		return success;
	}
}