# Shape Run: Markov Chain Infinite Runner

<br />
<div align="center">
  <h3 align="center">Shape Run</h3>

  <p align="center">
    A C++ procedural platformer engine powered by stochastic Markov Chain transitions.
    <br />
    <br />
    <a href="https://github.com/Sr33kk0/Shape-Run/issues">Report Bug</a>
    ·
    <a href="https://github.com/Sr33kk0/Shape-Run/issues">Request Feature</a>
  </p>
</div>

<details>
  <summary>Table of Contents</summary>
  <ol>
    <li>
      <a href="#about-the-project">About The Project</a>
      <ul>
        <li><a href="#built-with">Built With</a></li>
      </ul>
    </li>
    <li>
      <a href="#getting-started">Getting Started</a>
      <ul>
        <li><a href="#prerequisites">Prerequisites</a></li>
        <li><a href="#installation">Installation</a></li>
      </ul>
    </li>
    <li><a href="#usage">Usage</a></li>
    <li><a href="#technical-excellence">Technical Excellence</a></li>
    <li><a href="#roadmap">Roadmap</a></li>
    <li><a href="#contact">Contact</a></li>
    <li><a href="#acknowledgments">Acknowledgments</a></li>
  </ol>
</details>

## About The Project

**Shape Run** is a data-driven 2D side-scrolling platformer developed as a "Something Awesome" extension for the FIT1045 Introduction to Programming unit at Monash University. This engine solves the common problem of predictable or "impossible" procedural level design by implementing a **7-state Markov Chain** to ensure that map transitions remain mathematically balanced and physically navigable.



### Built With

* **C++** (Core Engine & Logic)
* **SplashKit SDK** (Graphics, Input & Audio)

## Getting Started

To get a local copy up and running, follow these steps.

### Prerequisites

You must have the **SplashKit SDK** installed on your machine.
* [SplashKit Installation Instructions](https://splashkit.io/installation/)

### Installation

1. Download the project folder from this repository.
2. Open your terminal or command prompt in the project root directory.
3. Compile the project using the SplashKit Manager:
   ```sh
   skm clang++ main.cpp physics.cpp graphics.cpp chunkgen.cpp types.cpp -o shape-run
4. Run the executable:
   ```sh
   ./shape-run

## Usage

The game starts in a menu state. Press **SPACE** to begin the infinite run.
* **Objective**: Survive as long as possible while world speed increases over time.
* **Mechanics**: Navigate through varying gravity states (Normal, Inverted) and flight modes (Flappy) triggered by portals.
* **Memory Management**: The engine automatically performs "garbage collection" on off-screen obstacles using a custom `dynamic_array` to maintain a low memory footprint during infinite play.



## Technical Excellence

This project demonstrates several advanced programming concepts beyond the standard introductory curriculum:

* **Stochastic Algorithmic Design**: Utilizes a 2D transition matrix to determine the sequence of map chunks based on conditional probability.
* **Manual Memory Management**: Features a custom-built `dynamic_array` template struct with manual heap allocation (`new`/`delete`) to handle obstacle data.
* **Mathematical Validation**: Includes a `calculate_stationary()` function that runs a Monte Carlo simulation of 1,000 iterations to verify the balance of the probability matrix.
* **Modular Architecture**: Separates concerns into distinct modules for Physics, Graphics, Logic, and Data, facilitating easier debugging and scalability.



## Roadmap

- [x] Implement 7-state Markov Chain Logic
- [x] Create 21 unique map chunks in text format for procedural loading
- [x] Build custom Dynamic Array template for manual heap management
- [ ] Add persistent High Score tracking via external file I/O
- [ ] Implement a GUI-based Level Editor for custom chunk creation

## Contact

**Ho Shou Yee (Daniel)** - Bachelor of Computer Science Student at Monash University  
Project Link: [https://github.com/Sr33kk0/Shape-Run](https://github.com/Sr33kk0/Shape-Run)

## Acknowledgments

* [Monash University FIT1045 Teaching Team](https://www.monash.edu/)
