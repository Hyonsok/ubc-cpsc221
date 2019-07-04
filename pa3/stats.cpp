
#include "stats.h"

stats::stats(PNG & im)
{

	// initialize the private vectors so that, for each color channel, 
	// (x,y) is the cumulative sum of the the color values from (0,0)
	// to (x,y). 
	// Note that the hue (h) value of each pixel is represented by
	// its cartesian coordinates: X = cos(h) and Y = sin(h). 
	// This is done to simplify distance and average computation.

	sumSat.resize(im.width());
	sumLum.resize(im.width());
	sumHueX.resize(im.width());
	sumHueY.resize(im.width());
	hist.resize(im.width());
	for (unsigned int x = 0; x < im.width(); x++) {
		sumSat[x].resize(im.height());
		sumLum[x].resize(im.height());
		sumHueX[x].resize(im.height());
		sumHueY[x].resize(im.height());
		hist[x].resize(im.height());
		for (unsigned int y = 0; y < im.height(); y++) {
			HSLAPixel temp = *im.getPixel(x, y);
			double degToRad = temp.h * (PI / 180);
			double cosH = cos(degToRad);
			double sinH = sin(degToRad);
			int HueRange = temp.h / 10;

			hist[x][y].resize(36);

			if (x == 0 && y == 0) {
				sumLum[x][y] = temp.l;
				sumSat[x][y] = temp.s;
				sumHueX[x][y] = cosH;
				sumHueY[x][y] = sinH;
				hist[x][y][HueRange] = hist[x][y][HueRange] + 1;
			}
			else if (x == 0 && y > 0) {
				sumLum[x][y] = sumLum[x][y - 1] + temp.l;
				sumSat[x][y] = sumSat[x][y - 1] + temp.s;
				sumHueX[x][y] = sumHueX[x][y - 1] + cosH;
				sumHueY[x][y] = sumHueY[x][y - 1] + sinH;
				for (unsigned int k = 0; k < 36; k++) {
					hist[x][y][k] = hist[x][y - 1][k];
				}
				hist[x][y][HueRange]++;
			}
			else if (x > 0 && y == 0) {
				sumLum[x][y] = sumLum[x - 1][y] + temp.l;
				sumSat[x][y] = sumSat[x - 1][y] + temp.s;
				sumHueX[x][y] = sumHueX[x - 1][y] + cosH;
				sumHueY[x][y] = sumHueY[x - 1][y] + sinH;
				for (unsigned int k = 0; k < 36; k++) {
					hist[x][y][k] = hist[x - 1][y][k];
				}
				hist[x][y][HueRange]++;
			}
			else {
				sumLum[x][y] = temp.l + sumLum[x - 1][y] + sumLum[x][y - 1] - sumLum[x - 1][y - 1];
				sumSat[x][y] = temp.s + sumSat[x - 1][y] + sumSat[x][y - 1] - sumSat[x - 1][y - 1];
				sumHueX[x][y] = cosH + sumHueX[x - 1][y] + sumHueX[x][y - 1] - sumHueX[x - 1][y - 1];
				sumHueY[x][y] = sinH + sumHueY[x - 1][y] + sumHueY[x][y - 1] - sumHueY[x - 1][y - 1];

				for (unsigned int k = 0; k < 36; k++) {
					hist[x][y][k] = hist[x - 1][y][k] + hist[x][y - 1][k] - hist[x - 1][y - 1][k];
				}
				hist[x][y][HueRange]++;
			}

		}
	}
}

long stats::rectArea(pair<int, int> ul, pair<int, int> lr)
{


	//x
	int xSide = lr.first - ul.first;

	//y
	int ySide = lr.second - ul.second;

	long result = (xSide + 1) * (ySide + 1);

	if (xSide == 0 && ySide == 0) {
		result = 1;
		return result;
	}

	if (xSide == 0) {
		result = ySide + 1;
		return result;
	}

	if (ySide == 0) {
		result = xSide + 1;
		return result;
	}

	//cout << "result" << endl;
	//cout << result << endl;
	return result;
}

