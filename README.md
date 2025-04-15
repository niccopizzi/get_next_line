#get_next_line


The main purpose for this project is to create a function that reads from a file descriptor and returns the line read.

## The function signature 

```c
    char* get_next_line(int fd)
```

This functions returns either

    1. A pointer to a memory allocated on the heap with the line red from the fd

    2. NULL if EOF was encountered.

> Please note that is the caller's job to free the memory when is not needed anymore. 

---

## IMPORTANT CONCEPTS:

### - Static variable

    A variable that retains its value in subsequents function calls.
In functions we are used to variables that lose their value after the function returns, for example let's suppose we have a very simple function 
```c
int calls(void);
```

And what we want from this function is to return the number of time it was called, how would we go with that? We would need a variable let's call it `tot` that we increase everytime the function is called 
```c
int total_calls(void)
{
    int tot = 0;
    
    tot++;
    return (tot);
}
```
But the problem is that this variable does not retain its value after the function returns,in fact everytime we call the function tot will be initialized to 0, and here is where `static variables` come to save the day, by just declaring tot as `static` we are able to keep track of the number of times this function is called, because after the first initialization to 0 the assignment tot = 0 will be skipped and tot will still have it's value saved when we call the function again later in the program. 
```c
int total_calls(void)
{
    static int tot = 0;

    tot++;
    return (tot);
}
```
To understand better why this works we need to go to a deeper level.
Let's suppose we have the following main.c 

```c
int total_calls(void)
{
    static int tot = 0;

    tot++;
    return (tot);
}

int main(void)
{
    calls();
    return (0);
}
```
We can compile this with `gcc main.c` and get `a.out` as a result.

If we run `a.out` what's going to happen is that the system will reserve an amount of memory for this program to work with, this memory is divided in different regions, the ones we care about for now are the **stack** and the **data segment**.

Let's think of the **stack** as a pile of dishes (a block of memory) put on top of each other, the system will give our program  a maximum amount of dishes (let's say 100) it can use (the stack size, usually 4/8 kbs, you can check it on Linux with ulimit -s). If we go over this number and put let's say 200 dishes on top of eachother the system will make our program crash by sending the infamous **SEGFAULT** signal to our program and we will have a stack overflow.

When we call from our `main` the function `total_calls` what's happening is that the function will put on the stack its own dishes (let's say 30) to do what it has to do (in this case keep track of the amount of time it was called) and when it returns the system will clean the stack by taking these dishes away, and here is the key part! If we don't declare the variable as static everytime the function is called one of the dishes put on the stack will be the variable `tot`, which means that after the function returns the system will take this dish and throw it in the bin. 
To avoid this we need to take this dish and put it aside where it can stay safe and sound, and that's what's happening when we declare the variable as **static**, we take the dish and put it in the **data segment** and so everytime we call `total_calls` from now on we will borrow the dish from the **data segment** and we can be sure that the value will stay there. 

When we return from `main` and the program finish execution the system will relieve the memory that was allocated for our `a.out` program including the data segment.

---

### - File descriptor 

    A non-negative number that refers to a specific file in the system. 
There are several ways to interact with a file from your program in C, one of the easiest one is the open function, which has the following signature:
```c
int open(const char *pathname, int flags, /* mode_t mode */ );
```
Common flags are `O_RDONLY` (open the file with read permission) and `O_RDWR` (open the file with read and write permission).
The pathname can be either relative or absolute and the integer returned by the function will be the file descriptor (the ID) of the file you want to interact with.
Usually open will return a number greater than 2, why?
Because in Linux 0, 1 and 2 are already assigned to represent 3 **specific file descriptors**:

- `0` -> Standard Input
- `1` -> Standard Output
- `2` -> Standard Error

It's quite interesting to see here the Linux's philosophy in action : everything is a file including the keyboard (standard input) and the screen (standard output/standard error). 
For this reason, the first call to open will return `3` (unless an error occurs) and subsequent calls will return `n + 1` where n is the last number returned by open.

### Key Points:

1. There is a **maximum** amount of file descriptors that a process can open at the same time, this limit is definide usually in the fcntl.h (file control) header by `FOPEN_MAX`, usually this limit is set to 16.

2. File descriptors are **not shared** between processes, what does it mean? Well it means that if you have two different processes calling open on different files (let's suppose file1 and file2) they can get the same resulting file descriptor (let's suppose 3), because as said file descriptors are not shared and so the same number can refer to different files depending on the process using it.

3. When you open a file with the open syscall the system **allocates some memory** for your program so that it can interact with the file opened, since this **memory is not automatically released** by the system you need to make it clear that you are not working with the file anymore by using the `close` function which has the following signature :
```c
int close(int fd);
```
> Super easy, lemon squeezy. Close the file and never think about it anymore! 

---

That's it! These are the most important concepts for this project, if you want to learn more I think it would be nice to check also :

- The stack (what it is, how it works, why stack overflow matters in cybersecurity)
- Syscalls, there's **[this]**(https://www.youtube.com/watch?v=xHu7qI1gDPA&t=1155s) great video about them that you can check, it goes quite in depth and explains this concept perfectly.
