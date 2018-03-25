spreading-simulation
====================

This is an implementation of the Susceptible-Infected (SI-) epidemiologic model on a network. Powerful and extensive tools exist for this problem, e.g. graph-tool [https://git.skewed.de] for python. graph-tool has multiprocessing capabilities but is written with the Boost Graph Library.

With the datastructures available in modern C++, a much simpler implementation is possible using multimaps (C++11, C++17).

The code simulates deterministic spreading on a directed, unweighted graph. It can be easily adopted to other graphs and spreading dynamics.

