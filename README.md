ASCII Music Project for Linux Embedded Chip (Onion Omega 2)

This project's main goal is to become a full-blown soundboard audio interface, where a matrix of soft, backlit, rubber keys control mappable audio sounds, pitches, effects, and samples. Note: The current version is entirely focused on backend functionality and has not yet been integrated with the embedded device's I/O pins. 

How it Works:

The code reads a composition file containing note instructions, rest instructions, and custom toggles:

Here's what's currently supported:

Input:
C,D,E...A,B

Output:
Plays audio at specific frequency of selected note within current octave. If the system is in drum mode, it plays the drum sound effect associated with the specific note.

Input:
OU

Output:
Increments octave

Input:
OD

Output:
Decrements octave

Input:
M

Output:
Toggles between piano mode and drum mode

Input:
C#,D#...A#

Output:
Similar to C,D,E... but instead plays C sharp, D sharp, etc. which is one semitone higher and allows for access to all keys in any scale.

