% Generated by roxygen2: do not edit by hand
% Please edit documentation in R/ctmcProbabilistic.R
\name{freq2Generator}
\alias{freq2Generator}
\title{Returns a generator matrix corresponding to frequency matrix}
\usage{
freq2Generator(P, t = 1, method = "QO", logmethod = "Eigen")
}
\arguments{
\item{P}{relative frequency matrix}

\item{t}{(default value = 1)}

\item{method}{one among "QO"(Quasi optimaisation), "WA"(weighted adjustment), "DA"(diagonal adjustment)}

\item{logmethod}{method for computation of matrx algorithm (by default : Eigen)}
}
\value{
returns a generator matix with same dimnames
}
\description{
The function provides interface to calculate generator matrix corresponding to 
a frequency matrix and time taken
}
\examples{
sample <- matrix(c(150,2,1,1,1,200,2,1,2,1,175,1,1,1,1,150),nrow = 4,byrow = TRUE)
sample_rel = rbind((sample/rowSums(sample))[1:dim(sample)[1]-1,],c(rep(0,dim(sample)[1]-1),1)) 
freq2Generator(sample_rel,1)

data(tm_abs)
tm_rel=rbind((tm_abs/rowSums(tm_abs))[1:7,],c(rep(0,7),1))
## Derive quasi optimization generator matrix estimate
freq2Generator(tm_rel,1)

}
\references{
E. Kreinin and M. Sidelnikova: Regularization Algorithms for
Transition Matrices. Algo Research Quarterly 4(1):23-40, 2001
}
