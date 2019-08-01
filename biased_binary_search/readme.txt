*** How to run, what you get ***

Edit " $i**0.5 " to some other sequence definition (or leave it as is).

Run the following in bash:

g++ solve.cpp -lpthread
function plotseq { gnuplot -p -e 'plot "/dev/stdin"'; }
perl -e 'for($i=10;$i<1000;$i+=10) { printf $i**0.5 . " \n"; }' | tee foo | plotseq ; cat foo | ./a.out | plotseq
rm foo

will then show two graphs. The first graph is simply a plot of the sequence a_1, ..., a_n that you've defined. The other graph shows numbers b_1, ..., b_n, which require a longer explanation.


Suppose we have an unknown number X uniformly distributed in {0, 1, ..., n-1}. The number X gives us a bit sequence of length n

Y = 0...01...1, where the last 0 occurs on position X.

Suppose we can query the value of Y(i) at cost a_i (defined by you). Then b_i is the total expected cost for determining X through queries, if the first query is i and every query from then on is optimally chosen.

*** Conclusion ***
So this is a model for understanding binary search in the case where different queries have different costs.
