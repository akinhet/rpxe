rpxe
====

This is a small command line tool used to evaluate [reverse polish notation](https://en.wikipedia.org/wiki/Reverse_Polish_notation) mathematical expressions.

Usage
-----

Reverse polish notation is an alternative way of writing mathematical expressions. In RPN the operands (the numbers) always come before the operator, there are no parenthesis and the only rule regarding order of operations is left to right.

Example:  
`2 * (3 + 4)` is equivalent to `2 3 4 + *`

Installation
------------

On Unix:  
`make clean install`
*you will probably need root access*

On Windows:  
`Uhhh... good luck :)`

Known bugs
----------

 - When using * symbol for multiplication, you'll need to escape it or put it in quotation marks, otherwise bash will substitute it with all of the files in the directory
