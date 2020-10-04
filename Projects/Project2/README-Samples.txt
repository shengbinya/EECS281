There are some sample files here to help you get correct output,
broken down into two types and two sizes.  The "no-tnt" tiles
have no TNT in them: all tiles are either already cleared (0)
or have rubble.  The "normal" test files have TNT, rubble, etc.

Each type of test files includes two sizes, small (around size 10)
and large (around size 1000).

There are R and equivalent M mode input files for each combination.

There are also output files, one for each input type and size.
Statistics was -s 10 for the small files, -s 1000 for the large.

There's no need to have separate output files for R or M input.
Since the input files are equivalent, you should get the same output
no matter which input file mode you use.  Test this!

Also look at the file Error_messages.txt.  If you have one of the
"Errors you must check for" from the project specification, copy
the appropriate message directly from this text file.  We're working
on adding a feature to the autograder that will show you your error
output if:

1) It is not an INV test case (supposed to exit 1).
2) Your exit status is 1.
3) The first line of text send to cerr matches a line in that file.

If you want to add a second line, that's fine, but we won't display
it to you.  For example, this is valid:

    cerr << "Invalid starting row" << endl;
    cerr << "Size is " << size << ", but starting row is " << startRow << endl;
    exit(1);

In this case, we would show you the first line of output in the
autograder feedback (assuming we get this done before you submit).
There will be an announcement on Piazza when this feature is working.
