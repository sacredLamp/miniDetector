# miniDetector
A "down detector" but scaled down to terminal.

miniDetector is a CLI application that allows you to check whether websites, databases, and services are currently online or unavailable, without having to browse the web for each one individually.

Added data is then saved into a `.txt` file, and saved so that on the next start-up, your list of sites remains intact. 


## Goal:
The goal is to create a scaled-down version of DownDetector in order to practice techniques that can be applied to the future project, without having to worry about UI elements. 

## Current Features:

- Allows for the user to add sites to saved list
- Users can input URL's or IP’s for checking manually 
- Stores “favorited” sites for checking later, which persist even on program restart, and can be run entirely

## Implementation:

- [x]  A favorites / saved list of sites, which persists even on program restart
    - [x]  Creates && writes to a `.txt` file in the directory to store saved data
    - [x]  Runs the list automatically on code start-up
- [x]  Users can manually input IPs for pinging
- [x]  Users can run list of saved sites and see which ones are online/offline