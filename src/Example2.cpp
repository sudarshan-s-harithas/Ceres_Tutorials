/*

This example demonstrates the optimization of a multi variable function 

Consider a function with multiple variables as shown below 

f1(x) = 5*x1 + 10*x2
f2(x) = 15( x2 - x3)
f3(x) = 10( x1 - x2)^{2} 
f4(x) =  (x3 - x4 )^{2}

F(x) [ f1 , f2, f3 , f4]

A similar example is given in http://ceres-solver.org/nnls_tutorial.html#powell-s-function

*/

#include "ceres/ceres.h"
#include "glog/logging.h"
using ceres::AutoDiffCostFunction;
using ceres::CostFunction;
using ceres::Problem;
using ceres::Solve;
using ceres::Solver;


// Declaration of the Multi Variable Functions 

struct f1 {
  template <typename T>
  bool operator()(const T* const x1, const T* const x2, T* residual) const {

  	// std::cout << x2 << std::endl;
    residual[0] = 5.0*x1[0] + 10.0*x2[0];
    return true;
  }
};

struct f2 {
  template <typename T>
  bool operator()(const T* const x2, const T* const x3, T* residual) const {
    residual[0] = 15.0*( x2[0] - x3[0] );
    return true;
  }
};

struct f3 {
  template <typename T>
  bool operator()(const T* const x1, const T* const x2, T* residual) const {
    residual[0] = 10.0*(x1[0] - x2[0])*(x1[0] - x2[0]);
    return true;
  }
};

struct f4 {
  template <typename T>
  bool operator()(const T* const x3, const T* const x4, T* residual) const {
    residual[0] = (x3[0] - x4[0])*(x3[0] - x4[0]);
    return true;
  }
};




int main(int argc, char** argv) {

  google::InitGoogleLogging(argv[0]);

  // Initilize the optimization variable 

  double x1 =  3.0; double x2 = -1.0; double x3 =  0.0; double x4 = 1.0;


  Problem problem;

  // Initilize AutoDiff to the residual terms. 

  problem.AddResidualBlock(
  	new AutoDiffCostFunction<f1, 1, 1, 1>(new f1), nullptr, &x1, &x2);  
  // the < f1,1,1 > indicates that the function f1 has two inputs each of 1 dimension scalar and output is 1 dimension scalar

  problem.AddResidualBlock(
  	new AutoDiffCostFunction<f2, 1, 1, 1>(new f2), nullptr, &x2, &x3);

  problem.AddResidualBlock(
  	new AutoDiffCostFunction<f3, 1, 1, 1>(new f3), nullptr, &x1, &x2);

  problem.AddResidualBlock(
  	new AutoDiffCostFunction<f4, 1, 1, 1>(new f4), nullptr, &x3, &x4);

  // Run the solver!

  Solver::Options options;
  options.minimizer_progress_to_stdout = true;
  Solver::Summary summary;
  Solve(options, &problem, &summary);
  std::cout << summary.BriefReport() << "\n";
  std::cout << "x1 : " << x1 << "\n";
  std::cout << "x2 : " << x2 << "\n";
  std::cout << "x3 : " << x3 << "\n";
  std::cout << "x4 : " << x4 << "\n";
  return 0;
}
