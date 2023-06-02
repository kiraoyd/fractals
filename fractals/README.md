To make an MPEG:

CL: imagemagick -version
CL: sudo apt install imagemagick

Run lights_out_frame_save()
Create Directory for movie to store .bmp files, call it Movie
Move all generated .bmps to Movie

CL: cd Movie

Convert all .bmps to .jpg: convert *.bmp image%d.jpg

CL:  sudo apt install ffmpeg

Convert using ffmpeg to a mp4 movie: ffmpeg -framerate 10 -i image%d.jpg -c:v libx264 -profile:v high -crf 20 -pix_fmt yuv420p lightsOut.mp4


