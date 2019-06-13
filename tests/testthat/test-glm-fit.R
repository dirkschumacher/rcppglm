test_that("linear regression works", {
  X <- model.matrix(mpg ~ 1 + hp + drat + cyl, data = mtcars)
  y <- mtcars$mpg
  family <- gaussian_family(link = "identity")
  res <- as.numeric(glm_fit(X, y, family))
  expected <- coef(glm.fit(X, y, family = stats::gaussian()))
  expect_equivalent(res, expected)
})

test_that("log gaussian works", {
  X <- model.matrix(mpg ~ 1 + hp + drat + cyl, data = mtcars)
  y <- mtcars$mpg
  family <- gaussian_family(link = "log")
  res <- as.numeric(glm_fit(X, y, family))
  expected <- coef(glm.fit(X, y, family = stats::gaussian("log")))
  expect_equivalent(res, expected, tolerance = 1e-7)
})

test_that("inverse gaussian works", {
  X <- model.matrix(wt ~ 1 + hp + cyl, data = mtcars)
  y <- mtcars$wt
  family <- gaussian_family(link = "inverse")
  res <- as.numeric(glm_fit(X, y, family))
  expected <- coef(glm.fit(X, y, family = stats::gaussian("inverse")))
  expect_equivalent(res, expected, tolerance = 1e-7)
})

test_that("logistic regression works", {
  X <- model.matrix(I(mpg < 20) ~ -1 + hp + drat + cyl, data = mtcars)
  y <- mtcars$mpg < 20
  family <- binomial_family(link = "logit")
  res <- as.numeric(glm_fit(X, y, family))
  expected <- coef(glm.fit(X, y, family = stats::binomial(link = "logit")))
  expect_equivalent(res, expected)
})

test_that("probit regression works", {
  X <- model.matrix(I(mpg < 20) ~ -1 + drat + cyl, data = mtcars)
  y <- mtcars$mpg < 20
  family <- binomial_family(link = "probit")
  res <- as.numeric(glm_fit(X, y, family))
  expected <- coef(glm.fit(X, y, family = stats::binomial(link = "probit")))
  expect_equivalent(res, expected, tolerance = 1e-5)
})

test_that("poisson regression works", {
  X <- model.matrix(hp ~ -1 + drat + cyl, data = mtcars)
  y <- mtcars$hp
  family <- poisson_family(link = "log")
  res <- as.numeric(glm_fit(X, y, family))
  expected <- coef(glm.fit(X, y, family = stats::poisson(link = "log")))
  expect_equivalent(res, expected)
})

test_that("poisson identity regression works", {
  X <- model.matrix(hp ~ -1 + drat + cyl, data = mtcars)
  y <- mtcars$hp
  family <- poisson_family(link = "identity")
  res <- as.numeric(glm_fit(X, y, family))
  expected <- coef(glm.fit(X, y, family = stats::poisson(link = "identity")))
  expect_equivalent(res, expected, tolerance = 1e-6)
})

test_that("poisson sqrt regression works", {
  X <- model.matrix(hp ~ -1 + drat + cyl, data = mtcars)
  y <- mtcars$hp
  family <- poisson_family(link = "sqrt")
  res <- as.numeric(glm_fit(X, y, family))
  expected <- coef(glm.fit(X, y, family = stats::poisson(link = "sqrt")))
  expect_equivalent(res, expected, tolerance = 1e-7)
})
