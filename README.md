# ftsize
A simple C-based tool which let's you find the total size of files with a particular extension on your linux based operating system.

## How to compile and install.
```sh
$ cd ftsize
$ make
$ make install
```

### Description
***ftsize*** displays the size's in Bytes, Kibibytes, Mibibytes of all the file of a perticular extension specified by user in a given path.

| Options | Usage |
| ------- | ----- |
| -h | Displays help option regarding the tool.|
| -p | Used to specify the path of the directory to scan from,(use's '/' as default path if option not specified by the user.) |
| -v | Displays Information regarding the tool |

##### Example of useage :
Display's size of all files with extension of '.c' in the current directory.
```sh
$ ./ftsize "c" -p .
```

Display's size of all files with extension of '.py' in the directory '~/Documents/'.
```sh
$ ./ftsize "py" -p ~/Documents/
```

Display's size of all files with extension of '.cpp' in the root directory (if no '-p' option specified '/' root will be used as path by default).

```sh
$ sudo ./ftsize "cpp"
```
