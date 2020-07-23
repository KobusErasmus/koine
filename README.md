# koine
A command-line program to help you learn Koine (New Testament) Greek

# Note
This program is still being developed.

# Installation
1) Clone this repository.
2) Change directory into the cloned directory.
3) Compile the source with a C compiler, such as GCC.
4) (Optional) make a link to the compiled program in a recoginised path, such as /usr/local/bin

Example:
```
git clone https://github.com/KobusErasmus/koine ; cd koine ; gcc -O3 -o koine src/koine.c ; sudo ln -s $PWD/koine /usr/local/bin/koine
```

# Usage
Run the program without any arguments to see the options, which
are currently as follows:
```
Usage: koine OPTION
    -a      show alphabet
    -A      show alphabet with extra details
    -at     take a test on the alphabet
    -c      show cases
    -ct     take a test on the cases
    -h      show this help file
```
