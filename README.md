# WaveSimulator
WaveSimulator is a project that we created as a practicum project for [Lumerical Solutions.](www.lumerical.com) It is a simple simulator that can show how a wave propogates in a 2D space. We used Qt and a library developed by Lumerical to create this solution.



## Features
We implemented a number of features for this project.
  * The GUI including:
    * Buttons that start, stop, and step the simulation
    * The ability to add shapes, as well as edit them
    * Clicking to change the source of the wave, and add a 1x1 rectangle
  * Saving and loading using JSON
  * An implementation of the HMVC Model
  
  
  
## HMVC
For this project, we were asked to determine if HMVC is a reasonable model to develop software using Qt. We came to the conclusion that HVMC is a very useful and extendable model, but that it can be difficult to implement as, at the time of development, there was no pre-made framework available. We designed and developed our own system which took up a significant portion of our 4 month development period.



## Dependencies
We used [Qt](https://www.qt.io/) for all the GUI development.



## Libraries
We used the [nlohmann JSON](https://github.com/nlohmann/json/) library for saving and loading, and a wave simulation library developed by Jens Niegemann at Lumerical to handle the wave propogation physics.



## Contibuting
This was a student term project and probably won't see development by us going forward, but feel free to submit a pull request!



## Developers
This was made by:
  * [Tim Bruecker](https://github.com/CanOSpam)
  * [Will Murphy](https://github.com/willamm)
  * [Benny Wang](https://github.com/krixium)
  * [Alex Xia](https://github.com/OPwonShinobi)
