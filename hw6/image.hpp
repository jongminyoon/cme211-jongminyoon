#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <string>

#include <boost/multi_array.hpp>
#include "hw6.hpp"

class image {

	boost::multi_array<unsigned char, 2> input;
	boost::multi_array<unsigned char, 2> output;

	std::string inputname;
public:
	/* constructs a class image by reading an image with the filename */
	image(std::string inputname);

	/* saves the current version of the image (output) to a jpeg file with the file name. */
	void Save(std::string outputname);
	void Save(); /* if no argument is provided, use the inputname for the output jpeg file */

	void Convolution(boost::multi_array<unsigned char, 2> &input,
					boost::multi_array<unsigned char, 2> &output,
					boost::multi_array<float, 2> &kernel);

	void BoxBlur(int k_size);

	unsigned int Sharpness();

};




#endif /* IMAGE_HPP */