# step2trigger
This is a particular work I did for an UnB (Universidade de Brasília) group. They asked me for a code to filter some inconsistencies in the readings an EMG sensor that should control a trigger. Latter they asked for some particular randomization in the trigger signal.

For this work I first used a low-pass filter in the ADC readings to filter de inconsitencies. Than I uses a differential high-pass filter to detect the momment when the step occurred.

The ramdomization uses the characteristcs specified in the research paradigm.
