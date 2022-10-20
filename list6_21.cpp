#include <cstdio>

template <typename T>
T mean(const T* values, size_t length) {
   T result {};
   for (size_t i {}; i < length; i++) {
      result += values[i];
   }
   return result / length;
}

int main() {
   const double nums_d[] { 1.0, 2.0, 3.0, 4.0 };
   const double result = mean(nums_d, 4);
   printf("double: %f\n", result);
}