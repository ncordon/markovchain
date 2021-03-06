% Generated by roxygen2: do not edit by hand
% Please edit documentation in R/RcppExports.R
\name{ctmcFit}
\alias{ctmcFit}
\title{Function to fit a CTMC}
\usage{
ctmcFit(data, byrow = TRUE, name = "", confidencelevel = 0.95)
}
\arguments{
\item{data}{It is a list of two elements. The first element is a character
vector denoting the states. The second is a numeric vector denoting the
corresponding transition times.}

\item{byrow}{Determines if the output transition probabilities of the
underlying embedded DTMC are by row.}

\item{name}{Optional name for the CTMC.}

\item{confidencelevel}{Confidence level for the confidence interval
construnction.}
}
\value{
It returns a list containing the CTMC object and the confidence intervals.
}
\description{
This function fits the underlying CTMC give the state
  transition data and the transition times using the maximum likelihood
  method (MLE)
}
\details{
Note that in data, there must exist an element wise corresponding
  between the two elements of the list and that data[[2]][1] is always 0.
}
\examples{
data <- list(c("a", "b", "c", "a", "b", "a", "c", "b", "c"), c(0, 0.8, 2.1, 2.4, 4, 5, 5.9, 8.2, 9))
ctmcFit(data)

}
\references{
Continuous Time Markov Chains (vignette), Sai Bhargav Yalamanchi, Giorgio Alfredo Spedicato 2015
}
\seealso{
\code{\link{rctmc}}
}
\author{
Sai Bhargav Yalamanchi
}
