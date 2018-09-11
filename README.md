# step2trigger
This is a particular work I did for an UnB (Universidade de Brasília) group. They asked me for a code to filter some inconsistencies in the readings of an EMG sensor that should control a trigger. Latter they asked for some uncommon randomization in the trigger signal. The ramdomization uses the characteristcs specified in the research paradigm.

For this work I first used a low-pass filter in the ADC readings to filter de inconsitencies. Than I uses a differential high-pass filter to detect the momment when the step occurred.

This is indeed a piece of bad code. This was non-critical application. My objectives was provide a signal correction with a minimum interference in the signal or delay in response time. The ramdomization was a demand for proccess automatization (they used to trigger pressing a buttom accordint to a random table).

Besides that, the code is a good demonstration of filters operating in a stream of data. As said early, the first one is a low-pass (moving average) acting over ADC readings. People calls it a Lazy Filter because it have a very slow response time (50 samples). I guess Skeptical Filter is more appropriate as it waits too long to believe a change have occurred.

Then the input need to succeed a change state test. This is the same logic for unbouncing a switch and transforms the analogic data into digital by thresholding.

The input is a squared pulse but just rising edges should activate the trigger. For that porpose a derivative filter with two samples was implemented.

Last but not least: this piece of code shows how a simple code can solve real problems.

The drowbacks of the code do not affect its performance as the events in question had a very low frequency if compared to dalays included in the code. It is a mensurable problem and I knew it would work before I even applied it.

Multitasking was not needed, but would be a cassy solution. I do not think that a pre-emptive aproach would work nor a run-time (interruptions) approach. I would like to try a cooperative approach using state machine or RTOS.
