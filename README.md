# PlayerAnalyzer

Application that allows users to compare and analyze Football Manager(FM) players and their efficiency at all the roles of the game.
Only outfield players are supported (no GK).

By default the program uses the attributes set by the game to calculate the efficiency(0-100 value) of a player for every outfield role in the game.
Each attribute that is relevant for a role is assigned a weight. Vital attributes get 0.3 and Prefer attrbutes get 0.2
Efficiency is calculated using a very simple formula 
Eff = SUM OF All(Att(1-20)*Att.weight) / (Number of Attributes* 20*TotalWeight)
The user can edit the weights of each attribute for each role and save them to a file to reuse later. It can also add or remove new attributes from a role.

To upload the player data to the program:
Open FM, go to the player profile, press Ctrl + P and save as a text file.
On the app either:
Drag the player file created by FM to the "Drag and Drop section" (with this method you can upload multiple files at once
Move the player file to the same folder as the executable and write the name of the file in the "Insert File Name" section of the app

The user can also edit the color coding used, this new setting will be saved in between sessions.

The implementation of the app uses:
ImGui for the UI
GLFW for the window
OpenGL and stb_image to load images for the UI
Json for Modern C++ to read the database file 
   


