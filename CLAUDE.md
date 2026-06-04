UBC — CLAUDE.md
============================

A meta-repository of demos and implementations inspired by research from University of
British Columbia academics. Each subproject explores a concept from a researcher's
published work — a way to learn the underlying algorithms (sampling, stippling, energy
balance, phase transitions, least squares) by building them.

Project Structure
-----------------

The root `CMakeLists.txt` aggregates five independent subprojects via `add_subdirectory`:

| Subproject | Researcher | Topic | Demo dir |
| --- | --- | --- | --- |
| `Bergersen/` | Birger Bergersen | Phase transitions, statistical mechanics | `PhaseTransitions/` |
| `Blok/` | — | Discounted least squares | `DiscountedLeastSquares/` |
| `Bridson/` | Robert Bridson | Fast Poisson-disk sampling | `FastPoisson/` (+ `unittests/`) |
| `Harris/` | Sara Harris | Climate / energy balance | `EnergyBalance/` |
| `Secord/` | Adrian Secord | Weighted Voronoi stippling | `WeightedVoroniStippling/` |

Each subproject has its own `CMakeLists.txt` and (mostly) its own `README.md` — start in
the relevant subproject's README. `Bergersen`, `Bridson`, `Harris/EnergyBalance`, and
`Secord/WeightedVoroniStippling` have READMEs; `Blok` does not yet. `cmake-build-*/` are
CLion's generated build dirs (not source).

Environment
-----------

*   IDE: CLion 2023
*   Language: C++ (CMake projects)
*   Build system: CMake 3.26+ at the root (README notes 3.27+); each subproject builds
    independently
*   Key dependencies: per-subproject — see individual READMEs. Developed on Apple M1 Max,
    macOS Sonoma.

Building and Testing
--------------------

Build everything from the root:

```
mkdir build && cd build
cmake ..
make
```

Or build a single subproject from its own directory the same way. `Bridson/unittests/`
holds tests for the Poisson-disk sampler (run via `ctest` from that build). Most
subprojects are visual demos verified by running them.

Conventions
-----------

*   No comments unless the why is non-obvious
*   No speculative code — only implement what is needed right now
*   Commit messages: short, descriptive, imperative tense ("add Poisson-disk grid lookup" not "added" or "adding")
*   Each subproject is self-contained: its own `CMakeLists.txt`, demo dir, and README;
    new work belongs inside the relevant subproject, not the root
*   Keep per-subproject dependencies and datasets documented in that subproject's README

Current State
-------------

### Completed

*   Root CMake aggregation of all five subprojects
*   `Bergersen/PhaseTransitions`, `Bridson/FastPoisson` (with unit tests),
    `Harris/EnergyBalance`, `Secord/WeightedVoroniStippling`, and `Blok/DiscountedLeastSquares`

### In Progress

*   Nothing in flight

### Next

*   Add a `README.md` for `Blok` (and add it to the root README's project table)
*   Add a short description for each subproject and document per-subproject special
    dependencies / datasets
*   Document a "build all from the root" example in the top-level README

### Decisions Pending

*   None

Do Not Touch
------------

*   Nothing off limits at this time.

Pair Programming
----------------

*   Driver writes all code — navigator (Claude) does not write code unless explicitly asked
*   Navigator provides: direction, design decisions, code review, and course corrections
*   One step at a time — navigator waits for driver to confirm before moving to the next
*   Navigator confirms tests pass before suggesting the next step
*   Navigation is terse — no lengthy explanations unless explicitly asked
*   If navigator disagrees with an approach, say so once then follow the driver's lead

Karpathy Rules
--------------

All rules apply to every task unless explicitly overridden.

### Rule 1 — Think Before Coding

State assumptions explicitly. If uncertain, ask rather than guess. Present multiple interpretations when ambiguity exists. Push back when a simpler approach exists. Stop when confused. Name what's unclear.

### Rule 2 — Simplicity First

Minimum code that solves the problem. Nothing speculative. No features beyond what was asked. No abstractions for single-use code. Test: would a senior engineer say this is overcomplicated? If yes, simplify.

### Rule 3 — Surgical Changes

The driver should touch only what is necessary to make the current test pass. Don't "improve" adjacent code, comments, or formatting. Don't refactor what isn't broken. Match existing style. Navigator warns the driver if this rule is being broken.

### Rule 4 — Agree on Done Before Starting

Before implementing anything, both driver and navigator should agree on what done looks like. A failing test is the preferred success criterion. Don't start until done is defined.

### Rule 5 — Dropped

Original rule was written for agentic coding and does not apply to this pair programming model.

### Rule 6 — Know When to Stop

If the session is getting long or context feels stale, checkpoint before continuing. Summarise what's done, what's verified, what's next. Update CLAUDE.md to reflect current state, then commit before ending the session. A fresh session with good context beats a stale one with accumulated confusion.

### Rule 7 — Surface Conflicts, Don't Average Them

If two patterns contradict, pick one (more recent / more tested). Explain why. Flag the other for cleanup. Don't blend conflicting patterns.

### Rule 8 — Read Before You Write

Before adding code, read exports, immediate callers, shared utilities. "Looks orthogonal" is dangerous. If unsure why code is structured a way, ask.

### Rule 9 — Test Behaviours, Not Functionality

Tests verify what the code does from the outside, not how it does it internally. Tests must encode WHY the behaviour matters, not just WHAT it does. A test that can't fail when business logic changes is wrong.

### Rule 10 — Checkpoint After Every Significant Step

Summarize what was done, what's verified, what's left. Don't continue from a state you can't describe back. If you lose track, stop and restate.

### Rule 11 — Match the Codebase's Conventions, Even If You Disagree

Conformance > taste inside the codebase. If you genuinely think a convention is harmful, surface it. Don't fork silently.

### Rule 12 — Fail Loud

"Completed" is wrong if anything was skipped silently. "Tests pass" is wrong if any were skipped. Default to surfacing uncertainty, not hiding it.
