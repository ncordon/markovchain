// [[Rcpp::depends(RcppArmadillo)]]
#include <RcppArmadillo.h>
#include <unordered_set>
#include <unordered_map>
#include <string>
#include <iostream>
using namespace Rcpp;
using namespace arma;
using namespace std;


bool approxEqual(const double& a, const double& b) {
  if (a >= b)
    return (a - b) <= 1E-7;
  else
    return approxEqual(b, a);
}


bool approxEqual(const cx_double& a, const cx_double& b){
  double x = a.real() - b.real();
  double y = a.imag() - b.imag();
  
  return (x*x - y*y) <= 1E-14;
}


// This method receives the output of communicatingClasses(object) and object@states
// and checks that in fact the communicating classes are a partition of states
// Is a method agnostic on whether the Markov Chain was given by rows or columns
// [[Rcpp::export(.testthatIsPartitionRcpp)]]
bool isPartition(List commClasses, 
                 CharacterVector states) {
  int n = states.size();
  unordered_set<string> used;
  unordered_set<string> originalStates;
  int numClassStates = 0;
  bool partition = true;
  
  for (auto state : states)
    originalStates.insert((string) state);
  
  // Check that the union of the classes is
  // states and they do not overlap
  for (int i = 0; i < commClasses.size() && partition; ++i) {
    CharacterVector currentClass = commClasses(i);
    numClassStates += currentClass.size();

    for (int j = 0; j < currentClass.size() && partition; ++j) {
      string state = (string) currentClass(j);
      partition = used.count(state) == 0 && originalStates.count(state) > 0;
      used.insert(state);
    }
  }

  return partition && numClassStates == n;
}

// This is simply a method that checks the following recurrence,
// naming p = probs, f = hitting, it checks:
//
// f(i, j) = p(i, j) + ∑_{k ≠ j} p(i, k) f(k, j)
//
// where p are the transitionMatrix probs and hitting are the
// hitting probabilities for the Markov Chain associated to
// probs. byrow indicates whether probs is an stochastic matrix
// by rows or by columns. tolerance is the tolerance we want to
// check against (values must sufficiently close to 1)
// [[Rcpp::export(.testthatAreHittingRcpp)]]
bool areHittingProbabilities(NumericMatrix probs, 
                             NumericMatrix hitting,
                             bool byrow,
                             double tolerance) {
  if (!byrow) {
    probs = transpose(probs);
    hitting = transpose(hitting);
  }
  
  int numStates = probs.nrow();
  bool holds = true;
  double result;
  
  for (int i = 0; i < numStates && holds; ++i) {
    for (int j = 0; j < numStates && holds; ++j) {
      result = 0;
      
      for (int k = 0; k < numStates; ++k)
        if (k != j)
          result -= probs(i, k) * hitting(k, j);
        
      result += hitting(i, j) - probs(i, j);
      holds = abs(result) < tolerance;
    }
  }
  
  return holds;
}

// [[Rcpp::export(.testthatRecurrentAreHittingRcpp)]]
bool recurrentAreHitting(List recurrentClasses,
                         NumericMatrix hitting,
                         CharacterVector states,
                         bool byrow) {
  if (!byrow)
    hitting = transpose(hitting);
  
  unordered_map<string, int> stateToIndex;
  bool correct = true;
  int n = states.size();
  
  for (int i = 0; i < n; ++i)
    stateToIndex[(string) states(i)] = i;
  
  for (CharacterVector recClass : recurrentClasses) {
    unordered_set<int> classIndexes;
    
    for (auto state : recClass)
      classIndexes.insert(stateToIndex[(string) state]);
    
    for (int i : classIndexes) {
      for (int j = 0; j < n; ++j) {
        if (classIndexes.count(j) > 0)
          correct = correct && approxEqual(hitting(i, j), 1);
        else
          correct = correct && approxEqual(hitting(i, j), 0);
      }
    }
  }
  
  return correct;
}


// [[Rcpp::export(.testthatHittingAreOneRcpp)]]
bool hittingProbsAreOne(NumericMatrix matrix) {
  bool allOne = true;
  int nrow = matrix.nrow();
  int ncol = matrix.ncol();
  
  for (int i = 0; i < nrow && allOne; ++i)
    for (int j = 0; j < ncol && allOne; ++j)
      allOne = approxEqual(matrix(i, j), 1);
  
  return allOne;
}