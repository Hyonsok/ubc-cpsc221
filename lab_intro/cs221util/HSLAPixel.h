#ifndef HSLAPixel_H
#define HSLAPixel_H

namespace cs221util {
	class HSLAPixel {
	public:
		double s;
		double a;
		double l;
		double h;

		HSLAPixel();

		HSLAPixel(double hue, double saturation, double luminance);

		HSLAPixel(double hue, double saturation, double luminance, double alpha);

	};
}
#endif