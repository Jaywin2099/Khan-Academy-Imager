# Khan-Academy-Imager
Used to convert images into a format usable on Khan Academy.

The images must follow the guidlines of KA.

To use this you must put the two files (KAImager.cpp and stb_image.h) in the same folder as the image you want to pixelate.
Compile the KAImager.cpp file and run it as a .exe; input the name you want for the image on KA (you can just make something up for this if you want), 
hit enter, then input the name of the image you want to pixelate. This must include the file extension as well, for example dog.png, or cat.jpg.

Hit enter and pixels will be automatically copied to your clipboard! All you need to do then is go on Khan Academy and paste it in at the beginning of your code.
The name you gave the image is the name of the image in KA. To use it just add 'image(*name*, x, y);' wherever you want it.

WARNING: Images over 200x200 will probably lag your browser out when you paste them into KA!