HSLAPixel stats::getAvg(pair<int, int> ul, pair<int, int> lr)
{

	/* your code here */
	long pixels = rectArea(ul, lr);
	// sumSat
	double sat;

	if (ul.first == 0 && ul.second == 0) {
		sat = sumSat[lr.first][lr.second];
	}
	else if (ul.first == 0 && ul.second > 0) {
		sat = sumSat[lr.first][lr.second] - sumSat[lr.first][ul.second - 1];
	}
	else if (ul.first > 0 && ul.second == 0) {
		sat = sumSat[lr.first][lr.second] - sumSat[ul.first - 1][lr.second];
	}
	else {
		sat = sumSat[lr.first][lr.second] - sumSat[lr.first][ul.second - 1] - sumSat[ul.first - 1][lr.second]
			+ sumSat[ul.first - 1][ul.second - 1];
	}

	sat /= pixels;


	// sumLum
	double lum;

	// sumHueX
	double hueX;
	double hueY;

	if (ul.first == 0 && ul.second == 0) {
		lum = sumLum[lr.first][lr.second];
		hueX = sumHueX[lr.first][lr.second];
		hueY = sumHueY[lr.first][lr.second];
	}
	else if (ul.first == 0 && ul.second > 0) {
		lum = sumLum[lr.first][lr.second] - sumLum[lr.first][ul.second - 1];
		hueX = sumHueX[lr.first][lr.second] - sumHueX[lr.first][ul.second - 1];
		hueY = sumHueY[lr.first][lr.second] - sumHueY[lr.first][ul.second - 1];
	}
	else if (ul.first > 0 && ul.second == 0) {
		lum = sumLum[lr.first][lr.second] - sumLum[ul.first - 1][lr.second];
		hueX = sumHueX[lr.first][lr.second] - sumHueX[ul.first - 1][lr.second];
		hueY = sumHueX[lr.first][lr.second] - sumHueY[ul.first - 1][lr.second];
	}
	else {
		lum = sumLum[lr.first][lr.second] - sumLum[lr.first][ul.second - 1] - sumLum[ul.first - 1][lr.second]
			+ sumLum[ul.first - 1][ul.second - 1];
		hueX = sumHueX[lr.first][lr.second] - sumHueX[lr.first][ul.second - 1] - sumHueX[ul.first - 1][lr.second]
			+ sumHueX[ul.first - 1][ul.second - 1];
		hueY = sumHueY[lr.first][lr.second] - sumHueY[lr.first][ul.second - 1] - sumHueY[ul.first - 1][lr.second]
			+ sumHueY[ul.first - 1][ul.second - 1];
	}

	lum /= pixels;



	hueX /= pixels;
	hueY /= pixels;

	double hue = atan2(hueY, hueX) * (180 / PI);

	HSLAPixel result;

	result.s = sat;
	result.l = lum;
	result.h = hue;
	result.a = 1.0;

	return result;
}

double stats::entropy(pair<int, int> ul, pair<int, int> lr)
{

	vector<int> distn;

	/* using private member hist, assemble the distribution over the
	*  given rectangle defined by points ul, and lr into variable distn.
	*  You will use distn to compute the entropy over the rectangle.
	*  if any bin in the distn has frequency 0, then do not add that
	*  term to the entropy total. see .h file for more details.
	*/

	int x = ul.first;
	int y = ul.second;

	int xx = lr.first;
	int yy = lr.second;

	double entropy = 0;
	long area = rectArea(ul, lr);
	distn.resize(36);

	if (ul.first == 0 && ul.first == 0) {
		for (unsigned int k = 0; k < 36; k++) {
			distn[k] = hist[xx][yy][k];
		}
	}

	if (ul.first == 0 && ul.second == 0) {
		for (unsigned int k = 0; k < 36; k++) {
			distn[k] = hist[xx][yy][k];
		}
	}
	else if (ul.first == 0 && ul.second > 0) {

		for (unsigned int k = 0; k < 36; k++) {
			distn[k] = hist[lr.first][lr.second][k] - hist[lr.first][ul.second - 1][k];
		}
	}
	else if (ul.first > 0 && ul.second == 0) {
		for (unsigned int k = 0; k < 36; k++) {
			distn[k] = hist[lr.first][lr.second][k] - hist[ul.first - 1][lr.second][k];
		}
	}
	else {
		for (unsigned int k = 0; k < 36; k++) {
			distn[k] = hist[lr.first][lr.second][k] - hist[ul.first - 1][lr.second][k] - hist[lr.first][ul.second - 1][k]
				+ hist[ul.first - 1][ul.second - 1][k];
		}
	}


	for (int i = 0; i < 36; i++) {
		if (distn[i] > 0) {
			entropy += ((double)distn[i] / (double)area) * log2((double)distn[i] / (double)area);
		}

	}
	return  -1 * entropy;
}