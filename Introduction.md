# Introduction #

A C/C++ Library for computing minimum cost weighted matching.


# Details #
Given a weighted bipartite graph G =(U,V,E) and a non-negative cost function C = cij associated with each edge  (i,j)&isin;E, the problem of finding a match M &sub; E such that minimizes &sum; cpq|(p,q) &isin; M, is a very important problem this problem is a classic example of Combinatorial Optimization, where a optimization problem is solved iteratively by solving an underlying combinatorial problem. This problem is also known as the assignment problem.

The techniques developed in the Hungarian method assumes that the representation of the underlying bipartite graph is dense and thus emphasizes on the asymptotic complexity of computing the shortest augmenting path which is O((|V|+|U| +|E|)log(|V|+|U|)). However in practice this worst case asymptotic bound was never hit especially in case of the sparse representation of the underlying bipartite graph. In practice we found that the runtime (cputime) of the algorithm is dominated by the time to update the dual variables rather than the time to compute the shortest augmenting path. In the original algorithm techniques to update the dual variables are ignored totally and hence the updating of the dual variables need an asymptotic time of O(|U|+|V|+|E|) , in this work we update the dual variables only in O(|V|+|U|) thus improving the performance of solving the assignment problem by a great extent.

We encountered this problem in the context of building efficient numerically stable linear solvers which solve equations of the form Ax = b. It has been an accepted fact that permuting the matrix A so that the elements along the diagonal of A are large is a desired property. Weighted bipartite graph matching is used extensively to permute the row/column's of the matrix A so that its closely diagonally dominant.