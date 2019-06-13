#ifndef glm_H
#define glm_H

#include "family.h"
#include "linkfunctions.h"

arma::mat glm_fit(const arma::mat& X, const arma::colvec& y,
                  const Family::ExponentialFamily& family,
                  int maxit, double tol);

#endif
