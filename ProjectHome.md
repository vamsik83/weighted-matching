<p>Given a weighted bipartite graph <b>G =(U,V,E)</b> and a non-negative cost function <b>C = c<sub>ij</sub></b> associated with each edge <b> (i,j)&isin;E</b>, the problem of finding a match <b>M &sub; E</b> such that minimizes <b>&sum; c<sub>pq</sub>|(p,q) &isin; M</b>, is a very important problem this problem is a classic example of Combinatorial Optimization, where a optimization problem is solved iteratively by solving an underlying combinatorial problem. This problem is also known as the assignment problem.<br>
</p>

<p>
The techniques developed in the Hungarian method assumes that the representation of the underlying bipartite graph is dense and thus emphasizes on the asymptotic complexity of computing the shortest augmenting path which is <b>O((|V|+|U| +|E|)log(|V|+|U|))</b>. However in practice this worst case asymptotic bound was never hit especially in case of the sparse representation of the underlying bipartite graph. In practice we found that the runtime (cputime) of the algorithm is dominated by the time to update the dual variables rather than the time to compute the shortest augmenting path. In the original algorithm techniques to update the dual variables are ignored totally and hence the updating of the dual variables need an asymptotic time of <b>O(|U|+|V|+|E|)</b> , in this work we update the dual variables only in <b>O(|V|+|U|)</b> thus improving the performance of solving the assignment problem by a great extent.<br>
</p>


<p>
We encountered this problem in the context of building efficient numerically stable linear solvers which solve equations of the form <b>Ax = b</b>. It has been an accepted<br>
fact that permuting the matrix <b>A</b> so that the elements along the diagonal of <b>A</b> are large is a desired property. Weighted bipartite graph matching is used extensively to permute the row/column's of the matrix <b>A</b> so that its closely diagonally dominant.<br>
</p>