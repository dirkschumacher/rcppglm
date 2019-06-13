
<!-- README.md is generated from README.Rmd. Please edit that file -->

# RcppGLM

<!-- badges: start -->

[![Lifecycle:
experimental](https://img.shields.io/badge/lifecycle-experimental-orange.svg)](https://www.tidyverse.org/lifecycle/#experimental)
<!-- badges: end -->

`RcppGLM` implements the GLM fitting algorithm in c++ using Armadillo.
It follows the code from \[1\]. Requires c++11 at the moment.

It is work in progress and mainly for learning purposes.

There are some numerical problems depending on the input. But a lot of
stuff seems to work already.

## Supported families and link functions

  - Gaussian (`gaussian_family`) (log, identity, inverse (fails at the
    moment `¯\_(ツ)_/¯`️))
  - Poisson (`poisson_family`) (log, sqrt, identity)
  - Binomial (`binomial_family`) (logit, probit)

## Example

Logistic regression:

``` r
library(RcppGLM)
X <- model.matrix(I(mpg < 20) ~ -1 + hp + drat + cyl, data = mtcars)
y <- mtcars$mpg < 20
family <- binomial_family(link = "logit")
glm_fit(X, y, family)
#>             [,1]
#> [1,]  0.12609238
#> [2,] -4.00405338
#> [3,] -0.03569851
```

Same as the R implementation:

``` r
coef(glm.fit(X, y, family = stats::binomial(link = "logit")))
#>         hp       drat        cyl 
#>  0.1260924 -4.0040534 -0.0356985
```

Poisson regression:

``` r
X <- model.matrix(hp ~ -1 + drat + cyl, data = mtcars)
y <- mtcars$hp
family <- poisson_family(link = "log")
glm_fit(X, y, family)
#>           [,1]
#> [1,] 0.6425100
#> [2,] 0.4078514
```

Same as the R implementation:

``` r
coef(glm.fit(X, y, family = stats::poisson(link = "log")))
#>      drat       cyl 
#> 0.6425100 0.4078514
```

## References

1: Arnold, T., Kane, M., & Lewis, B. W. (2019). A Computational Approach
to Statistical Learning. CRC Press.
