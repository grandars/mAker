# Basic syntax

The Arduino programming language is very similar to that of the C programming language.

For those familiar with programming, below is a summary of the syntax. For those of you who do not know programming, the best way to learn is to look at the [example code](), load it and run it, change it to see what happens and Google when it breaks. And of course, ask! But a full programming course is not the intention here - we do not know it ourselves.

## Setting variables

Variables must always be declared before they are used. Any variable declared outside a function, will be a *global* variable. This means that any function can see and use the variable. These variables should be places at the top of the program, both to find them more easily and to make sure they are set when the functions run.

Any variable placed inside a function will *only* exist inside that function!

