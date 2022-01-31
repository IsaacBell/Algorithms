# References

- https://codeforces.com/blog/entry/62690
- https://codeforces.com/blog/entry/62792

# Definition

Experiment: an acitivity w/ an outcome

Random Var: real-valued var whose val is the outcome of the experiment

EV: If I conduct an experiment, what's the most likely outcome?

MATHEMATICAL DEFINITION:
If I conduct the experiment N times (e1, e2, ...en) Let the outcomes be x1, x2, x3, ..., xn.

# Example w/ Formula

Let's say we bought a lottery ticket for 2$. We will win 10$ with probability 10%, and 20$ with p-bility 2%. On average, it gives us 0.1·10 + 0.02·20 = 1.4, so we are worse off after buying the ticket. The computed average is called the expected value.

The expected value (EV, expectation) is the average value of an event/experiment.

For example, EV of the number of pips rolled on a 6-sided die is 3.5:

E(X) = Σ( P(w) * X(w) ) = 1/6*1 + 1/6*2 + 1/6*3 + 1/6*4 + 1/6*5 + 1/6*6

## Linearity of EV

E(X + Y) = E(X) + E(Y)

# Contribution to the sum

When looking for sum over many possibilities, consider every el and count how many times it'll be added to the answer.

