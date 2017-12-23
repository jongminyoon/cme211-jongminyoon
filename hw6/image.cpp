#include <string>
#include <boost/multi_array.hpp>


#include "image.hpp"
#include "hw6.hpp"

image::image(std::string inputname) {
	this->inputname = inputname;
	ReadGrayscaleJPEG(inputname, this->input);
	this->output.resize(boost::extents[this->input.shape()[0]][this->input.shape()[1]]);
	this->output = this->input;
}

void image::Save(std::string outputname) {
	WriteGrayscaleJPEG(outputname, this->output);
}

void image::Save() {
	image::Save(this->inputname);
}

void image::Convolution(boost::multi_array<unsigned char, 2> &input,
				boost::multi_array<unsigned char, 2> &output,
				boost::multi_array<float, 2> &kernel) {

	unsigned int nrows = (unsigned int)input.shape()[0];
	unsigned int ncols = (unsigned int)input.shape()[1];

	if ((nrows != output.shape()[0]) or ncols != output.shape()[1]) {
		std::cerr << "ERROR : input and output image sizes are different" << std::endl;
		exit(1);
	}

	unsigned int nker = (unsigned int)kernel.shape()[0];

	if (nker != kernel.shape()[1]) {
		std::cerr << "ERROR : kernel is not square" << std::endl;
		exit(1);
	}

	if (nker < 3 or nker%2 == 1) {
		std::cerr << "ERROR : kernel size is smaller than 3 or not odd" << std::endl;
		exit(1);
	}

	/* calculate the convolution. x,y for row and column indices for the image and i,j for scanning the kernel. */
	for (unsigned int x = 0 ; x < nrows ; x++) {
		for (unsigned int y = 0 ; y < ncols ; y++) {
			float temp = 0.f;
			for (int i = -nker/2 ; i <= (int)nker/2 ; i++) {
				int r = x+i;
				if (r < 0) r = 0;
				if (r >= (int)nrows) r = nrows-1;
				for (int j = -nker/2 ; j<= (int)nker/2 ; j++) {
					int c = y+j;
					if (c < 0) c = 0;
					if (c >= (int)ncols) c = ncols-1;
					temp += (float)input[r][c]*kernel[i+nker/2][j+nker/2];
				}
			}
			output[x][y] = (unsigned char)round(temp);
		}
	}
}

void image::BoxBlur(int k_size) {
	boost::multi_array<float,2> kernel(boost::extents[k_size][k_size]);
	float val = 1.f/((float)k_size)/((float)k_size);
	for (int i = 0 ; i < k_size ; i++) {
		for (int j = 0 ; j < k_size ; j++) {
			kernel[i][j] = val;
		}
	}
	image::Convolution(this->input, this->output, kernel);
}

unsigned int image::Sharpness() {
	boost::multi_array<float,2> kernel(boost::extents[3][3]);
	kernel[0][0] = 0.f;
	kernel[0][1] = 1.f;
	kernel[0][2] = 0.f;
	kernel[1][0] = 1.f;
	kernel[1][1] = -4.f;
	kernel[1][2] = 1.f;
	kernel[2][0] = 0.f;
	kernel[2][1] = 1.f;
	kernel[2][2] = 0.f;

	auto temp = this->output;

	image::Convolution(this->output, temp, kernel);
	unsigned int sharp = *std::max_element(temp.origin(), temp.origin() + temp.num_elements());

	return sharp;
}