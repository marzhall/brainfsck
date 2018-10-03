Brainfuck interpreter. Becuase why not?

Compile:
    make

Run:
    ./bfi <brainfuck program>

Hello World:
    ./bfi "++++++++[>++++[>++>+++>+++>+<<<<-]>+>+>->>+[<]<-]>>.>---.+++++++..+++.>>.<-.<.+++.------.--------.>>+.>++."

If you're a masochist who'd like to inspect and continue using the tape after having run a computation,
you can use the '-r' option to get a prompt after your inital program is run, after which you can enter
a new computation that'll run on the same tape you created to run the main computation!
