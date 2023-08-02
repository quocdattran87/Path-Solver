## Second Year University Assignment

The path solving algorithm will find the shortest path from the start to the goal and draw the path. If no path is possible, it will return the map unchanged.

### Running the program:
- Install g++
- Run 'make' to compile all the objects and executable
- Run './solver <input.env >output.out' to execute the program.
- Note the < is required before the input and > is required before the output.
- input.env can be any custom map.
- output.out is the name of the output the algorithm prints the results into.
- Output files are placed in the same directory the the Run command is run in.

### Creating custom maps:
- Check the Maps directories for examples of map layouts so you can create your own.
- Maps can be any square or rectangle size. The bigger it is, the longer it will take to solve.
- Walls are labeled '='.
- Starting position is labelled 'S'.
- Goal is labelled 'G'.
- Empty space is labeled '.'.
