#RGB control using a rotatry encoder

This project is based on [Dr Robert Paz'](https://www.youtube.com/user/DrZAP42/feed) excellent *Embedded Systems*, *Hands-On* lecture series: Hands On Arduino 2: Incremental Encoders, Part 1 & 2

...and from [Kevin Darah's](https://www.youtube.com/user/kdarrah1234/featured) eqaually excellent tutorials: Rotary Encoder Tutorial with Arduino Code

The .ffz file shows the *bread-board* set-up I used. The component values I used are also shown on the corresponding components although, the caps I used were the polyester type.
The rotatry encoder I used incorporated a push button, unlike to the simple type and a separate *mode* button, shown in the Fritzing file.

The rotary encoder pins are hardware de-bounced while the *mode* push button is de-bounced in software.

There is a very much reduced level range to each RGB led pin.
 
This is quite likely due to the *count to pwm* mapping. Still trying to get my head around that!

By calculation, I'd expect about 10 steps but by experiment, this appears to yeald about 30 or so levels per 96 counts.

The counter *jumps* (about) 4 counts per rotary indent (out of 96) and these *4 count blocks* are re-mapped to 8 bit pwm - I need to get clear about the calculation for this.

- one possible way to improve this could be to re-work the re-map of the *interupt count* to *level output* in order to utilize the full 0-255 pwm output range.
- or perhaps something in the interupt count could be re-organized.

Another thing to note is that I haven't declared the quadrature array as volatile, as advise due to it being called from within the interupt service routine. This doesn't appear to be causing any problems in this simple implementation, but could possibly cause issues in more complex applications. I, in fact, didn't expect it to work in this way!

  
This project is a work in progress.

All suggestions, comments, fork re-works etc, very welcome.

Thanks : )
