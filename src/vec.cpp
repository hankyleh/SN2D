#include <vec.h>
#include <vector>
#include <algorithm>
#include <cmath>

#include <iostream>

int vec2d::get_I() { return I; }
int vec2d::get_J() { return J; }

double& vec2d::operator()(int i, int j){
  return data[i*J + j];
}

int vec2d::get_size() { return size; }

vec2d::vec2d(std::vector<std::vector<double>> input) {
  I = input.size();
  J = input[0].size();
  size = I * J;

  for (int i = 0; i < I; i++) {
    for (int j = 0; j < J; j++) {
      data.push_back(input[i][j]);
    }
  }
}

vec2d::vec2d(const vec2d &vec) {
  I = vec.I;
  J = vec.J;
  size = vec.size;
  data = vec.data;
}

vec2d::vec2d(int I_in, int J_in) {
  I = I_in;
  J = J_in;
  size = I * J;
  std::vector<double> buffer(I_in * J_in, 0);
  data = buffer;
}

void vec2d::print_all() {
  for (int i = 0; i < I; i++) {
    for (int j = 0; j < J; j++) {
      std::cout << data[i * J + j] << " ";
    }
    std::cout << std::endl;
  }
}

void vec2d::operator =(vec2d vec){
  I = vec.I;
  J = vec.J;
  size = vec.size;
  data = vec.data;
}

void vec2d::operator+=(double c) {
  for (int s = 0; s < size; s++) {
    data[s] += c;
  }
}

void vec2d::operator+=(vec2d summand) {
  if (size != summand.size) {
    throw std::runtime_error(
        "Attempted to add to 'vec2d' objects of different sizes");
  }
  for (int s = 0; s < size; s++) {
    data[s] += summand.data[s];
  }
}

vec2d vec2d::operator+(double c) {
  vec2d result(*this);
  result += c;
  return result;
}

vec2d vec2d::operator+(vec2d summand) {
  if (size != summand.size) {
    throw std::runtime_error(
        "Attempted to add to 'vec2d' objects of different sizes");
  }
  vec2d result(*this);
  for (int s = 0; s < summand.size; s++) {
    result.data[s] += summand.data[s];
  }
  return result;
}

void vec2d::operator*=(double c) {
  for (int s = 0; s < size; s++) {
    data[s] *= c;
  }
}

void vec2d::operator*=(vec2d factor) {
  if (size != factor.size) {
    throw std::runtime_error(
        "Attempted to add to 'vec2d' objects of different sizes");
  }
  for (int s = 0; s < size; s++) {
    data[s] *= factor.data[s];
  }
}

vec2d vec2d::operator*(double c) {
  vec2d result(*this);
  result *= c;
  return result;
}

vec2d vec2d::operator*(vec2d factor) {
  if (size != factor.size) {
    throw std::runtime_error(
        "Attempted to add to 'vec2d' objects of different sizes");
  }
  vec2d result(*this);
  for (int s = 0; s < factor.size; s++) {
    result.data[s] *= factor.data[s];
  }
  return result;
}

void vec2d::zero() {
  for (int s = 0; s < size; s++) {
    data[s] = 0;
  }
}

double vec2d::linf_norm(){
    return *std::max_element(data.begin(), data.end());
}

double vec2d::l2_norm(){
    double result = 0;
    for (int s=0; s<size; s++){
        result += std::pow(data[s], 2);
    }
    return std::pow(result, 0.5);
}

double vec2d::l1_norm(){
    double result = 0;
    for (int s=0; s<size; s++){
        result += std::abs(data[s]);
    }
    return result;
}
