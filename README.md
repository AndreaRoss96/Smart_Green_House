# Smart_Green_House
integrated embedded system that represents a simplified version of a smart greenhouse.

The task of the smart greenhouse is the automated irrigation (of a certain soil or plant) by implementing a strategy that takes into account the perceived humidity, with the possibility to control and intervene manually via mobile app.

The system is composed by 5 subsystems:
![alt text](https://github.com/AndreaRoss96/Smart_Green_House/blob/master/Report/system.jpg)


 * GreenHouse Server (PC)
    - contains the logic that defines and implements the irrigation strategy
 * GreenHouse Controller (Arduino)
   - allows you to control the opening and closing of the sprinklers (water pumps), thus the amount of water delivered per minute
 * GreenHouse Edge (ESP)
   - allows you to sense the humidity of the soil
 * GreenHouse Mobile App (Android) 
   - allows manual control of the greenhouse 
 * GreenHouse Front End (PC)
   - Front end for data visualisation/observation/analysis

![alt text](https://github.com/AndreaRoss96/Smart_Green_House/blob/master/Report/controllerino_bb.png)
