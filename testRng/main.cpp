

#include <iostream>
#include <cstdio>

#include "openeaagles/base/Statistic.h"

#include "openeaagles/base/Rng.h"
#include "openeaagles/base/distributions/Uniform.h"
#include "openeaagles/base/distributions/Pareto.h"
#include "openeaagles/base/distributions/Lognormal.h"
#include "openeaagles/base/distributions/Exponential.h"

namespace oe {

// this test is to match original Mersenne Twister output
void testValidation()
{
  unsigned int init[4] = {0x123, 0x234, 0x345, 0x456}, length = 4;
  base::Rng irand(init, length); // 32-bit int generator
  base::Rng drand; // double in [0, 1) generator, already init

  std::printf("1000 32-bit integer random numbers:\n");
  for (int i = 0; i < 1000; ++i) {
    std::printf("%10u ", irand.drawInt32());
    if ((i % 5) == 4) std::printf("\n");
  }
  std::printf("\n1000 random numbers in [0, 1):\n");
  for (int i = 0; i < 1000; ++i) {
    std::printf("%10.8f ", drand.drawHalfOpen());
    if ((i % 5) == 4) std::printf("\n");
  }
  return;
}

//
void testUniform()
{
  base::Uniform rng;
  rng.setMin(0.0);
  rng.setMax(10.0);

  for (int i = 0; i < 5000; ++i) {
    std::printf("%10.8f ", rng.draw());
    std::printf("\n");
  }
  return;
}

void testPareto()
{
  base::Pareto rng;
  rng.setAlpha(5.0);
  rng.setBeta(8.0);

  for (int i = 0; i < 5000; ++i) {
    std::printf("%10.8f ", rng.draw());
    std::printf("\n");
  }
  return;
}

void testLognormal()
{
  base::Lognormal rng;
  rng.setSigma(1.0);
  rng.setMu(4.0);
  rng.setGamma(5.0);     // location

  for (int i = 0; i < 5000; ++i) {
    std::printf("%10.8f ", rng.draw());
    std::printf("\n");
  }
  return;
}

void testExponential()
{
  base::Exponential rng;
  base::Statistic stats;

  //rng.setMean(10);       // 1/lambda
  rng.setLambda(1);
  rng.setGamma(0);     // location

  stats.clear();
  for (int i = 0; i < 1000; ++i) {
    double draw = rng.draw();
    //std::printf("%10.8f ", draw);
    //std::printf("\n");
    stats.sigma(draw);
  }

  std::cout << "Mean     : " << stats.mean() << std::endl;
  std::cout << "Variance : " << stats.variance() << std::endl;
  std::cout << "StdDev   : " << stats.stdDev() << std::endl;
  double ci = (1.96*stats.stdDev()) / std::sqrt(static_cast<double>(stats.getN()));
  std::cout << "CI : " << ci << std::endl;

  return;
}

} // end namespace oe

int main(int argc, char* argv[])
{
  oe::testValidation();
  //oe::testLognormal();
  //oe::testPareto();
  //oe::testExponential();
  return 0;
}

