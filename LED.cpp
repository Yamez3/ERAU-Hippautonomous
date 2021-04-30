//This code is meant for an Arduino Nano or related system.
//It controls onboard LED strips by reading voltage values of input pins.
//Due to issues with its related controller current setup is hardcoded to allow only
//one type of LED coloring, despite any inputs read.
inputpins[2] = [1,2];

LED_PIN 6
LED_COUNT 7

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

//last leds are eyes, 6,7

void setup()
{
	strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
	strip.show();            // Turn OFF all pixels ASAP
	strip.setBrightness(255);
}

loop
{
	if(digitalRead(inputpins[0]) == HIGH && digitalRead(inputpins[1]) == LOW)
	{
		//Search
		//Pulsing Red
		redLoop();
	}
	if(digitalRead(inputpins[0]) == LOW && digitalRead(inputpins[1] == HIGH)
	{
		//Capture
		//Changing Green, left right eyes change, body same
		greenLoop();
	}
	if(digitalRead(inputpins[0]) == HIGH && digitalRead(inputpins[1] == HIGH)
	{
		//Backup
		//Flashing Purple
		//155,0,255
		purpleLoop();
	}
	if(digitalRead(inputpins[0]) == LOW && digitalRead(inputpins[1] == LOW)
	{
		//End Game
		//Cirling Colors
		endLoop(50);
	}

strip.setPixelColor(pixel,R,G,B);
strip.show()

}

void greenloop()
{
	for(int i = 0; i < LED_COUNT; i++)
	{
		strip.setPixelColor(i,0,255,0);
	}
	strip.show()
	while(true)
	{
		if(digitalRead(inputpins[0]) != LOW && digitalRead(inputpins[1] != HIGH))
		{
			break;
		}
		else
		{
			strip.setPixelColor(5,0,255,0);
			strip.setPixelColor(6,0,0,0);
			delay(500);
			strip.setPixelColor(5,0,0,0);
			strip.setPixelColor(6,0,255,0);
			delay(500);
			
		}
	}
}

void redloop()
{
	for(int i = 0; i < LED_COUNT; i++)
	{
		strip.setPixelColor(i,255,0,0);
	}
	strip.show()
	while(true)
	{
		if(digitalRead(inputpins[0]) != HIGH && digitalRead(inputpins[1] != LOW))
		{
			break;
		}
		else
		{
			int incr = 6;
			
			for(int j = 1; j < incr; j++)
			{
				for(int i = 0; i < LED_COUNT; i++)
				{
					int x = round(j * (127/incr));
					strip.setPixelColor(i,255-x,0,0);
				}
				strip.show();
				delay(50);
			}
			
			for(int j = 1; j < incr; j++)
			{
				for(int i = 0; i < LED_COUNT; i++)
				{
					int x = round(j * (127/incr));
					strip.setPixelColor(i,128 + x,0,0);
				}
				strip.show();
				delay(50);
			}
			
		}
	}
}

void purpleloop()
{
	for(int i = 0; i < LED_COUNT; i++)
	{
		strip.setPixelColor(i,155,0,255);
	}
	strip.show();
	
	while(true)
	{
		if(digitalRead(inputpins[0]) != HIGH && digitalRead(inputpins[1] != HIGH))
		{
			break;
		}
		else
		{
			for(int i = 0; i < LED_COUNT; i++)
			{
				strip.setPixelColor(i,155,0,255);
			}
			
			strip.show();
			delay(200);

			for(int i = 0; i < LED_COUNT; i++)
			{

				strip.setPixelColor(i,0,0,0);
			}
			strip.show();
			delay(200);
			
		}
	}
}

void endLoop(int wait) {
  int firstPixelHue = 0;     // First pixel starts at red (hue 0)
  for(int a=0; a<30; a++) {  // Repeat 30 times...
    for(int b=0; b<3; b++) { //  'b' counts from 0 to 2...
      strip.clear();         //   Set all pixels in RAM to 0 (off)
      // 'c' counts up from 'b' to end of strip in increments of 3...
      for(int c=b; c<strip.numPixels(); c += 3) {
        // hue of pixel 'c' is offset by an amount to make one full
        // revolution of the color wheel (range 65536) along the length
        // of the strip (strip.numPixels() steps):
        int      hue   = firstPixelHue + c * 65536L / strip.numPixels();
        uint32_t color = strip.gamma32(strip.ColorHSV(hue)); // hue -> RGB
        strip.setPixelColor(c, color); // Set pixel 'c' to value 'color'
      }
      strip.show();                // Update strip with new contents
      delay(wait);                 // Pause for a moment
      firstPixelHue += 65536 / 90; // One cycle of color wheel over 90 frames
    }
  }
}
