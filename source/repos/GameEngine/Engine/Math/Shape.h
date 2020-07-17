#pragma once
#include "core.h"
#include "Color.h"
#include "Vector2.h"
#include <vector>
namespace nc {
	class Shape {
	private:
		std::vector<nc::Vector2> m_points;
		Color m_color;
	public:
		Shape() {}
		Shape(const std::vector<nc::Vector2>& points, const Color& color) : m_color{ color }, m_points{ points }{

		}

		void Draw(Core::Graphics& graphics, nc::Vector2 position, float scale = 1.0f, float angle = 0.0f) {
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


			void SetColor(Color color) { m_color = color; }
			const Color& GetColor() const { return m_color; }

		
	};
}