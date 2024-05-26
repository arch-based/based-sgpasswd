# BASED Utility

## sgpasswd - Suckless Password Generating Utility

The `BASED` sgpasswd is a suckless, based fetching utility that utilitizes the suckless programming language which is C, it is built from the ground up.

### Features

- **Universal Compatibility**: The `BASED` sgpasswd can be built on any Linux distribution, making it compatible with any distribution based on the Linux kernel.
- **Source Code Distribution**: The `BASED` sgpasswd is distributed as source code rather than a pre-built binary, promoting transparency and flexibility.
- **Memory Safety**: The `BASED` sgpasswd uses the `free()` function to deallocate memory once it's no longer needed, helping prevent memory leaks and contributing to the overall safety of the utility.
- **Password Checking**: Instead of just generating password, The `BASED` sgpasswd checks the password given or generated with a special password checking algorithm that is accurate.
- **Safe Password Generating**: As it is distributed with its code open-sourced, there is no data being sent to a BIG TECH COMPANY like Google, Microsoft, etc.

### Building from Source

As per the "suckless" philosophy, the `BASED` sgpasswd is designed to be built from source. Here's how you can do it with the use of the Makefile:

```
# make clean install
```

### Usage

Using the $PATH environment variable you can run it indirectly without typing in the whole path:

```
$ sgpasswd
```

### Contributing

You may contribute to `sgpasswd` by building, and making pull requests or opening an issue.

### License

`sgpasswd` is an open source software licensed under GNU General Public License version 3.0 (GPLv3.0)
