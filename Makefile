TCC = $(USERPROFILE)\app\tcc\tcc.exe

balles.exe: main.o
	$(TCC) -lOpenGL32 -o $@ $+

main.o: main.c
	$(TCC) -I. -c $<

