# DanmakufuObfuscator
A C++ Obfuscator for Touhou Danmakufu ph3, made by Sparen

This project aims to work with the existing Danmakufu syntax to obfuscate individual script files in such a manner as to impede legibility.

The actual aim of this project is to make sure I don't completely forget C++ over the summer.

To compile:		<br>
    make

To run:			<br>
    ./dnhobf filename.ext

# Aims
---Full removal of all comments [Status: DONE]						<br>
---Full removal of all instances of tabs and extra whitespace [Status: TODO]		<br>
---Replacement of all instances of new lines with single spaces  [Status: TODO]		<br>
---Replacement of all local variables with hexadecimal [Status: TODO]			<br>

# Notes
TESTERS: Please do all testing in the tmp folder. I don't want the test files (the originals) to magically disappear.<br>