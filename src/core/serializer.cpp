
#include "serializer.h"

#include "yaml-cpp/yaml.h"
#include<fstream>

namespace raytracing
{
	bool Serializer::saveWindowSize(int32_t width, int32_t height)
	{
		YAML::Node rootNode;
		rootNode["width"] = width;
		rootNode["height"] = height;

		std::ofstream fout("window_settings.yaml");
		fout << rootNode << std::endl;
		return true;
	}

	bool Serializer::loadWindowSize(int32_t& width, int32_t& height)
	{
		const YAML::Node rootNode = YAML::LoadFile("window_settings.yaml");
		width = rootNode["width"].as<int32_t>();
		height = rootNode["height"].as<int32_t>();
		return true;
	}
}
