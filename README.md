Assignment 1 – predictMe
Concepts required: Files, Command-line arguments, arrays and strings, makefile, gitlab
1.0 The context: Machine Learning
Machine learning (ML) is an area of Artificial Intelligence that is often talked about.
Every application these days uses machine learning in some form or the other. What is
ML? We will learn a tiny part of what ML is in this assignment.
Machine learning (ML) is like teaching a computer to learn from examples and make
decisions. Imagine you're teaching a toddler to recognize different shapes. You show it
lots of circles, squares, and triangles, and say what each shape is. Eventually, your
toddler learns to recognize them on its own. The more examples you show, the better
the toddler learns.
Similarly, in machine learning, we give a computer a bunch of examples with labels (like
showing the computer lots of pictures of different shapes and saying which is which).
The computer learns patterns from these examples. Then, when we give a new picture
with a certain shape, it uses what it learned to guess the shape (e.g., whether the shape
is circle, square or rectangle).
In the world of computers, we have programs that can learn from data just like your
smart toddler. Instead of writing out every single rule, we give the computer lots of
examples and let it figure out the patterns by itself. Once the computer learns these
patterns, it can make decisions or predictions on new data that it has never seen before.
A simple example used in machine learning is a zoo dataset from the UCI repository
[Forsyth,Richard. (1990). Zoo. UCI Machine Learning Repository.
https://doi.org/10.24432/C5R59V]. In this dataset, a few properties (also called as
features or attributes in the ML world) of 100 different animals are given. One of the
features stores the actual category or class of the animal (also called as class label).
This dataset classifies animals into 7 unique classes. Read the given text files,
readmeZoo and a1Data, to understand the given features, including the last column that
identifies the class label. Machine learning algorithms use the given data (x number
features and 1 class label of y number of samples), to predict the class of a new sample
z, given its x number of features. Many a times, these predictions are correct, but many
a times, they are also incorrect. The number of correct predictions it makes is used to
determine the accuracy of the ML algorithm.

You can read more on these ML concepts from this textbook: Data Mining: Concepts
and Techniques by Jiawei Han (Author), Micheline Kamber (Author), Jian Pei (Author)
1.1 Prerequisite – First things First
As the sole software developer of this project, you will create a program that does some
simple machine learning tasks. Although it is beyond the scope of this course and
assignment to explain ML algorithms in detail, in this assignment, you will write
functions to do simple ML tasks.
All data will be read in from external files and parsed into structs. Two data files will be
provided to you. One of them called a1Data.txt will contain data for 100 animals. The
second data file called testData.csv consists of data for NUM_TEST_DATA animals.
The software will take the parsed data and determine some statistics on the data. It will
also use a simple ML algorithm called k-nearest neighbors to predict the class label of a
new sample using some distance / similarity functions. The details on this follows in the
next section.
This assignment stresses the importance of developing software that strictly conforms
to specification—when you're in the industry, you'll face all sorts of strict clients.
There are two source (2) files that you will need to submit:
(1) You will write a .c file, lastnameFirstnameA1.c containing the function
implementations detailed below, and of any additional helper functions you may use in
your code.
(2) You will write a .c file, lastnameFirstnameA1Main.c with the main function
____________________________________________________________________
