SweetFXOculus
=============

SweetFX Oculus shader (with chroma aberration correction) for Oculus/Dive/Google cardboard

This is based on SweetFX 1.4 (the latest version compatible with RadeonPro 1.1.1.0). The only file that was modified from the source files was main.h (the Oculus/Dive/Google cardboard rift warping shader was written directly in that file, with all the includes also hardcoded in there).

Feel free to clean it up. This was tested with a Nexus 7 homebuilt Cheap-culus device successfully.

You want to adapt the #defines in order to adapt the lens correction factors, chroma aberration factors, image X-Y shift, and x separation shift between the 2 eyes, in order to adapt to your own device.

Note: the usual #defines for SweetFX will NOT work, nor the "Custom" one. The barrel distortion shader simply ignores those for now :-/

Enjoy,

Whitecanid