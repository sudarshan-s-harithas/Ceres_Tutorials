/*

Sample code for Pose Graph Optimization

*/


#include "ceres/ceres.h"
#include "glog/logging.h"
#include <Eigen/Dense>

using ceres::AutoDiffCostFunction;
using ceres::CostFunction;
using ceres::Problem;
using ceres::Solve;
using ceres::Solver;




struct Sample_BA_1D {

  Sample_BA_1D( Eigen::VectorXd predictions_x )
      : predictions_x(predictions_x){}

  template <typename T>
  bool operator()(const T* const state,
                  T* residuals) const {

  	Eigen::MatrixXd InvCovar(6, 6) ; 

  	InvCovar << 100 , 0 ,0,0,0 , 0,
  	0, 100,0,0,0,0,
  	0,0,100,0,0 ,0,
  	0,0,0,100,0,0,
  	0,0,0,0, 100,0,
  	0,0,0,0,0,1000 ;

  	residuals[0] = (state[0] - predictions_x).transpose() *InvCovar* (state[0] - predictions_x) ;

    return true;
  }

   // Factory to hide the construction of the CostFunction object from
   // the client code.

   static ceres::CostFunction* Create(const Eigen::VectorXd predictions_x ) {
     return (new ceres::AutoDiffCostFunction<Sample_BA_1D, 6 , 1 >(
                 new Sample_BA_1D(predictions_x) ) );
   }

  Eigen::VectorXd predictions_x ;

};


int main(int argc, char** argv) {

	int Total_Number_of_States  =  5 ;

	Eigen::VectorXd States(6); 
	States << 0 , 1.1 , 2.1 , 3.2 , 0.5 ,0.0 ; 
	Eigen::VectorXd Predictions(6) ; 
	Predictions <<  0 , 1.1 , 2.1 , 3.2 , 0.0 , 0.0 ;

	ceres::Problem problem;

	ceres::CostFunction* cost_function =
	Sample_BA_1D::Create( Predictions ) ;

	problem.AddResidualBlock(cost_function,
                           nullptr /* squared loss */,
                           &States  );

	ceres::Solver::Options options;
	options.linear_solver_type = ceres::DENSE_SCHUR;
	options.minimizer_progress_to_stdout = true;
	ceres::Solver::Summary summary;
	ceres::Solve(options, &problem, &summary);
	std::cout << summary.FullReport() << "\n";

}







