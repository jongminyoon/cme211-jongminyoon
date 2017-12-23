#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

#include "image.hpp"
#include "hw6.hpp"


int main() {
	std::string inputname = "stanford.jpg";

	image img = image(inputname);
	std::cout << "Original image: " << img.Sharpness() << std::endl;

	int k_size = 3;
	while (k_size < 28) {
		img.BoxBlur(k_size);
		std::cout << "BoxBlur(" << std::setw(2) << k_size;
		std::cout << std::setw(7) << img.Sharpness() << std::endl;
		std::stringstream ss;
		ss << std::setw(2) << std::setfill('0') << k_size;
		std::string s = "BoxBlur"; 
		s += ss.str();
		s += ".jpg";
		img.Save(s);
		k_size += 4;
	}
	return 0;
}