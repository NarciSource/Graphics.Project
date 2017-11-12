#pragma once
#include <string>

namespace CAGLE {

	class ModelData {
	public:
		int polygoncount;
		int polygoncolor;
		float* vertexdata;
		float* normaldata;
		float* uvdata;
		
	public:
		void dataLoad(const std::string filename);
		void dataLoad2(const std::string filename);
	};

}