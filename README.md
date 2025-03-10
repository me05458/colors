# colors
Pretty stuff that deals with colors in linux terminal, mostly for the fun of it
# usage
to install: `git clone https://github.com/me05458/colors&&cd colors&&make`\
when using simple mode: `./colors <rows>` (looks better on bigger rows)\
when using fancy mode: `./colors <width> <height>` (bigger rows even more important here, and make sure they exactly fit the screen by height or problems will ensue)\
when using test mode: `./colors <width> <height>`\
If `<rows>` or `<width> <height>` not specified they will be 10.
# configure
Place one number in the config file\
1 - simple mode (just falling color changes, slightly less nice gradient)\
2 - fancy mode (fun little star thingies that only barely work and fade to white)\
3 - test mode (prints out a square of the specified size, to test what size looks good on screen)\
4 - gradient mode (pretty vertical gradient, currently default)
# test mode
Bear in mind that test mode simply prints a square of the size specified. After that the program exits and the system provides a prompt (and an extra line) so the optimal size will be one row more than the screen displays. The width should not be more than the windth of the window or it will look very strange, but it's exact size is less important. The top row of the square will be white, the bottom row dark blue.
