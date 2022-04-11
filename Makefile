colorflood: colorflood.c
	gcc -O3 -o colorflood colorflood.c
install: colorflood /usr/local/bin/
	install -m 755 colorflood /usr/local/bin/colorflood
clean: colorflood
	rm colorflood
