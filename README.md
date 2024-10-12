# Burrows-Wheeler Transform
The Burrows-Wheeler Transform is a lossless compression algorithm best suited for text with repetitive data. It is used with run-length encode compression.

## How to run (windows/unix/macOS)

1) Clone the repository in desired directory
 ```bash
 git clone https://github.com/ttcpavle/Burrows-Wheeler-Transform.git
 ```
2) Navigate to build directory
3) Run:
```bash
cmake ..
```

After those steps:
- If you are using windows, open the `BurrowsWheelerTransform.sln` solution (if visual studio was selected compiler). Select the BurrowsWheelerTransform as startup project and run. Header files should appear in solution explorer under Header files. HINT: change mode from debug to release for better performance.
- If you are using linux, run generated files for building a project. If cmake generated makefile, run `make` and than run the executable `./BurrowsWheelerTransform`
<p>
Required software: <br>
Cmake installation: https://www.youtube.com/watch?v=8_X5Iq9niDE <br>
Git installation: https://www.youtube.com/watch?v=JgOs70Y7jew <br>
</p>
