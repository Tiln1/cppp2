#include "../Header Files/pch.h"
#include "Transform.h"

namespace nc {
	std::istream& operator >> (std::istream& stream, Transform& transform) {
		stream >> transform.position;
		std::string line;
		std::getline(stream, line);
		transform.scale = stof(line);
		std::getline(stream, line);
		transform.angle = stof(line);
		//stream >> transform.scale;
		//stream >> transform.angle;

		return stream;
	}

	void Transform::Update() {
		Matrix33 mxs;
		mxs.Scale(scale);
		Matrix33 mxr;
		mxs.Rotate(angle);
		Matrix33 mxt;
		mxs.Translate(position);
		
		matrix = mxs * mxr * mxt;
	}
		
}