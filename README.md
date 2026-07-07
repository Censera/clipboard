# clipboard

clipboard is a command-line utility written in C. It writes standard input or command-line arguments to the system clipboard.

## Building

Building requires a C compiler and `libclipboard`.

__Install dependencies:__

Ubuntu/Debian:

```ts
sudo apt install libclipboard-dev`
```

Arch Linux:

```ts
sudo pacman -S libclipboard`
```

NixOS: Use the provided development shell

```nix
nix develop
```

__Compile the binary:__

```ts
clang src/main.c -lclipboard -o bin/clipboard
```

Alternatively, compile with __X11__ support directly via __XCB__:

```ts
clang src/main.c inc/clipboard_x11.c -lxcb -o bin/clipboard
```

## Usage

Write a string argument to the clipboard:

```ts
./bin/clipboard "Copy me."
```

Write standard input to the clipboard:

```ts
echo "Hello, me!" | ./bin/clipboard
cat file.txt | ./bin/clipboard
```
