# Heph lang compiler
1. modify program.heph (Syntax docs coming soon)
2. run `make` to build the compiler code
3. run `make compile` to compile the code from program.heph into hello.S
4. run `make run` to run the compiled code

## Syntax
- You can use !! infront of a line to use the old syntax which allows
weird stuff to compile correctly:)
## Code example
```go
// define a function that returns f(g(h)) for f, g, functions and h number
composefun => @(f, g, h)
    make f : func(1, 1)
    make g : func(1, 1)
// can be also `!!    return h g f`
    return f(g(h))
// double plus one
dblp => @(a)
    return a + a + 1
// triple but if a = 2 modify ret value (one)
trpl => @(a)
    b(a + a + a)
    if (a == 2)
        b(1)
        if (b == 13)
            b(2)
        end
    end
    return b
// return address of a function
getaddr => @(f)
    make f : func(??, ??)
    return f
// make a variable that is 6
// same as `!! 6 gasan`
gasan(6)
// load into gasan the address of composefun
// !! composefun getaddr gasan
gasan(getaddr(composefun))
// load into horia the address of gasan
horia(getaddr(gasan))
// let compiler know that horia is a function and it's signature
make horia : func(3, 1)
// !! 1 _ _dblp _trpl 2 horia call
call(1, horia(dblp, trpl, 2))
```

Checkout program.heph