# DanmakufuObfuscator
A C++ Obfuscator for Touhou Danmakufu ph3, made by Sparen

This project aims to work with the existing Danmakufu syntax to obfuscate individual script files in such a manner as to impede legibility.

There are currently two levels of Obfuscation: <br>
1: Remove all comments - very good for purging documentation and various comments from your code <br>
2: Remove all comments, new lines, tabs, and extra whitespace - Theoretically very good but needs a lot of fixing due to Danmakufu requiring certain things to be on seperate lines.<br>

To compile:		<br>
    make

To run:			<br>
    ./dnhobf filename.ext

# Aims
---Full removal of all comments [Status: DONE]						<br>
---Replacement of all instances of new lines with single spaces  [Status: PROGRESS]		<br>
---Full removal of all instances of tabs and extra whitespace [Status: PROGRESS]		<br>
---Replacement of all local variables with hexadecimal [Status: TODO]			<br>

# Notes
TESTERS: Please do all testing in the tmp folder. I don't want the test files (the originals) to magically disappear.<br>