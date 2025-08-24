#include "pixels.h"
#include "lodepng.h"
#include <fstream>
#include <cmath>

Pixels::Pixels(int columns, int rows)
  :columns{columns}, rows{rows}, values(columns*rows) {}
Pixels::Pixels()
  :columns{1}, rows{1}, values(1) {}
const Color& Pixels::operator()(int row, int col) const {
    return values[row * columns + col];
}
Color& Pixels::operator()(int row, int col) {
  return values[row * columns + col];
}
void Pixels::operator=(const Pixels& pixels) {
  rows = pixels.rows;
  columns = pixels.columns;
  values = pixels.values;
}

void Pixels::save_ppm(const std::string& filename) {
  std::ofstream output(filename); 
  if(!output) {
    throw std::runtime_error("Cannot open output file: " + filename);
  }
  output << "P3\n" << columns << ' ' << rows << "\n255";
  for(auto [r, g, b] : values) {
    output << '\n' << to_color<unsigned>(r) << ' ' << to_color<unsigned>(g) << ' ' << to_color<unsigned>(b);
  }
}

void Pixels::save_png(const std::string& filename) {
  std::ofstream output(filename); 
  if(!output) {
    throw std::runtime_error("Cannot open output file: " + filename);
  } 
  std::vector<unsigned char> data; 
  for (auto c : values) { 
    data.push_back(to_color<unsigned char>(c.x)); 
    data.push_back(to_color<unsigned char>(c.y)); 
    data.push_back(to_color<unsigned char>(c.z)); 
    data.push_back(255); 
  } 

  unsigned error = lodepng::encode(filename, data, columns, rows);
  if (error) { 
    throw std::runtime_error(lodepng_error_text(error)); 
  }
}

double gamma_correction(double value) {
  // double gamma = 2.2;
  double gamma = 1.0;
  return std::pow(value, 1/gamma);
}
