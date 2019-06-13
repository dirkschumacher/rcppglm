#include "glm.h"


// Based on the algorithm on page 137:
// Arnold, T., Kane, M., & Lewis, B. W. (2019). A Computational Approach to Statistical Learning. CRC Press.
arma::mat glm_fit(const arma::mat& X, const arma::colvec& y,
                  const Family::ExponentialFamily& family,
                  int maxit, double tol) {
  const int n_cols = X.n_cols;
  const int n_rows = X.n_rows;
  arma::mat Q, R;
  arma::colvec s = arma::zeros<arma::colvec>(n_cols);
  arma::colvec s_old;
  arma::colvec eta = arma::ones<arma::colvec>(n_rows);
  arma::qr_econ(Q, R, X);
  for (int i = 0; i < maxit; i++) {
    s_old = s;
    const arma::colvec mu = family.link_inverse(eta);
    const arma::colvec mu_p = family.link_mu_eta(eta);
    const arma::colvec z = eta + (y - mu) / mu_p;
    const arma::colvec W = arma::square(mu_p) / family.variance(mu);
    const arma::mat C = arma::chol(Q.t() * (Q.each_col() % W));
    const arma::colvec s1 = arma::solve(arma::trimatl(C.t()), Q.t() * (W % z));
    s = arma::solve(arma::trimatu(C), s1);
    eta = Q * s;

    const bool is_converged = std::sqrt(arma::accu(arma::square(s - s_old))) < tol;
    if (is_converged) break;
  }
  return arma::solve(arma::trimatu(R), Q.t() * eta);
}
