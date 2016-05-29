# erandu
Extended version of the RANDU random number generator
RANDU with the Bays-Durham shuffle, runs for 5.41e+2639 cycles
beforen repeating.  The Bays-Durham shuffle eliminates many of the
weaknesses of the RANDU algorithm.  It passes the dieharder and
TestU01 tests with expected results.

erandu proves that adding the Bays-Durham shuffle to the RANDU
algorithm strengthens the random number generator and puts it on
a par with taus, KISS, and Mersenne Twister.  The only caveat is
that the lower 16 bits, especially the lower 4 bits, are not
random.  The higher 8 bits pass the tests for randomness.

