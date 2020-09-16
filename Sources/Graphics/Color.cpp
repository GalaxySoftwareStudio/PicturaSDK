#include "PicturaPCH.h"
#include "Color.h"

namespace Pictura::Graphics
{
    Color Color::Black = Graphics::Color();
	Color Color::White = Color(1.f, 1.f, 1.f, 1.f);
	Color Color::Transparent = Color(1.f, 1.f, 1.f, 0.f);
	Color Color::PureRed = Color(1.f, 0.f, 0.f, 1.f);
	Color Color::Yellow = Color(1.f, 1.f, 0.f, 1.f);
	Color Color::Orange = Color(1.f, 0.5f, 0.f, 1.f);
	Color Color::PureGreen = Color(0.f, 1.f, 0.f, 1.f);
	Color Color::Cyan = Color(0.f, 1.f, 1.f, 1.f);
	Color Color::PureBlue = Color(0.f, 0.f, 1.f, 1.f);
	Color Color::Magenta = Color(1.f, 0.f, 1.f, 1.f);
	Color Color::Purple = Color(0.5f, 0.f, 1.f, 1.f);
}