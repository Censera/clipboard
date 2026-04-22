# Clipboard

Clipboard is a CLI tool that copies another tool's output to a clipboard manager in your system (Linux)

Copy a string to the clipboard manager

```bash
clipboard "Copy me."
```
Copy the output of a command

```bash
echo "hello" | clipboard
```

```bash
cat file.txt | clipboard
```
