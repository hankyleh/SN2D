#ifndef VEC_H
#define VEC_H

#include <vector>


class vec2d {
private:
  std::vector<double> data;
  int I;
  int J;
  int size;

public:
  int get_I();
  int get_J();
  double &operator()(int i, int j);

  int get_size();
  void print_all();

  void operator=(vec2d vec); // copies data from 'vec'
  void operator=(std::vector<std::vector<double>> input);

  vec2d(std::vector<std::vector<double>> input); // copies data from input
  vec2d(const vec2d &vec);                       // copies data from input
  vec2d(int I_in, int J_in); // initialize with given size
  vec2d(int I_in, int J_in, double val); // initialize with given value
  vec2d();                   // zero vector of IxJ dimension
  void operator+=(double c);
  void operator+=(vec2d summand);
  vec2d operator+(double c);
  vec2d operator+(vec2d summand);

  void operator-=(double c);
  void operator-=(vec2d subtrahend);
  vec2d operator-(double c);
  vec2d operator-(vec2d subtrahend);

  void operator*=(double c);
  void operator*=(vec2d factor);
  vec2d operator*(double c);
  vec2d operator*(vec2d factor);

  void operator/=(double c);
  void operator/=(vec2d divisor);
  vec2d operator/(double c);
  vec2d operator/(vec2d divisor);

  void zero();        // set all elements to 0.0
  double linf_norm(); // L-infinity norm
  double l2_norm();
  double l1_norm();

  friend vec2d abs(vec2d vector);
};

vec2d abs(vec2d vector);



#endif