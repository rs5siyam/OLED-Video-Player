# OLED-Video-Player

================================================================================
   ESP32 + OLED VIDEO PLAYER – COMPLETE GUIDE
   Convert any video to play on a 0.96" OLED display
================================================================================

# What you need:
--------------
- ESP32 dev board (e.g., NodeMCU‑32S, DOIT ESP32)
- 0.96 inch OLED display (SSD1306, I2C)
- Jumper wires
- PC with Windows / Mac / Linux
- USB cable for ESP32
- Video file (MP4, AVI, MOV, etc.) – keep it short (5‑10 seconds)

================================================================================
# PART 1 – INSTALL REQUIRED SOFTWARE
================================================================================

1. Install Python (if not already):
   - Download from https://www.python.org/downloads/
   - During installation, check "Add Python to PATH"
   - Verify by opening a terminal / CMD and typing: python --version

2. Install FFmpeg (required to extract frames):
   - Windows:
       * Download from https://www.gyan.dev/ffmpeg/builds/ (pick "release full")
       * Extract the zip, copy the "bin" folder path (e.g., C:\ffmpeg\bin)
       * Add that path to Environment Variables (System > Advanced > Environment Variables > Path)
   - Mac: brew install ffmpeg
   - Linux: sudo apt install ffmpeg
   - Verify: open terminal and type: ffmpeg -version

3. Install Python libraries:
   Open terminal / CMD and run:
      pip install pillow numpy

4. Install Arduino IDE (if not already):
   - Download from https://www.arduino.cc/en/software
   - Install ESP32 board support:
       * File > Preferences > Additional Boards Manager URLs
       * Add: https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
       * Tools > Board > Boards Manager > search "ESP32" > install "ESP32 by Espressif"

5. Install OLED libraries in Arduino IDE:
   - Sketch > Include Library > Manage Libraries
   - Search and install: "Adafruit GFX Library" and "Adafruit SSD1306"

================================================================================
# PART 2 – PREPARE THE CONVERSION SCRIPT
================================================================================

1. Create a new folder on your PC, e.g. "VideoToOLED"

2. Inside that folder, create a Python file named "video_to_esp32_oled.py"
   (Copy the script provided above into this file)

3. Place your video file (e.g., myvideo.mp4) inside the same folder.

4. Edit the script (optional):
   - Change INPUT_VIDEO = "myvideo.mp4"
   - Adjust FPS (frames per second) – lower = smaller file, slower playback
   - Adjust DURATION (seconds to convert) – e.g., 5 for first 5 seconds
   - Leave resolution 128x64 (OLED native)

================================================================================
# PART 3 – RUN THE CONVERSION
================================================================================

1. Open a terminal / CMD in that folder (shift+right-click > Open PowerShell / Terminal).

2. Run the script:
      python video_to_esp32_oled.py

3. Wait – FFmpeg will extract frames, then the script will convert them.
   When finished, you will see a file "video_frames.h" in the same folder.

================================================================================
# PART 4 – UPLOAD TO ESP32 AND PLAY THE VIDEO
================================================================================

1. Open Arduino IDE and create a new sketch (File > New).

2. Save the sketch as "VideoPlayer" (File > Save).

3. Copy the "video_frames.h" file into the sketch folder:
   - In Arduino IDE: Sketch > Show Sketch Folder
   - Move (or copy) video_frames.h into that folder.

4. Write the Arduino code (copy the complete code from below – "Arduino Sketch").
   (See the next section for the full Arduino code)

5. Connect your OLED to ESP32:
      OLED VCC → ESP32 3.3V (or 5V)
      OLED GND → ESP32 GND
      OLED SDA → ESP32 GPIO21
      OLED SCL → ESP32 GPIO22

6. In Arduino IDE:
   - Select your ESP32 board: Tools > Board > ESP32 Arduino > ESP32 Dev Module
   - Select the correct COM port: Tools > Port > COMx (Windows) or /dev/cu... (Mac)
   - Click Upload (right arrow).

7. After upload, the video will play on the OLED with a 3‑second countdown before each loop!

================================================================================
# TROUBLESHOOTING
================================================================================

- "SSD1306 allocation failed": Check I2C wiring (SDA=GPIO21, SCL=GPIO22). Try address 0x3D.
- "video_frames.h: No such file": Put the header file in the same folder as your .ino.
- Sketch too big: Reduce video duration or FPS. Use Tools > Partition Scheme > Huge APP.
- Video plays too fast: Increase FRAME_DELAY_MS (e.g., 150 or 200).
- Video plays too slow: Decrease FRAME_DELAY_MS.
- FFmpeg not found: Install FFmpeg and add to PATH, or use full path in the script.
- No frames extracted: Check that your video file exists and FFmpeg works (test with "ffmpeg -i video.mp4").

================================================================================
END OF INSTRUCTIONS
================================================================================
