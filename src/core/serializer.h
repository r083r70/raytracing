#pragma once

#include<cstdint>

namespace raytracing
{
	class Serializer
	{
    public:
		static bool saveWindowSize(int32_t width, int32_t height);
		static bool loadWindowSize(int32_t& width, int32_t& height);
	};
}
