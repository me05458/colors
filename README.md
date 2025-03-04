# colors
Pretty stuff that deals with colors in linux  terminal, mostly for the fun of it
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
3 - test mode (prints out a square of the specified size, to test what size looks good on screen)
