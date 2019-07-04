#include <vector>
#include "block.h"

// From im, grabs the vertical strip of pixels whose upper left corner is at position (column,0), 
// and whose width is width.
void Block::build(PNG & im, int column, int width)
{

	for (int w = column; w < column + width; w++) {
		vector<HSLAPixel> temp;
		for (int h = 0; h < im.height(); h++) {
			temp.push_back(*(im.getPixel(w, h)));
		}
		data.push_back(temp);
	}
	return;
}

// Draws the current block at position (column,0) in im.
void Block::render(PNG & im, int column) const
{

	for (int w = column; w < column + this->width(); w++) {
		for (int h = 0; h < this->height(); h++) {
			*(im.getPixel(w, h)) = this->data[w - column][h];
		}
	}

	return;
}

//This function changes the saturation of every pixel in the block to 0, which removes the color, leaving grey.
void Block::greyscale()
{

	for (unsigned x = 0; x < width(); x++) {
		for (unsigned y = 0; y < height(); y++) {
			(data[x][y]).s = 0;
		}
	}
}


int Block::width() const
{
	return data.size();
}

int Block::height() const
{
	return data[0].size();
}