#include <RcppArmadillo.h>
#include "family.h"
#include "linkfunctions.h"
#include "glm.h"

// [[Rcpp::depends(RcppArmadillo)]]

std::unique_ptr<Link::LinkFunction> link_from_string(const std::string& link_name) {
  if (link_name == "logit") {
    std::unique_ptr<Link::LinkFunction> ptr(new Link::Logit());
    return ptr;
  } else if (link_name == "identity") {
    std::unique_ptr<Link::LinkFunction> ptr(new Link::Identity());
    return ptr;
  } else if (link_name == "log") {
    std::unique_ptr<Link::LinkFunction> ptr(new Link::Log());
    return ptr;
  } else if (link_name == "inverse") {
    std::unique_ptr<Link::LinkFunction> ptr(new Link::Inverse());
    return ptr;
  } else if (link_name == "probit") {
    std::unique_ptr<Link::LinkFunction> ptr(new Link::Probit());
    return ptr;
  } else if (link_name == "sqrt") {
    std::unique_ptr<Link::LinkFunction> ptr(new Link::Sqrt());
    return ptr;
  }
  Rcpp::stop("Link function not available.");
}

template<class FamilyClass>
inline Rcpp::XPtr<FamilyClass> make_family(std::string link) {
  auto l = link_from_string(link);
  auto* family = new FamilyClass(l);
  Rcpp::XPtr<FamilyClass> pointer(family, true);
  return pointer;
}

// [[Rcpp::export]]
Rcpp::XPtr<Family::Gaussian> rcpp_make_gaussian(std::string link) {
  return make_family<Family::Gaussian>(link);
}

// [[Rcpp::export]]
Rcpp::XPtr<Family::Binomial> rcpp_make_binomial(std::string link) {
  return make_family<Family::Binomial>(link);
}

// [[Rcpp::export]]
Rcpp::XPtr<Family::Poisson> rcpp_make_poisson(std::string link) {
  return make_family<Family::Poisson>(link);
}

// [[Rcpp::export]]
arma::mat rcpp_glm_fit(const arma::mat& X, const arma::colvec& y,
                  Rcpp::XPtr<Family::ExponentialFamily> family,
                  int maxit, double tol) {
  return glm_fit(X, y, *family, maxit, tol);
}

// You can include R code blocks in C++ files processed with sourceCpp
// (useful for testing and development). The R code will be automatically
// run after the compilation.
//

/*** R
X <- model.matrix(mpg ~ 1 + hp + drat + cyl, data = mtcars)
y <- mtcars$mpg
glm_fit_gaussian_identity(X, y, 25, 1e-10)
*/

/*** R
# X <- model.matrix(I(mpg < 21) ~ -1 + hp + drat + cyl, data = mtcars)
# y <- mtcars$mpg < 21
# coef(glm.fit(X, y, family = binomial()))
# glm_fit_binomial_logit(X, y, 25, 1e-10)
*/
