## Queue data structure

It's **generic** - works with any type because data in `QueueNode`s is stored with `void*`. You just need to cast when using it (see [main.c](./main.c)).

`QueueNode`s are allocated dynamically, while `Queue` itself is not.
