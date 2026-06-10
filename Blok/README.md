# Blok — Discounted Least Squares

An exploration of discounted (exponentially weighted) least squares fitting on time-series
data, inspired by the work of **Hendrik J. Blok** (UBC physics) on stock-market simulations
and time-series dynamics. Discounted least squares weights recent observations more heavily
than older ones, making it suited to non-stationary series where the recent past matters most.

> Early-stage. The demo (`DiscountedLeastSquares/`) is currently a stub — it builds and runs
> but does not yet implement the fit. The sample dataset (`data/staking.csv`) is in place to
> drive the implementation. Source papers are in [`doc/`](doc/).

## Getting Started

These instructions get the subproject building and running on your local machine. It builds
standalone, or as part of the [root UBC project](../README.md).

### Prerequisites

- CMake 3.26+
- A C++23-capable compiler (developed on Apple M1 Max, macOS Sonoma, CLion 2023)

### Installing

From this directory:

```
mkdir build && cd build
cmake ..
make
```

Run the demo:

```
./DiscountedLeastSquares/dls
```

Currently this prints a placeholder line. The dataset it will fit, `data/staking.csv`, is a
tab-separated daily time series:

```
Date	Staked
21/09/2023 00:00:00	4719.70
22/09/2023 00:00:00	4728.52
```

## Running the tests

No tests yet. When the fit is implemented, behaviour tests belong alongside it (see the
`Bridson/unittests/` subproject for the `ctest` pattern used elsewhere in this repo).

## Built With

- C++23
- CMake

## References

Source papers (in [`doc/`](doc/)):

- `blok97b.pdf`
- `On_the_nature_of_the_stock_market_Simulations_and_.pdf` — Blok & Bergersen
- `Scale-free_extinction_dynamics_in_spatially_struct.pdf`
- `Blok-2004-ParallelPoisson-Updatinginsimulationsofparallel2.pdf`

## Acknowledgments

- Hendrik J. Blok, whose research this demo explores
- Part of the [UBC](../README.md) meta-repository of demos inspired by UBC researchers
