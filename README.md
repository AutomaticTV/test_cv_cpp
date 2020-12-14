# Computer Vision & C++ test

The test consists of two separated questions. First, given analysis data (players and ball) for a set of frames, we want to extract when a certain action occurs. And, secondly, we want you to find a bug in a C++ snippet of code. Good luck!

## 1. Computer vision task
Build an application in C++ which aims to, given the (noisy) output from a player and ball detector of a soccer match, detect specific game situations.

Specifically, the application should
 * Parse the input file and process each frame
 * Preprocess the data and try to infer the following Soccer situations from it: ***CORNER***.
 * Generate a new text file with the detected game situations.
 
 Take into account
 * It is possible to use the future (or the past) to take a decision at any moment, but no more than 7 seconds in the future.
 * Players may dissapear from the field of view or be missdetected by our detector and the ball may not be available or be wrongly detected (false positive), however it can be safely assumed this will not happen very often.
 * Try to be as robust as possible. 
 * The code does not have to be fully optimized, but any speed-ups/optimizations are appreciated.
 
 ---
 
 The input file **Task1/players_and_ball.txt** is structured using the following format. Each frame begins with
 
 F: video time in HH:MM:SS.
 
 Then for each frame, each player is marked as:
 
 P:**Track_ID**,**X1**,**Y1**,**X2**,**Y2**,**XF**,**YF**
 
 where **Track_ID** denotes the track number of the detection (if a player with the same **Track_ID** appears in two different frames, it could be assumed that it corresponds to the same player),
 **X1**,**Y1**,**X2**,**Y2** denotes the position in texture coordinates of the player's bounding box (0 <= **X1**,**Y1**,**X2**,**Y2** <= 1). Multiplying these values with the width and height would transform the coordinates to pixels.
 Finally, **XF**, **YF** denotes the position of the players feet on the field in meters. Note that a football field is 105 x 68 meters and that the **[0,0]** position demarks the center of the field (see image below).
 
Also, if the ball is detetected, it is written as:

 B:**XF**,**YF** 
 
where **XF**,**YF** denotes the position of the ball on the field.

As an example, the following frame was extracted from the minute 00:04:43 of the match, has 21 players and the ball.
``` 
F: 00:04:43 
P:20,0.481613,0.324371,0.483661,0.346018,-6.39371,12.6469
P:110,0.477205,0.371702,0.480568,0.404844,-4.20809,-9.33267
P:125,0.460398,0.348474,0.463397,0.375975,-12.2322,-1.07568
P:131,0.454893,0.33643,0.458086,0.366984,-15.5541,2.29287
P:143,0.512629,0.373409,0.516026,0.40982,6.76736,-10.3754
P:153,0.525436,0.374944,0.529068,0.413489,10.5203,-11.14
P:167,0.60594,0.351929,0.609996,0.382523,41.6521,-2.78881
P:186,0.463461,0.418456,0.468901,0.464421,-5.22114,-19.6048
P:189,0.536162,0.412253,0.540176,0.459652,11.3954,-18.8443
P:192,0.483575,0.401176,0.487588,0.435894,-1.32188,-15.4546
P:200,0.485006,0.390363,0.489024,0.424982,-1.16953,-13.5343
P:201,0.463858,0.3828,0.467981,0.424855,-7.04511,-13.5631
P:203,0.437941,0.380308,0.442379,0.420745,-14.6126,-12.8452
P:208,0.409611,0.459737,0.416959,0.519762,-13.2589,-25.2245
P:212,0.382157,0.337401,0.386788,0.372868,-42.906,-0.229768
P:217,0.512193,0.324942,0.514209,0.348154,8.62388,11.5441
P:220,0.501438,0.371372,0.504528,0.406608,3.33286,-9.6777
P:223,0.445514,0.356294,0.448667,0.390672,-15.8111,-5.75998
P:224,0.497761,0.317038,0.499281,0.335593,1.32977,19.5914
P:225,0.479704,0.382285,0.483129,0.417429,-2.96653,-12.08
P:227,0.439279,0.36292,0.442775,0.400392,-16.605,-8.36074
B:-3.51777,-9.91208
```

### Coordinate systems
In the field (0, 0) is the center of the field. In the image the (0, 0) is the top-left corner.
![alt text](https://github.com/AutomaticTV/test-cv-developer/blob/master/images/coordinateSystems.png "Coordinate systems")

### Visual Example
![alt text](https://github.com/AutomaticTV/test-cv-developer/blob/master/images/exampleFrame234.PNG "Field coordinates")

### Final comments
* Upload solution code in a private repository together with the resulting text file and send us the link. We will value both the solution and quality of the code made.

## 2. Code review & bug hunting

Please analyze the following code included in `Task2/main.cxx` file as if you were doing code review for a producer/consumer queue. Note that it is simplified to fit 100 lines of code.
As a part of this task, please share with us your findings and possible improvements (with an explanation why they should be done).

This code may contain a bug causing it to deadlock. Can you find and fix the bug? If yes, can you explain why the bug happened? If not, please describe us the steps you took to verify this.
