/*  The 10 Print algorithm, implemented on an Arduino with native TV output
 *  See https://10print.org
 *  Written by Danny Walker, 2018
 *  Licensed as CC BY-NC-SA 4.0, see https://creativecommons.org/licenses/by-nc-sa/4.0/
 *  http://danny.makesthings.work
 */ 

#include <TVout.h> // Include the TV output library.

// If you don't have the TVout Library installed already, install it through Sketch -> Include Library -> Manage Libraries.

TVout TV; // Declare the TVout object, and call it TV for convenience.
int gridSize = 8; // The size of the tiles. Feel free to play with this and see what happens! It's best to keep it to a common factor of 128 and 96, so 4, 8, 16 etc.

void setup()  {
  TV.begin(PAL);	// Start the TV output. Change PAL to NTSC if you're in USA/any other NTSC region.
  Serial.begin(9600); // Start the serial output at 9600 baud, so we can see what the Arduino generates on a computer too!
}

void loop() {
  TV.clear_screen(); // Wipe the screen clean so we can draw a new set of tiles to it.
  
  for(int y=0;y<TV.vres();y+=gridSize){ // Loop over the horizontal rows of the tile grid.
    for(int x=0;x<TV.hres();x+= gridSize){ // For each row, loop over each individual tile horizontally.
      
      int threshold = analogRead(A0); // Read the potentiometer to determine the threshold to be used.
      int randomNum = random(0,1024); // Generate a random number from 0-1023
      
      if(randomNum > threshold){
        // Draw a forward slash
        TV.draw_line(x, y+gridSize, x+gridSize, y,1);
        TV.delay(5); // Wait a short time. This makes it animate.
        Serial.print("/"); // Also send the forward slash over Serial
      } else {
        // Draw a backward slash
        TV.draw_line(x,y,x+gridSize, y+gridSize,1);
        TV.delay(5);
        Serial.print("\\"); // The backward slash character is used for "escaping" special characters, and so we need two of them.
      }
    }
    Serial.print("\n"); // Send a new line over serial for every row.
  }
  TV.delay(5000); // At the end of drawing all the tiles, wait 5 seconds.
  Serial.print("\n"); // Print a blank line over serial to separate different patterns.
}
