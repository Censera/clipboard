# Clipboard

Clipboard is a minimal CLI utility written in C. It allows you to pipe streams or pass arguments directly into an available system clipboard.


The utility requires `libclipboard` installed on your system.

- Ubuntu/Debian: `sudo apt install libclipboard-dev`
- Arch Linux: `sudo pacman -S libclipboard`

## Usage

1. Copying via arguments

```bash
./clipboard "Copy me."
```

2. Copying via piping

```bash
echo "Hello, me!" | ./clipboard
```

```bash
cat file.txt | ./clipboard
```
