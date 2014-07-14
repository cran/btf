#include "individual.cpp"

// [[Rcpp::plugins("cpp11")]]

// [[Rcpp::export]]
Eigen::MatrixXd gdPBTF(const int& iter,
                        const Eigen::Map<Eigen::VectorXd>& y, 
                        const int& k, const Eigen::MappedSparseMatrix<double>& D, 
                       const double& alpha, const double& rho, const bool& debug) {

  // initialize btf object
  individual *btf; double a;
  if ( alpha < 0.0 ) a = 1.0; else a = alpha;
  btf = new individual(y, k, D, a, rho); 

  // initialize matrix of posterior draws
  int P = btf->n + btf->nk + 3; // count number of parameters
  Eigen::MatrixXd history = Eigen::MatrixXd::Zero(iter, P); 

  // runs sampler
  for (int i=0; i<iter; ++i) {
    btf->upBeta(); btf->upS2();
    btf->upLambda(); btf->upOmega(); 

    // alpha as parameter
    if ( alpha < 0.0 ) btf->upA(); 

    history.row(i) << btf->beta.transpose(), btf->s2, 
      btf->l, btf->o2.transpose(), btf->alpha;

    if ( debug ) {
      for (int j=0; j<P; ++j) {
        if ( std::isnan(history(i,j)) ) {
          Rcpp::Rcout << "Warning: watch out gdP!, nan @ (" <<  i << "," << j << ")" << std::endl;
          return history;
        }
      }      
    }
  }
  return history;
}