# Lab 11 – Multiprocessing

**Name:** Emanuel Hernandez  
**Course:** CPE-2600  
**Section:** 111

## Description

This program generates 50 Mandelbrot images using multiple child processes. It uses `fork()` to create processes, `execl()` to run the Mandelbrot program, and `waitpid()` to wait for processes to finish.

The `-p` option controls how many processes run at the same time.

## Compiling and Running

Compile the programs:

```bash
make clean
make
```

Generate 50 images using 5 processes:

```bash
./mandelmovie -p 5
```

Create and play the movie:

```bash
ffmpeg -y -framerate 10 -i mandel%d.jpg -vf "fps=25" mandel.mpg
ffplay mandel.mpg
```

Start the movie at approximately frame 27:

```bash
ffplay -ss 2.7 mandel.mpg
```

## Runtime Results

The program was tested using 1, 2, 5, 10, and 20 processes with the `time` command.

| Processes | Runtime (seconds) |
|---|---|
| 1 | 228 |
| 2 | 124 |
| 5 | 62 |
| 10 | 38 |
| 20 | 37 |

## Runtime Graph

![Runtime Graph](runtime.png)

## Discussion

Using multiple processes can reduce execution time because several images can be generated at once. However, using too many processes may not improve performance because the computer has limited CPU resources.

14 processors was the fastest and it plateaud there because my computer only has 14 processers

## Conclusion

This lab demonstrated how multiprocessing works using `fork()`, `execl()`, and `waitpid()`. It also showed how the number of processes affects the time needed to generate Mandelbrot images.