/*

The objective of this code is to introduce the readers to the structure
in which the program is be written to solve for the Bundle Adjustment.


What is different from the previus programs ?

In Bundle Adjustment there would be two parameters, a predicted value and an
observed value. The state is to be updated the difference between the predictions 
and observations is minimized. (Unlike the prevous code where the objective was
to minimize an anlytical cost function).

So how do we structure the program such that residual takes in predicted and observed measurments
and returns the updated state. 

Consider a simple example with an identiy state transition. 

*/

#include "ceres/ceres.h"
#include "glog/logging.h"
using ceres::AutoDiffCostFunction;
using ceres::CostFunction;
using ceres::Problem;
using ceres::Solve;
using ceres::Solver;



struct Sample_BA_1D {
  Sample_BA_1D(double observed_x )
      : observed_x(observed_x){}

  template <typename T>
  bool operator()(const T* const state,
                  T* residuals) const {

  	residuals[0] = state[0] - observed_x ;

    return true;
  }

   // Factory to hide the construction of the CostFunction object from
   // the client code.

   static ceres::CostFunction* Create(const double observed_x ) {
     return (new ceres::AutoDiffCostFunction<Sample_BA_1D, 1 , 1 >(
                 new Sample_BA_1D(observed_x) ) );
   }

  double observed_x;
};



int main(int argc, char** argv) {

	google::InitGoogleLogging(argv[0]);

	int TotalNumber_of_observations = 5 ; 
	
	double Observations[TotalNumber_of_observations] = { 0 , 2.1 , 4.1 , 6.2 , 2.5 }; 

	double states[ TotalNumber_of_observations] = { 0 , 1.1 , 2.1 , 3.2 , 0.5 };

	double *state ;
	double *obs;
	state = states ; 
	obs = Observations ; 

	ceres::Problem problem;


	for (int i = 0; i < TotalNumber_of_observations ; i++ ) {

		ceres::CostFunction* cost_function =
		Sample_BA_1D::Create( Observations[i] ) ;

		problem.AddResidualBlock(cost_function,
                           nullptr /* squared loss */,
                           (state + i )  );
	}

	ceres::Solver::Options options;
	options.linear_solver_type = ceres::DENSE_SCHUR;
	options.minimizer_progress_to_stdout = true;
	ceres::Solver::Summary summary;
	ceres::Solve(options, &problem, &summary);
	std::cout << summary.FullReport() << "\n";

	for( int i =0 ; i < TotalNumber_of_observations  ;  i++){

		std::cout << *(state +i ) << std::endl;
	}


}
