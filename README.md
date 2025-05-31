# MINIMAL SHELL

## Installation
- Run `make` in order to compile the code and create the `msh` binary file
- Move the `msh` binary in `/usr/local/bin`
    - `/bin`: Contains essential user-level binaries, often required for basic system operations. 
    - `/sbin`: Contains system-level binaries, usually requiring root privileges. 
    - `/usr/bin`: Holds additional user-level binaries, including those installed by the system or packages. 
    - `/usr/sbin`: Contains additional system-level binaries, often for advanced system administration tasks. 
    - `/usr/local/bin`: Used for locally installed binaries, typically for software not packaged with the system. 
    - `/usr/local/sbin`: Similar to /usr/local/bin but for system administration binaries

If you want to set minimal-shell as your login shell, modify the `/etc/passwd` file accordingly.  
If you want to run `msh` shell in your terminal emulator, set it in the "Preference"->"Command" 


## Configuration
The shell is looking for commands in the directories of your PATH environment variable.
PATH environment variable is setted using the `/etc/environment/` file.  

## Build-in commands
- `exit` in order to exit the shell
- `cd [some path]` in order to change working directory

## What is setting env variables
In order to understand what is setting environment variables (on Linux) you could check 

1. Check what happens on bash startup running   
    `bash -xl`    

2. Files that are usually sources   

    Remember that in Unix-like system env variable are inherited from parent process. So the process that launch the shell could set up some of them (ex. terminal emulator)

   System wide

        /etc/environment: specifically meant for environment variables
        /etc/env.d/*: environment variables, split in multiple files
        /etc/profile: all types of initialization scripts
        /etc/profile.d/*: initialization scripts
        /etc/bashrc, /etc/bash.bashrc: meant for functions and aliases

   User specific

        ~/.profile: used for all shells
        ~/.pam_environment: part of Pluggable Authentication Modules for Linux
        ~/.bash_profile: initialization for login (bash-)shells
        ~/.bashrc: initialization for all interactive (bash-)shells
        ~/.cshrc, ~/.zshrc, ~/.tcshrc: similar for non-bash shells

3. Find files where specific env variable is mentioned  
    `grep -r VARIABLE /etc/*`  
    `grep -r VARIABLE ~/*`  


## To Do
- build on other OS
- manage errors better looking at errno global variable
