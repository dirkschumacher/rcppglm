#' Gaussian family
#'
#' @param link the link function
#'
#' @export
gaussian_family <- function(link = "identity") {
  link <- match.arg(link, c("identity", "inverse", "log"))
  rcpp_make_gaussian(link)
}

#' Binomial family
#'
#' @param link the link function
#'
#' @export
binomial_family <- function(link = "logit") {
  link <- match.arg(link, c("logit", "probit", "cauchit"))
  rcpp_make_binomial(link)
}

#' Poisson family
#'
#' @param link the link function
#'
#' @export
poisson_family <- function(link = "log") {
  link <- match.arg(link, c("log", "identity", "sqrt"))
  rcpp_make_poisson(link)
}
