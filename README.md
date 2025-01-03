# s(M)exoscope

This is Bram de Jong's classic **s(M)exoscope** plug-in with the source code cleaned up, documented, and modernized for JUCE 8.

![s(M)exoscope](Docs/oscilloscope_full.png)

The original smartelectronix site is defunct now but Bram was kind enough to upload [his plug-in source code](https://github.com/bdejong/smartelectronix/tree/master) to GitHub.

This version is based on [Armando Montanez's JUCE port](https://github.com/armandomontanez/smexoscope) from 2016 and [Jason Perez's fixes](https://github.com/jasonmarkperez/smexoscope-mac). However, I changed almost everything. :smile:

See also [my blog post](https://audiodev.blog/smexoscope/) about this plug-in.

## Installation instructions

:warning: **Use this software at your own risk.** See the [LICENSE](LICENSE.txt) for full details. :warning:

### Mac

The Mac version of the plug-in is signed and notarized.

1. Download **sMexoscope-Mac.zip** from the [Releases page](https://github.com/hollance/sMexoscope/releases).
2. In your **Downloads** folder, double-click **sMexoscope-Mac.zip** to unzip the file.
3. Copy **s(M)exoscope.component** to the folder **/Library/Audio/Plug-Ins/Components**
4. Copy **s(M)exoscope.vst3** to the folder **/Library/Audio/Plug-Ins/VST3**
5. In your DAW, look for **Smartelectronix > s(M)exoscope**. You can insert this plug-in on a mono or stereo track.

If the AU version of the plug-in is not visible in your DAW, open **Applications/Utilities/Terminal**. Type the following and press the enter key:

```bash
killall -9 AudioComponentRegistrar
```

Then restart your DAW. Now the plug-in should be visible. If not, reboot your computer.

### Windows

1. Download **sMexoscope-Windows.zip** from the [Releases page](https://github.com/hollance/sMexoscope/releases).
2. In your **Downloads** folder, right-click **sMexoscope-Windows.zip** and choose **Extract All...** to unzip the file.
3. Copy **s(M)exoscope.vst3** to the folder **C:\Program Files\Common Files\VST3**
4. In your DAW, look for **Smartelectronix > s(M)exoscope**. You can insert this plug-in on a mono or stereo track.

## How to use this plug-in

[Read the manual](Docs/Manual.md) (original by Kerrydan)

Notes: 

- The External trigger mode is not implemented in this version. 
- The docs mention a "modular" version but only the standard version is available.

## Building from source code

### Projucer

Brief instructions:

- Install JUCE 8 or newer.
- Open **s(M)exoscope.jucer** in Projucer and export to your IDE.
- Select the **VST3** or **AU** target and build.

## To-do list

- [x] Improve drawing. Stuff seems to be off by a few pixels.
- [x] Provide binaries so you don't have to compile this from scratch.
- [ ] Dark mode. Bram's repo has dark mode images so why not use them!
- [ ] Click on the text for the AMP knob to switch between linear and decibel display.
- [ ] Make the INTERNAL TRIG SPEED knob independent of the sample rate.
- [ ] Instead of simply clipping samples that go outside of visible range, show them in red to indicate they've been clipped.
- [ ] Use a path to draw the interpolated lines instead of doing the interpolation manually.
- [ ] Don't store two Point objects per pixel but use a custom struct.
- [ ] Make thread-safe. The `peaks` array is written to by the audio code and read from the UI thread.
- [ ] Retina/HiDPI graphics. Resizable UI.

From the original `todo.txt`:

```text
[TODO]
* stereo (left/right/both on display, trigger=left) [Ross Bencina]
* VST programs [AFH]
* editable default settings (think bidule / save as default / registry) [AFH]
```

## Revision history

```text
revision history
----------------
20161202
* static Windows VST builds

20161106
* fixed line rendering gaps
* rebuilt for release compatibility and optimization
* included build for 64-bit Windows

20160902
* ported to JUCE framework
* refresh rate increased to 30fps
* Mouse crosshair black instead of inverted

20040403
* DC-Killer now defaults to OFF [Ross Bencina]
* changed the way the trigger works ("<" to "<=" etc...) [Ross Bencina]
* XY-cross with value readouts on left-click

20031203 :: first release
```

---

```text
[CHANGELOG]

v = bugfix
+ = addition
c = change

[17-04-2004] c   Added sean's graphic readout
[15-12-2003] c   DC-Killer now defaults to OFF [Ross Bencina]
[15-12-2003] v   changed the way the trigger works ("<" to "<=" etc...) [Ross Bencina]
[??-12-2003] +   XY-cross with value readouts

  -- version 1 released

[06-08-2003] +   optional DC-killing [Lee Stacey]
[05-08-2003] +   freeze [Ross Bencina]
[05-08-2003] +   if(trigger less than XX seconds ago) don't trigger again [Ross Belcina]
[05-08-2003] +   waveform zoom when samples/pixel < 1 [Ross Bencina]
[05-08-2003] +   channel switch [Lee Stacey / Ross Bencina]
[04-08-2003] v   stupid clipping bug [Lee Stacey]
```

## Credits

Copyright (C) 2003 Bram de Jong

```text
Bram @ Smartelectronix presents :: The S(m)exoscope
---------------------------------------------------


bram @ smartelectronix.com      :: Code & Conccept
sean @ deadskinboy.com          :: GUI Design
kerrydan                        :: Documentation
sophia @ smartelectronix.com    :: Mac port
armando                         :: Multiplatform JUCE port


Smexoscope is not an effect, nor is it a synthesiser, don't
expect it to generate noise: it's a visualisation only plugin!

Useful for looking at waveforms and very useful for developers.

For more info, see the splendid documentation by Kerrydan.

have fun,


 - bram, sean, kyle, armando
```

Cleaned up and documented by [Matthijs Hollemans](https://audiodev.blog) in December 2024.

JUCE is copyright © Raw Material Software.

VST® is a trademark of Steinberg Media Technologies GmbH, registered in Europe and other countries.
