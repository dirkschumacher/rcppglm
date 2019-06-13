#include <RcppArmadillo.h>
#include "family.h"

namespace Family {

arma::colvec Gaussian::variance(const arma::colvec& mu) const {
  return arma::ones<arma::colvec>(mu.n_elem);
}

arma::colvec Family::Binomial::variance(const arma::colvec& mu) const {
  return mu % (1.0 - mu);
}

arma::colvec Family::Poisson::variance(const arma::colvec& mu) const {
  return mu;
}

arma::colvec Family::Gamma::variance(const arma::colvec& mu) const {
  return arma::square(mu);
}

}
