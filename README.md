# Repository Updating Tool

![GitHub license](https://img.shields.io/badge/license-MIT-blue.svg) 
### Languages used
![C Program](https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white) [![Shell](https://img.shields.io/badge/Shell_Script-121011?style=for-the-badge&logo=gnu-bash&logoColor=white)](Shell) 
## Overview

The Update Repo Tool is a command-line utility designed to simplify the process of updating multiple Git repositories in one go. It recursively searches for Git repositories within a specified directory and performs a `git pull` operation on each repository, keeping them up to date.

[![asciicast](https://asciinema.org/a/630844.svg)](https://asciinema.org/a/630844)


## Features

- Search for Git repositories recursively in a specified directory.
- Display progress while updating repositories.
- Customizable Git binary path.
- Caches the location of the git repositories so that it can run faster, unless the cache has been cleared.
- Color-coded output for better visibility.

## Table of Contents

- [Installation](#installation)
- [Usage](#usage)

## Installation

1. Clone this repository:

   ```bash
   git clone https://github.com/sumanrox/updatemyrepos.git
   ```
2. Run the following command
   ```bash
   cd updatemyrepos && chmod +x install.sh && ./install.sh
   ```

## Usage

```bash
updatemyrepos $HOME/Projects
```
## Issues currently on this project
Prompts for authentication on some repos, just enter blank credential to proceed, I am unable to suppress them for now.


### Made with ❤️ by Suman Roy
[![LinkedIn](https://img.shields.io/badge/LinkedIn-Connect-blue?style=flat-square&logo=linkedin)](https://www.linkedin.com/in/sumanrox/)
