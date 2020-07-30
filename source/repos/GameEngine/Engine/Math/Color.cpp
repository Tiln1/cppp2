#include "../Header Files/pch.h"
#include "Color.h"


namespace nc {
	Color const Color::white = { 1, 1, 1 };
	Color const Color::red = { 1, 0, 0 };
	Color const Color::yellow = { 1, 1, 0 };
	Color const Color::cyan = { 0, 1, 1 };
	std::istream& operator >> (std::istream& stream, Color& c)
	{
		std::string line;
		std::getline(stream, line);

		if (line.find("{") != std::string::npos) {
			std::string cr = line.substr(line.find("{") + 1, line.find(",") - line.find("{") - 1);
			c.r = std::stof(cr);
			line = line.substr(line.find(",") + 1, line.find("}") - line.find(","));
			std::string cg = line.substr(0, line.find(","));
			c.g = std::stof(cg);
			std::string cb = line.substr(line.find(",") + 1, line.find("}") - line.find(",") - 1);
			c.b = std::stof(cb);
		}
		return stream;
	}
}