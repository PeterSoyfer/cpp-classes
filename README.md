# C++ OOP projects

OOP projects exhibiting main properties of simple and complex classes, operators' overloading etc. Mostly created during my studies in the second year at the Moscow State University, Faculty of Mechanics and Mathematics.

Each sub-project has its own description file where you can see the task it is designed to solve, main features etc.

//-------------------------------------------------------------------------------------------------------

Task named 'simple class' is meant to represent a simple C++ class of rational numbers (fractions) as they are defined in Number Theory: equivalence class of pairs of integers (a, b) = "a / b" up to multiplying the numerator and denominator by the same number.
Features: three initialisation methods (default with no parameters, construct-by-reference and construct-by-value), 4 arithmetic operations (as methods), comparison of fractions, resetting an instance of the class to zero (0/1), parser built from scratch for filling in the fraction from std I/O input, finding the period of a fraction, checking if the fraction is proper, separating the whole part of a fraction. Also, as supportive methods, there are essential printing function, greatest common divisor method and a norming function which reflects the equivalence principle for "a / b" class of congruent rational numbers.
User interface via the command line (std I/O) and/or file data stream is designed to be of maximum safety and friendliness (lovely joke added), handling all exceptions possible.

Task named 'complex class' exploits the same idea of CFrac fraction class of rational numbers, but makes use of the OOP principles: initialisation methods are replaced with class constructors (three-fold polymorphism allows to construct a class instance either by default or by reference/by value), operational methods are replaced with the operators' overloading, other functions are designed in accordance with encapsulation and abstraction principles (usage of get_value/set_value idea and befriending a filling function infrac to the class). Also user-friendly interface with another good joke.

CStrList class was designed to introduce the concept of parsing the file line-by-line (built from scratch), printing the lines read, finding the sub-string in the string read. Everything was designed with the idea of handling all the exceptions possible and maintaining safe user-friendly interface via std I/O. It also has a sub-class CStr implemented for the sake of abstraction and data hiding, making the interaction with the file being parsed much more convenient.
