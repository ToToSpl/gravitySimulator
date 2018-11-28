<h2>Physics</h2>

<p>Gravity is a very weak force (gravity constant is very small), so masses has to be huge to generate force.
Because of that if we would use si units we would have to deal with huge differences of magnitude (from 10^-11 up to 10^24)
and obviously thats not good numbers for fast calculations.</p>
<p>Thats why i will use these units:</p>

* mass 1 unit is 10^24kg
* distance 1 unit is 10^9m
* force 1 unit is 10^24N (for easy diffision by mass)
* because of that gravity constant is G = 6.67408

* F=(m1*m2)/dist^2 * G * 10^5
* a = F / m * 10^-15

<h2>How to load your planets to simulator:</h2>

<p>You have to prepare a text file (.txt for example) and in it write objects you want to simulate for example:</p>

* star1   1000    760 540     0   2.5   255 200 100     30

<p>each object is divided using new line (enter key) each object has to have a name</p>
<p>what these numbers mean?</p>

- first: mass in 10^24kg
- second and third: x and y coordinates of a object (in pixels but at the same time in 10^9m)
- fourth and fifth: x an y coordinates of a speed vector
- sixth, seventh and eighth: color of a object (red green blue form 0 to 255)
- ninth: size on a screen in pixels

<h2>How to load your objects?</h2>
<p>when you launch program (in unix for example) you have to pass a text file as a standard input stream</p>
<p>./main < name_of_your_text_file</p>
<p>the file has to be in the same folder as the simulator otherwise you have to pass whole directory like in examples:</p>
<p>./main < /examples/planets1.txt</p>

<h2>how to compile?</h2>
<p>for g++ in unix:</p>
<p>g++ -o main main.cpp GravityObject.cpp -lallegro -lallegro_main -lallegro_primitives</p>

<p>the exec will be ./main</p>
