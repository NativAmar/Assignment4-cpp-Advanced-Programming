Overview->
Dungeon Adventure is a text-based game where players navigate through rooms, battle monsters, and manage their health and attack power.
The game uses dynamic room generation based on a configuration file.

Entity.cpp
    Implements the logic for Entity operations, including:
-Modifying health and attack values through overloaded operators.
-Comparing entities for combat logic.
-Outputting entity details using the << operator for easy display.

Room.cpp
   Manages room properties, including:
-Initialization of campfires, monsters, and room connections.
-Dynamically adjusts the room connection array size as needed.
-Ensures safe copying and assignment of room objects by managing dynamic memory effectively.
-Implements bounds-checked access to connected rooms using the [] operator.

Game.cpp
    Manages the core gameplay, including:
-Initializing rooms and entities based on the configuration file.
-Parsing the file to dynamically generate the dungeon structure.
-Controlling the game loop, where players interact with rooms and engage in combat.
-Handles player and monster interactions, like healing, combat, and navigation.

main.cpp:
-Entry point of the application.
-Initializes the Game object with player stats and configuration file path.
-Starts the game loop by calling initialization and execution methods.